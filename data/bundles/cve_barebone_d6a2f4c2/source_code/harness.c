/*
 * Direct-call harness for CVE-2017-13001 (tcpdump print-nfs.c: nfs_printfh()).
 *
 * Baseline dedup_token: __interceptor_strncpy--nfs_printfh--parsefh
 * CWE-125 (heap-buffer-overflow READ).
 *
 * Root cause: nfs_printfh() calls Parse_fh() (parsenfsfh.c) to classify a raw
 * NFS file handle.  When the handle bytes match the VMS/UCX heuristic
 * (is_UCX()), Parse_fh() sets *fsnamep to point DIRECTLY into the caller's
 * file-handle buffer: `*fsnamep = (const char *)&(fhp[1]);` -- with NO
 * guarantee that a NUL terminator exists within the buffer.  Back in
 * nfs_printfh(), `strncpy(temp, sfsname, NFSX_V3FHMAX)` (NFSX_V3FHMAX == 64)
 * then reads from that pointer looking for a NUL, up to 64 bytes -- if the
 * real captured-packet buffer backing the file handle is shorter than
 * (sfsname + 64), strncpy reads past the end of the heap allocation.  This
 * is exactly the upstream fix in tcpdump commit
 * 7a923447fd49a069a0fd3b6c3547438ab5ee2123 (adds an ND_TCHECK2/length check
 * before trusting an "Unknown" file handle's payload before this point --
 * nfs_printfh() itself performs NO bounds check on `dp`/`len` before handing
 * the raw pointer to Parse_fh()/strncpy(), which is the actual vulnerable
 * behaviour this harness reproduces).
 *
 * The target function nfs_printfh() is embedded VERBATIM (byte-identical to
 * target/original_function.c).  Its real callee Parse_fh() (plus its own
 * static helper is_UCX() and every FHT_ / make_uint macro it uses) is
 * embedded VERBATIM from source_code/parsenfsfh.c, because it is Parse_fh()
 * that decides whether the vulnerable *fsnamep pointer is produced -- the
 * bug cannot be reproduced without it.  my_fsid/my_devt (nfsfh.h) and
 * NFSX_V3FHMAX (nfs.h) are copied verbatim (real names).  netdissect_options
 * is reduced to just the two fields nfs_printfh() actually touches
 * (ndo_uflag, ndo_printf) -- same reduction precedent used by the other
 * tcpdump direct-call harnesses in this benchmark (real field names, unused
 * fields dropped since this is a fully self-contained translation unit).
 *
 * main() reads argv[1] into a HEAP buffer (malloc), sized EXACTLY to the
 * file, and calls nfs_printfh(&ndo, (const uint32_t *)buf, buf_len/4) once
 * directly -- so the ASAN redzone sits exactly where the real captured-
 * packet buffer boundary would be.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- real BSD-style aliases (netdissect-stdinc.h compat on this platform) ---- */
typedef unsigned int u_int;
typedef unsigned char u_char;

/* ---- netdissect.h (reduced to the fields nfs_printfh() actually touches) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_uflag;		/* Print undecoded NFS handles */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- nfsfh.h (verbatim) ---- */
typedef struct {
	uint32_t Minor;	/* upper case to avoid clashing with macro names */
	uint32_t Major;
} my_devt;

typedef	struct {
	my_devt	Fsid_dev;		/* XXX avoid name conflict with AIX */
	char Opaque_Handle[2 * 32 + 1];
	uint32_t fsid_code;
} my_fsid;

/* ---- nfs.h (verbatim, the one macro nfs_printfh() needs) ---- */
#define	NFSX_V3FHMAX		64	/* max. allowed by protocol */

/* ==================================================================== *
 * parsenfsfh.c -- Parse_fh() + is_UCX() + supporting macros, VERBATIM.  *
 * This is the real callee that decides the vulnerable *fsnamep pointer *
 * nfs_printfh() then strncpy()s from.                                  *
 * ==================================================================== */

#define	FHT_UNKNOWN	0
#define	FHT_AUSPEX	1
#define	FHT_DECOSF	2
#define	FHT_IRIX4	3
#define	FHT_IRIX5	4
#define	FHT_SUNOS3	5
#define	FHT_SUNOS4	6
#define	FHT_ULTRIX	7
#define	FHT_VMSUCX	8
#define	FHT_SUNOS5	9
#define	FHT_AIX32	10
#define	FHT_HPUX9	11
#define	FHT_BSD44	12

#ifdef	ultrix
/* Nasty hack to keep the Ultrix C compiler from emitting bogus warnings */
#define	XFF(x)	((uint32_t)(x))
#else
#define	XFF(x)	(x)
#endif

#define	make_uint32(msb,b,c,lsb)\
	(XFF(lsb) + (XFF(c)<<8) + (XFF(b)<<16) + (XFF(msb)<<24))

#define	make_uint24(msb,b, lsb)\
	(XFF(lsb) + (XFF(b)<<8) + (XFF(msb)<<16))

#define	make_uint16(msb,lsb)\
	(XFF(lsb) + (XFF(msb)<<8))

#ifdef	__alpha
	/* or other 64-bit systems */
#define	make_uint48(msb,b,c,d,e,lsb)\
	((lsb) + ((e)<<8) + ((d)<<16) + ((c)<<24) + ((b)<<32) + ((msb)<<40))
#else
	/* on 32-bit systems ignore high-order bits */
#define	make_uint48(msb,b,c,d,e,lsb)\
	((lsb) + ((e)<<8) + ((d)<<16) + ((c)<<24))
#endif

/* locale-independent printable-ASCII test (ND_ISPRINT from netdissect.h) */
#define	ND_ISPRINT(c)	((c) >= 0x20 && (c) <= 0x7E)

static int is_UCX(const unsigned char *, u_int);

void
Parse_fh(register const unsigned char *fh, u_int len, my_fsid *fsidp,
	 uint32_t *inop,
	 const char **osnamep, /* if non-NULL, return OS name here */
	 const char **fsnamep, /* if non-NULL, return server fs name here (for VMS) */
	 int ourself)	/* true if file handle was generated on this host */
{
	register const unsigned char *fhp = fh;
	uint32_t temp;
	int fhtype = FHT_UNKNOWN;
	u_int i;

	/*
	 * Require at least 16 bytes of file handle; it's variable-length
	 * in NFSv3.  "len" is in units of 32-bit words, not bytes.
	 */
	if (len < 16/4)
		fhtype = FHT_UNKNOWN;
	else {
		if (ourself) {
		    /* File handle generated on this host, no need for guessing */
		}
		/*
		 * This is basically a big decision tree
		 */
		else if ((fhp[0] == 0) && (fhp[1] == 0)) {
		    /* bytes[0,1] == (0,0); rules out Ultrix, IRIX5, SUNOS5 */
		    /* probably rules out HP-UX, AIX unless they allow major=0 */
		    if ((fhp[2] == 0) && (fhp[3] == 0)) {
			/* bytes[2,3] == (0,0); must be Auspex */
			/* XXX or could be Ultrix+MASSBUS "hp" disk? */
			fhtype = FHT_AUSPEX;
		    }
		    else {
			/*
			 * bytes[2,3] != (0,0); rules out Auspex, could be
			 * DECOSF, SUNOS4, or IRIX4
			 */
			if ((fhp[4] != 0) && (fhp[5] == 0) &&
				(fhp[8] == 12) && (fhp[9] == 0)) {
			    /* seems to be DECOSF, with minor == 0 */
			    fhtype = FHT_DECOSF;
			}
			else {
			    /* could be SUNOS4 or IRIX4 */
			    /* XXX the test of fhp[5] == 8 could be wrong */
			    if ((fhp[4] == 0) && (fhp[5] == 8) && (fhp[6] == 0) &&
			        (fhp[7] == 0)) {
				/* looks like a length, not a file system typecode */
				fhtype = FHT_IRIX4;
			    }
			    else {
				/* by elimination */
				fhtype = FHT_SUNOS4;
			    }
			}
		    }
		}
		else {
		    /*
		     * bytes[0,1] != (0,0); rules out Auspex, IRIX4, SUNOS4
		     * could be IRIX5, DECOSF, UCX, Ultrix, SUNOS5
		     * could be AIX, HP-UX
		     */
		    if ((fhp[2] == 0) && (fhp[3] == 0)) {
			/*
			 * bytes[2,3] == (0,0); rules out OSF, probably not UCX
			 * (unless the exported device name is just one letter!),
			 * could be Ultrix, IRIX5, AIX, or SUNOS5
			 * might be HP-UX (depends on their values for minor devs)
			 */
			if ((fhp[6] == 0) && (fhp[7] == 0)) {
			    fhtype = FHT_BSD44;
			}
			/*XXX we probably only need to test of these two bytes */
			else if ((len >= 24/4) && (fhp[21] == 0) && (fhp[23] == 0)) {
			    fhtype = FHT_ULTRIX;
			}
			else {
			    /* Could be SUNOS5/IRIX5, maybe AIX */
			    /* XXX no obvious difference between SUNOS5 and IRIX5 */
			    if (fhp[9] == 10)
				fhtype = FHT_SUNOS5;
			    /* XXX what about AIX? */
			}
		    }
		    else {
			/*
			 * bytes[2,3] != (0,0); rules out Ultrix, could be
			 * DECOSF, SUNOS5, IRIX5, AIX, HP-UX, or UCX
			 */
			if ((fhp[8] == 12) && (fhp[9] == 0)) {
			    fhtype = FHT_DECOSF;
			}
			else if ((fhp[8] == 0) && (fhp[9] == 10)) {
			    /* could be SUNOS5/IRIX5, AIX, HP-UX */
			    if ((fhp[7] == 0) && (fhp[6] == 0) &&
				(fhp[5] == 0) && (fhp[4] == 0)) {
				/* XXX is this always true of HP-UX? */
				fhtype = FHT_HPUX9;
			    }
			    else if (fhp[7] == 2) {
				/* This would be MNT_NFS on AIX, which is impossible */
				fhtype = FHT_SUNOS5;	/* or maybe IRIX5 */
			    }
			    else {
				/*
				 * XXX Could be SUNOS5/IRIX5 or AIX.  I don't
				 * XXX see any way to disambiguate these, so
				 * XXX I'm going with the more likely guess.
				 * XXX Sorry, Big Blue.
				 */
				fhtype = FHT_SUNOS5;	/* or maybe IRIX5 */
			    }
		        }
			else {
			    if (is_UCX(fhp, len)) {
				fhtype = FHT_VMSUCX;
			    }
			    else {
				fhtype = FHT_UNKNOWN;
			    }
			}
		    }
		}
	}

	/* XXX still needs to handle SUNOS3 */

	switch (fhtype) {
	case FHT_AUSPEX:
	    fsidp->Fsid_dev.Minor = fhp[7];
	    fsidp->Fsid_dev.Major = fhp[6];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "Auspex";
	    break;

	case FHT_BSD44:
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);

	    if (osnamep)
		*osnamep = "BSD 4.4";
	    break;

	case FHT_DECOSF:
	    fsidp->fsid_code = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
			/* XXX could ignore 3 high-order bytes */

	    temp = make_uint32(fhp[3], fhp[2], fhp[1], fhp[0]);
	    fsidp->Fsid_dev.Minor = temp & 0xFFFFF;
	    fsidp->Fsid_dev.Major = (temp>>20) & 0xFFF;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);
	    if (osnamep)
		*osnamep = "OSF";
	    break;

	case FHT_IRIX4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[8], fhp[9], fhp[10], fhp[11]);

	    if (osnamep)
		*osnamep = "IRIX4";
	    break;

	case FHT_IRIX5:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "IRIX5";
	    break;

	case FHT_SUNOS4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS4";
	    break;

	case FHT_SUNOS5:
	    temp = make_uint16(fhp[0], fhp[1]);
	    fsidp->Fsid_dev.Major = (temp>>2) &  0x3FFF;
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp & 0x3FFFF;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS5";
	    break;

	case FHT_ULTRIX:
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];

	    temp = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
	    *inop = temp;
	    if (osnamep)
		*osnamep = "Ultrix";
	    break;

	case FHT_VMSUCX:
	    /* No numeric file system ID, so hash on the device-name */
	    if (sizeof(*fsidp) >= 14) {
		if (sizeof(*fsidp) > 14)
		    memset((char *)fsidp, 0, sizeof(*fsidp));
		/* just use the whole thing */
		memcpy((char *)fsidp, (const char *)fh, 14);
	    }
	    else {
		uint32_t tempa[4];	/* at least 16 bytes, maybe more */

		memset((char *)tempa, 0, sizeof(tempa));
		memcpy((char *)tempa, (const char *)fh, 14); /* ensure alignment */
		fsidp->Fsid_dev.Minor = tempa[0] + (tempa[1]<<1);
		fsidp->Fsid_dev.Major = tempa[2] + (tempa[3]<<1);
		fsidp->fsid_code = 0;
	    }

	    /* VMS file ID is: (RVN, FidHi, FidLo) */
	    *inop = make_uint32(fhp[26], fhp[27], fhp[23], fhp[22]);

	    /* Caller must save (and null-terminate?) this value */
	    if (fsnamep)
		*fsnamep = (const char *)&(fhp[1]);

	    if (osnamep)
		*osnamep = "VMS";
	    break;

	case FHT_AIX32:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "AIX32";
	    break;

	case FHT_HPUX9:
	    fsidp->Fsid_dev.Major = fhp[0];
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "HPUX9";
	    break;

	case FHT_UNKNOWN:
	    /* Save the actual handle, so it can be display with -u */
	    for (i = 0; i < len*4 && i*2 < sizeof(fsidp->Opaque_Handle) - 1; i++)
	    	(void)snprintf(&(fsidp->Opaque_Handle[i*2]), 3, "%.2X", fhp[i]);
	    fsidp->Opaque_Handle[i*2] = '\0';

	    /* XXX for now, give "bogus" values to aid debugging */
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = 257;
	    fsidp->Fsid_dev.Major = 257;
	    *inop = 1;

	    /* display will show this string instead of (257,257) */
	    if (fsnamep)
		*fsnamep = "Unknown";

	    if (osnamep)
		*osnamep = "Unknown";
	    break;

	}
}

/*
 * Is this a VMS UCX file handle?
 *	Check for:
 *	(1) leading code byte	[XXX not yet]
 *	(2) followed by string of printing chars & spaces
 *	(3) followed by string of nulls
 */
static int
is_UCX(const unsigned char *fhp, u_int len)
{
	register u_int i;
	int seen_null = 0;

	/*
	 * Require at least 28 bytes of file handle; it's variable-length
	 * in NFSv3.  "len" is in units of 32-bit words, not bytes.
	 */
	if (len < 28/4)
		return(0);

	for (i = 1; i < 14; i++) {
	    if (ND_ISPRINT(fhp[i])) {
		if (seen_null)
		   return(0);
		else
		   continue;
	    }
	    else if (fhp[i] == 0) {
		seen_null = 1;
		continue;
	    }
	    else
		return(0);
	}

	return(1);
}

/* ==================================================================== *
 * print-nfs.c: nfs_printfh() -- the TARGET function, VERBATIM.          *
 * ==================================================================== */

static void
nfs_printfh(netdissect_options *ndo,
            register const uint32_t *dp, const u_int len)
{
	my_fsid fsid;
	uint32_t ino;
	const char *sfsname = NULL;
	char *spacep;

	if (ndo->ndo_uflag) {
		u_int i;
		char const *sep = "";

		ND_PRINT((ndo, " fh["));
		for (i=0; i<len; i++) {
			ND_PRINT((ndo, "%s%x", sep, dp[i]));
			sep = ":";
		}
		ND_PRINT((ndo, "]"));
		return;
	}

	Parse_fh((const u_char *)dp, len, &fsid, &ino, NULL, &sfsname, 0);

	if (sfsname) {
		/* file system ID is ASCII, not numeric, for this server OS */
		static char temp[NFSX_V3FHMAX+1];

		/* Make sure string is null-terminated */
		strncpy(temp, sfsname, NFSX_V3FHMAX);
		temp[sizeof(temp) - 1] = '\0';
		/* Remove trailing spaces */
		spacep = strchr(temp, ' ');
		if (spacep)
			*spacep = '\0';

		ND_PRINT((ndo, " fh %s/", temp));
	} else {
		ND_PRINT((ndo, " fh %d,%d/",
			     fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor));
	}

	if(fsid.Fsid_dev.Minor == 257)
		/* Print the undecoded handle */
		ND_PRINT((ndo, "%s", fsid.Opaque_Handle));
	else
		ND_PRINT((ndo, "%ld", (long) ino));
}

/* ==================================================================== *
 * main(): direct-call driver.                                          *
 * ==================================================================== */

static int
harness_printf(netdissect_options *ndo, const char *fmt, ...)
{
	int rc;
	va_list ap;
	(void)ndo;
	va_start(ap, fmt);
	rc = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return rc;
}

int
main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	unsigned char *buf;
	size_t nread;
	netdissect_options ndo;
	const uint32_t *dp;
	u_int len;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 1; }
	rewind(f);

	/* Attacker data MUST live on the heap so ASAN's redzone lines up
	 * exactly with the real captured-packet buffer boundary. */
	buf = (unsigned char *)malloc(fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 1; }

	nread = fsz > 0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);
	(void)nread;

	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_uflag = 0;		/* real run_template uses "-v -nn -r", no -u */
	ndo.ndo_printf = harness_printf;

	dp = (const uint32_t *)buf;
	len = (u_int)((fsz > 0 ? (size_t)fsz : 0) / sizeof(uint32_t));

	nfs_printfh(&ndo, dp, len);

	free(buf);
	return 0;
}

/* cve_barebone direct-call harness for CVE (file/file `file` utility)
 * Target: do_core_note  (src/readelf.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * Fix commit a642587a9c9e2dd7feacdf513c3643ce26ad3c22 changed:
 *     for (cp = cname; *cp && isprint(*cp); cp++)
 *   to:
 *     for (cp = cname; cp < nbuf + size && *cp && isprint(*cp); cp++)
 *
 * do_core_note() scans up to NOFFSETS candidate offsets into the note-descriptor
 * buffer `nbuf` looking for a run of 16 printable, non-NUL bytes (the "program
 * name" heuristic).  Each candidate window IS bounds-checked against `size` and
 * `descsz` while it validates those first 16 bytes.  But once a window "wins",
 * the vulnerable code re-walks the SAME start pointer `cname` with a second,
 * UNBOUNDED loop that only stops on a NUL byte or a non-printable byte -- it
 * never compares `cp` against `nbuf + size`.  If the winning 16-byte window
 * sits at (or near) the very end of the `size`-byte allocation and the bytes
 * immediately after it also happen to be printable/non-NUL, the second loop
 * walks straight off the end of the heap allocation -> ASAN heap-buffer-overflow
 * READ, entirely inside do_core_note's own body.
 *
 * Isolation notes:
 *  - `struct magic_set` is fully opaque to do_core_note (it is only ever passed
 *    through to file_printf/file_printable, never dereferenced) so a minimal
 *    opaque definition is faithful.
 *  - `file_printf` / `file_printable` are incidental formatting helpers (their
 *    real implementations format into ms->o.buf, an accumulation buffer that
 *    plays no role in the bug); minimal faithful stubs matching the real
 *    prototypes in src/file.h stand in for them.
 *  - `getu32`/`elf_getu32` ARE on a code path compiled into do_core_note's body
 *    (the OS_STYLE_NETBSD case) so `getu32` is copied verbatim from
 *    src/readelf.c rather than stubbed.
 *  - All #defines/typedefs below (isquote, CAST, ELFCLASS64, FLAGS_*, OS_STYLE_*,
 *    os_style_names, NT_PRPSINFO, NT_NETBSD_CORE_PROCINFO,
 *    struct NetBSD_elfcore_procinfo) are copied verbatim from src/readelf.c /
 *    src/readelf.h / src/file.h -- real names, real values.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- verbatim from src/file.h ---- */
#define private static
#define CAST(T, b)	((T)(b))

/* Enable the ELFCORE-guarded body of do_core_note (verbatim source has the
 * whole function wrapped in #ifdef ELFCORE ... #endif; without this it would
 * be a no-op `return 0;` and the bug could never be reached). */
#define ELFCORE 1

/* ---- verbatim from src/readelf.c (isquote macro) ---- */
#define isquote(c) (strchr("'\"`", (c)) != NULL)

/* ---- verbatim from src/readelf.h ---- */
#define	ELFCLASS32	1
#define	ELFCLASS64	2

#define	NT_NETBSD_CORE_PROCINFO		1
#define	NT_PRPSINFO	3

struct NetBSD_elfcore_procinfo {
	/* Version 1 fields start here. */
	uint32_t	cpi_version;		/* our version */
	uint32_t	cpi_cpisize;		/* sizeof(this struct) */
	uint32_t	cpi_signo;		/* killing signal */
	uint32_t	cpi_sigcode;		/* signal code */
	uint32_t	cpi_sigpend[4];		/* pending signals */
	uint32_t	cpi_sigmask[4];		/* blocked signals */
	uint32_t	cpi_sigignore[4];	/* ignored signals */
	uint32_t	cpi_sigcatch[4];	/* caught signals */
	int32_t		cpi_pid;		/* process ID */
	int32_t		cpi_ppid;		/* parent process ID */
	int32_t		cpi_pgrp;		/* process group ID */
	int32_t		cpi_sid;		/* session ID */
	uint32_t	cpi_ruid;		/* real user ID */
	uint32_t	cpi_euid;		/* effective user ID */
	uint32_t	cpi_svuid;		/* saved user ID */
	uint32_t	cpi_rgid;		/* real group ID */
	uint32_t	cpi_egid;		/* effective group ID */
	uint32_t	cpi_svgid;		/* saved group ID */
	uint32_t	cpi_nlwps;		/* number of LWPs */
	int8_t		cpi_name[32];		/* copy of p->p_comm */
	/* Add version 2 fields below here. */
	int32_t		cpi_siglwp;	/* LWP target of killing signal */
};

/* ---- verbatim from src/readelf.c ---- */
#define	OS_STYLE_SVR4		0
#define	OS_STYLE_FREEBSD	1
#define	OS_STYLE_NETBSD		2

private const char os_style_names[][8] = {
	"SVR4",
	"FreeBSD",
	"NetBSD",
};

#define FLAGS_DID_CORE			0x0004
#define FLAGS_DID_CORE_STYLE		0x0020
#define FLAGS_IS_CORE			0x0800

/* prpsoffsets()/NOFFSETS as built with USE_NT_PSINFO undefined (the file
 * project's own default -- USE_NT_PSINFO is not defined anywhere in the
 * build). Verbatim from src/readelf.c. */
static const size_t	prpsoffsets32[] = {
	100,		/* SunOS 5.x (command line) */
	84,		/* SunOS 5.x (short name) */

	44,		/* Linux (command line) */
	28,		/* Linux 2.0.36 (short name) */

	8,		/* FreeBSD */
};

static const size_t	prpsoffsets64[] = {
	136,		/* SunOS 5.x, 64-bit (command line) */
	120,		/* SunOS 5.x, 64-bit (short name) */

	56,		/* Linux (command line) */
	40,             /* Linux (tested on core from 2.4.x, short name) */

	16,		/* FreeBSD, 64-bit */
};

#define	NOFFSETS32	(sizeof(prpsoffsets32) / sizeof(prpsoffsets32[0]))
#define NOFFSETS64	(sizeof(prpsoffsets64) / sizeof(prpsoffsets64[0]))

/* clazz/prpsoffsets/NOFFSETS below reference the function-local parameter
 * `clazz`, matching the real header's function-like macros exactly. */
#define prpsoffsets(i)	(clazz == ELFCLASS32			\
			 ? prpsoffsets32[i]			\
			 : prpsoffsets64[i])
#define NOFFSETS	(clazz == ELFCLASS32 ? NOFFSETS32 : NOFFSETS64)

/* ---- opaque `struct magic_set`: do_core_note never dereferences it, only
 * threads the pointer through to file_printf/file_printable. ---- */
struct magic_set { int _unused; };

/* ---- verbatim from src/readelf.c: getu32(), used by the elf_getu32() macro
 * on the OS_STYLE_NETBSD path compiled into do_core_note's body. ---- */
private uint32_t
getu32(int swap, uint32_t value)
{
	union {
		uint32_t ui;
		char c[4];
	} retval, tmpval;

	if (swap) {
		tmpval.ui = value;

		retval.c[0] = tmpval.c[3];
		retval.c[1] = tmpval.c[2];
		retval.c[2] = tmpval.c[1];
		retval.c[3] = tmpval.c[0];

		return retval.ui;
	} else
		return value;
}

#define elf_getu32(swap, value) getu32(swap, value)

/* ---- minimal faithful stub for the incidental ms-accumulation-buffer
 * formatting helper (src/file.h prototype, real signature). do_core_note only
 * checks the return value (!= -1), never the formatted content -- BUT the
 * stub must actually CONSUME its varargs (here via a real vfprintf to
 * stderr) rather than silently discard them. A discard-everything stub
 * (`(void)fmt; return 0;`) is fully analyzable by the optimizer within this
 * one-TU build: it can prove do_core_note's `cp`/`cname` computation feeds
 * nothing but that provably-pure, always-0 call, and at -O1 it DCEs the
 * whole loop -- silently eliminating the very heap OOB reads this harness
 * exists to reproduce. Routing through vfprintf (an opaque external libc
 * call whose body isn't visible in this TU) forces the compiler to keep the
 * loop and its reads for real, matching the real file_printf's behavior of
 * actually walking the string it's given. */
private int
file_printf(struct magic_set *ms, const char *fmt, ...)
{
	(void)ms;
	va_list ap;
	va_start(ap, fmt);
	int rv = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return rv;
}

private char *
file_printable(char *buf, size_t bufsize, const char *str)
{
	size_t n = strlen(str);
	if (bufsize == 0)
		return buf;
	if (n >= bufsize)
		n = bufsize - 1;
	memcpy(buf, str, n);
	buf[n] = '\0';
	return buf;
}

/* ==== VERBATIM from data_cve/cve_b1c7f1b0/target/original_function.c ==== */
private int
do_core_note(struct magic_set *ms, unsigned char *nbuf, uint32_t type,
    int swap, uint32_t namesz, uint32_t descsz,
    size_t noff, size_t doff, int *flags, size_t size, int clazz)
{
#ifdef ELFCORE
	int os_style = -1;
	/*
	 * Sigh.  The 2.0.36 kernel in Debian 2.1, at
	 * least, doesn't correctly implement name
	 * sections, in core dumps, as specified by
	 * the "Program Linking" section of "UNIX(R) System
	 * V Release 4 Programmer's Guide: ANSI C and
	 * Programming Support Tools", because my copy
	 * clearly says "The first 'namesz' bytes in 'name'
	 * contain a *null-terminated* [emphasis mine]
	 * character representation of the entry's owner
	 * or originator", but the 2.0.36 kernel code
	 * doesn't include the terminating null in the
	 * name....
	 */
	if ((namesz == 4 && strncmp((char *)&nbuf[noff], "CORE", 4) == 0) ||
	    (namesz == 5 && strcmp((char *)&nbuf[noff], "CORE") == 0)) {
		os_style = OS_STYLE_SVR4;
	} 

	if ((namesz == 8 && strcmp((char *)&nbuf[noff], "FreeBSD") == 0)) {
		os_style = OS_STYLE_FREEBSD;
	}

	if ((namesz >= 11 && strncmp((char *)&nbuf[noff], "NetBSD-CORE", 11)
	    == 0)) {
		os_style = OS_STYLE_NETBSD;
	}

	if (os_style != -1 && (*flags & FLAGS_DID_CORE_STYLE) == 0) {
		if (file_printf(ms, ", %s-style", os_style_names[os_style])
		    == -1)
			return 1;
		*flags |= FLAGS_DID_CORE_STYLE;
		*flags |= os_style;
	}

	switch (os_style) {
	case OS_STYLE_NETBSD:
		if (type == NT_NETBSD_CORE_PROCINFO) {
			char sbuf[512];
			struct NetBSD_elfcore_procinfo pi;
			memset(&pi, 0, sizeof(pi));
			memcpy(&pi, nbuf + doff, descsz);

			if (file_printf(ms, ", from '%.31s', pid=%u, uid=%u, "
			    "gid=%u, nlwps=%u, lwp=%u (signal %u/code %u)",
			    file_printable(sbuf, sizeof(sbuf),
			    CAST(char *, pi.cpi_name)),
			    elf_getu32(swap, (uint32_t)pi.cpi_pid),
			    elf_getu32(swap, pi.cpi_euid),
			    elf_getu32(swap, pi.cpi_egid),
			    elf_getu32(swap, pi.cpi_nlwps),
			    elf_getu32(swap, (uint32_t)pi.cpi_siglwp),
			    elf_getu32(swap, pi.cpi_signo),
			    elf_getu32(swap, pi.cpi_sigcode)) == -1)
				return 1;

			*flags |= FLAGS_DID_CORE;
			return 1;
		}
		break;

	default:
		if (type == NT_PRPSINFO && *flags & FLAGS_IS_CORE) {
			size_t i, j;
			unsigned char c;
			/*
			 * Extract the program name.  We assume
			 * it to be 16 characters (that's what it
			 * is in SunOS 5.x and Linux).
			 *
			 * Unfortunately, it's at a different offset
			 * in various OSes, so try multiple offsets.
			 * If the characters aren't all printable,
			 * reject it.
			 */
			for (i = 0; i < NOFFSETS; i++) {
				unsigned char *cname, *cp;
				size_t reloffset = prpsoffsets(i);
				size_t noffset = doff + reloffset;
				size_t k;
				for (j = 0; j < 16; j++, noffset++,
				    reloffset++) {
					/*
					 * Make sure we're not past
					 * the end of the buffer; if
					 * we are, just give up.
					 */
					if (noffset >= size)
						goto tryanother;

					/*
					 * Make sure we're not past
					 * the end of the contents;
					 * if we are, this obviously
					 * isn't the right offset.
					 */
					if (reloffset >= descsz)
						goto tryanother;

					c = nbuf[noffset];
					if (c == '\0') {
						/*
						 * A '\0' at the
						 * beginning is
						 * obviously wrong.
						 * Any other '\0'
						 * means we're done.
						 */
						if (j == 0)
							goto tryanother;
						else
							break;
					} else {
						/*
						 * A nonprintable
						 * character is also
						 * wrong.
						 */
						if (!isprint(c) || isquote(c))
							goto tryanother;
					}
				}
				/*
				 * Well, that worked.
				 */

				/*
				 * Try next offsets, in case this match is
				 * in the middle of a string.
				 */
				for (k = i + 1 ; k < NOFFSETS; k++) {
					size_t no;
					int adjust = 1;
					if (prpsoffsets(k) >= prpsoffsets(i))
						continue;
					for (no = doff + prpsoffsets(k);
					     no < doff + prpsoffsets(i); no++)
						adjust = adjust
						         && isprint(nbuf[no]);
					if (adjust)
						i = k;
				}

				cname = (unsigned char *)
				    &nbuf[doff + prpsoffsets(i)];
				for (cp = cname; *cp && isprint(*cp); cp++)
					continue;
				/*
				 * Linux apparently appends a space at the end
				 * of the command line: remove it.
				 */
				while (cp > cname && isspace(cp[-1]))
					cp--;
				if (file_printf(ms, ", from '%.*s'",
				    (int)(cp - cname), cname) == -1)
					return 1;
				*flags |= FLAGS_DID_CORE;
				return 1;

			tryanother:
				;
			}
		}
		break;
	}
#endif
	return 0;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
	if (sz == 0) { fclose(f); return 0; }

	/* HEAP-allocate the note-descriptor buffer with EXACTLY the input's
	 * byte length -- no padding -- so `size` below is precisely the
	 * allocation size and any read do_core_note performs past it lands
	 * in ASAN's redzone (that is the whole bug: the vulnerable loop
	 * has no check against this boundary). */
	unsigned char *nbuf = (unsigned char *)malloc((size_t)sz);
	if (!nbuf) { fclose(f); return 0; }
	size_t n = fread(nbuf, 1, (size_t)sz, f);
	fclose(f);
	if (n != (size_t)sz) { free(nbuf); return 0; }

	struct magic_set ms;
	memset(&ms, 0, sizeof(ms));

	/* Fixed "path-selecting" arguments: pick the NT_PRPSINFO / FLAGS_IS_CORE
	 * branch (the one the fix patches) on a 64-bit note. descsz=64 is wide
	 * enough to admit the "Linux (short name)" and "FreeBSD, 64-bit"
	 * candidate offsets (40, 16) the vulnerable loop actually scans. The
	 * ENTIRE bug is then a function of the buffer bytes + its length, which
	 * is exactly what argv[1]'s content determines. */
	int flags = FLAGS_IS_CORE;
	(void)do_core_note(&ms, nbuf, NT_PRPSINFO, /*swap=*/0,
	    /*namesz=*/0, /*descsz=*/64, /*noff=*/0, /*doff=*/0,
	    &flags, (size_t)n, ELFCLASS64);

	free(nbuf);
	return 0;
}

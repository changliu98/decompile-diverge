/* ============================================================================
 * cve_842a533a -- direct-call harness for libtiff `TIFFReadEncodedStrip()`
 * (libtiff/tif_read.c), CVE-2016-10266 / CWE-369 divide-by-zero.
 *
 * Baseline (case.json): dedup_token
 * "TIFFReadEncodedStrip--TIFFReadContigStripData--TIFFReadData", summary
 * "UndefinedBehaviorSanitizer: undefined-behavior tif_read.c:350:21 in".
 * `TIFFReadEncodedStrip` IS the bundle's crash_site/target function, and the
 * faulting instruction is INSIDE it (no callee needs to be embedded):
 *
 *     rowsperstrip=td->td_rowsperstrip;
 *     if (rowsperstrip>td->td_imagelength)
 *         rowsperstrip=td->td_imagelength;
 *     stripsperplane=((td->td_imagelength+rowsperstrip-1)/rowsperstrip);  // L349
 *     stripinplane=(strip%stripsperplane);                               // L350 <-- crash
 *
 * Root cause (fix commit 438274f938e046d33cb0e1230b41da32ffe223e1): when
 * `td_imagelength` is large enough (> 2^31, e.g. the classic PoC value
 * 0xFFFFFFFF) and `rowsperstrip == td_imagelength` (so the preceding clamp
 * is a no-op and rowsperstrip stays nonzero), the uint32 addition
 * `td_imagelength + rowsperstrip - 1` overflows and wraps to a value SMALLER
 * than `rowsperstrip`, so the division at L349 truncates to exactly 0 --
 * `stripsperplane` is 0 (rowsperstrip itself is NOT 0), and the very next
 * line's `strip % stripsperplane` is a division-by-zero (SIGFPE / UBSAN
 * `integer-divide-by-zero`). The fix replaces the raw division with the
 * overflow-safe `TIFFhowmany_32_maxuint_compat`.
 *
 * FAITHFULNESS / what is VERBATIM vs. glue:
 *   - TIFFReadEncodedStrip() (target/original_function.c): embedded 100%
 *     VERBATIM below, byte-for-byte, no logic/name/signature changes.
 *   - TIFFCheckRead() (source_code/libtiff/tif_read.c): embedded VERBATIM.
 *     It gates entry to the target function (`if (!TIFFCheckRead(tif,0))
 *     return -1;`) but is NOT itself the fault site.
 *   - Every OTHER external symbol TIFFReadEncodedStrip()'s body references
 *     (TIFFErrorExt, TIFFVStripSize, TIFFReadRawStrip1, TIFFReverseBits,
 *     TIFFFillStrip, tif->tif_decodestrip, tif->tif_postdecode) sits
 *     strictly AFTER both the divide-by-zero line (triggering inputs crash
 *     first) and the function's own `if (stripsize==0) return -1;` early
 *     exit, which this harness's TIFFVStripSize stub always takes (safe
 *     inputs return cleanly there without ever calling them). They are
 *     supplied as trivial, real-signature, provably-never-invoked stubs
 *     purely so the verbatim body links; see the per-stub comments.
 *   - `struct tiff` / `TIFFDirectory` below are MINIMAL subsets of the real
 *     structs (libtiff/tiffiop.h, libtiff/tif_dir.h) -- only the fields
 *     TIFFReadEncodedStrip()/TIFFCheckRead() actually dereference -- using
 *     the REAL field names (td_nstrips, td_rowsperstrip, td_imagelength,
 *     td_compression, td_fillorder, tif_dir, tif_flags, tif_mode,
 *     tif_clientdata, tif_name, tif_postdecode, tif_decodestrip). The real
 *     `struct tiff` has ~50 more fields irrelevant to this function; a
 *     one-function harness cannot (and per the task brief should not) carry
 *     the whole opaque type.
 *   - main() reads argv[1] into a HEAP buffer (malloc) -- the attacker-
 *     controlled bytes never touch the stack/globals -- and decodes it as
 *     four little-endian uint32 fields (this harness's own compact encoding
 *     for {strip, td_nstrips, td_rowsperstrip, td_imagelength}; there is no
 *     TIFF file parser here because the direct call bypasses the real
 *     caller's IFD-parsing entirely, exactly as instructed). It then builds
 *     a minimal real TIFF/TIFFDirectory pair from those fields (tif_mode=
 *     O_RDONLY, tif_flags=0 i.e. not tiled/not mapped, mirroring a normal
 *     open-for-read handle) and calls TIFFReadEncodedStrip() ONCE, directly.
 * ============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>   /* O_RDONLY / O_WRONLY -- real open-mode constants tif_mode compares against */

/* ---------------------------------------------------------------------- *
 * Minimal REAL libtiff primitive typedefs (libtiff/tiff.h, libtiff/tiffio.h)
 * ---------------------------------------------------------------------- */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef long                tmsize_t;   /* tiffio.h: typedef TIFF_SSIZE_T tmsize_t (ssize_t-class -> `long` on LP64) */
typedef void*               thandle_t;  /* tiffio.h, non-Win32 branch */

#define COMPRESSION_NONE   1            /* libtiff/tiff.h */

struct tiff;
typedef struct tiff TIFF;

/* ---- Minimal REAL TIFFDirectory (libtiff/tif_dir.h) -- only the fields
 * TIFFReadEncodedStrip() dereferences (td->td_nstrips/td_rowsperstrip/
 * td_imagelength/td_compression/td_fillorder), real names. ---- */
typedef struct {
	uint16  td_compression;
	uint16  td_fillorder;
	uint32  td_rowsperstrip;
	uint32  td_imagelength;
	uint32  td_nstrips;
} TIFFDirectory;

/* ---- method-pointer typedefs (libtiff/tiffiop.h) -- only the two the
 * target function's own body names. Both call sites sit in code this
 * corpus never reaches at runtime (see file header), but the types must
 * exist to compile the verbatim body. ---- */
typedef void (*TIFFPostMethod)(TIFF* tif, uint8* buf, tmsize_t cc);
typedef int  (*TIFFCodeMethod)(TIFF* tif, uint8* buf, tmsize_t size, uint16 sample);

/* ---- Minimal REAL `struct tiff` (libtiff/tiffiop.h) -- only the fields
 * TIFFReadEncodedStrip()/TIFFCheckRead() dereference, real names/values. ---- */
struct tiff {
	char*            tif_name;         /* name of open file */
	int              tif_mode;         /* open mode (O_*) */
	uint32           tif_flags;
	#define TIFF_NOBITREV    0x00100U  /* inhibit bit reversal logic */
	#define TIFF_ISTILED     0x00400U  /* file is tile, not strip-based */
	#define TIFF_MAPPED      0x00800U  /* file is mapped into memory */
	#define TIFF_NOREADRAW   0x20000U  /* skip reading of raw uncompressed image data */
	TIFFDirectory    tif_dir;          /* internal rep of current directory */
	thandle_t        tif_clientdata;   /* callback parameter */
	TIFFPostMethod   tif_postdecode;   /* post decoding routine */
	TIFFCodeMethod   tif_decodestrip;  /* strip decoding routine */
};

#define isTiled(tif)       (((tif)->tif_flags & TIFF_ISTILED) != 0)
#define isMapped(tif)      (((tif)->tif_flags & TIFF_MAPPED) != 0)
#define isFillOrder(tif,o) (((tif)->tif_flags & (o)) != 0)

/* ---------------------------------------------------------------------- *
 * Link-only stubs for every external symbol TIFFReadEncodedStrip()'s body
 * references besides TIFFCheckRead(). Each is provably unreached at
 * runtime by every input in this corpus (see file header); real signatures
 * from tiffio.h/tif_read.c.
 * ---------------------------------------------------------------------- */
void TIFFErrorExt(thandle_t fd, const char* module, const char* fmt, ...)
{
	/* REACHABLE (safe inputs that hit the `strip>=td_nstrips` early-return
	 * print this); a plain diagnostic print, not the fault site. */
	va_list ap;
	(void) fd;
	va_start(ap, fmt);
	fprintf(stderr, "%s: ", module ? module : "(null)");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

tmsize_t TIFFVStripSize(TIFF* tif, uint32 nrows)
{
	/* STUB: real formula (tif_strip.c) lives strictly downstream of the
	 * fault and is never load-bearing for this corpus -- triggering inputs
	 * crash at the `strip % stripsperplane` line ABOVE this call; safe
	 * inputs reach it with a valid nonzero stripsperplane, and this stub's
	 * 0 return sends them straight into the target function's OWN
	 * `if (stripsize==0) return ((tmsize_t)(-1));` early exit, so no input
	 * in this corpus depends on TIFFVStripSize's real value. */
	(void) tif; (void) nrows;
	return 0;
}

int TIFFFillStrip(TIFF* tif, uint32 strip)
{
	(void) tif; (void) strip;
	return 0; /* never invoked -- see TIFFVStripSize note (dead past the stripsize==0 return) */
}

static int TIFFReadRawStrip1(TIFF* tif, uint32 strip, void* buf, tmsize_t size, const char* module);
static int TIFFReadRawStrip1(TIFF* tif, uint32 strip, void* buf, tmsize_t size, const char* module)
{
	(void) tif; (void) strip; (void) buf; (void) size; (void) module;
	return 0; /* never invoked -- see TIFFVStripSize note */
}

void TIFFReverseBits(uint8* cp, tmsize_t n)
{
	(void) cp; (void) n; /* never invoked -- see TIFFVStripSize note */
}

/* ---- TIFFCheckRead(): VERBATIM from source_code/libtiff/tif_read.c.
 * Gates entry to the target function; NOT itself the fault site. ---- */
static int
TIFFCheckRead(TIFF* tif, int tiles)
{
	if (tif->tif_mode == O_WRONLY) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name, "File not open for reading");
		return (0);
	}
	if (tiles ^ isTiled(tif)) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name, tiles ?
		    "Can not read tiles from a stripped image" :
		    "Can not read scanlines from a tiled image");
		return (0);
	}
	return (1);
}

/* ==========================================================================
 * TARGET FUNCTION -- VERBATIM from target/original_function.c, byte-for-
 * byte, no logic/name/signature changes. (noinline forward decl only, so
 * -O1 keeps its own ASAN/UBSAN backtrace frame; the definition below carries
 * no attribute of its own.)
 * ========================================================================== */
tmsize_t TIFFReadEncodedStrip(TIFF*, uint32, void*, tmsize_t) __attribute__((noinline));

tmsize_t
TIFFReadEncodedStrip(TIFF* tif, uint32 strip, void* buf, tmsize_t size)
{
	static const char module[] = "TIFFReadEncodedStrip";
	TIFFDirectory *td = &tif->tif_dir;
	uint32 rowsperstrip;
	uint32 stripsperplane;
	uint32 stripinplane;
	uint16 plane;
	uint32 rows;
	tmsize_t stripsize;
	if (!TIFFCheckRead(tif,0))
		return((tmsize_t)(-1));
	if (strip>=td->td_nstrips)
	{
		TIFFErrorExt(tif->tif_clientdata,module,
		    "%lu: Strip out of range, max %lu",(unsigned long)strip,
		    (unsigned long)td->td_nstrips);
		return((tmsize_t)(-1));
	}
	/*
	 * Calculate the strip size according to the number of
	 * rows in the strip (check for truncated last strip on any
	 * of the separations).
	 */
	rowsperstrip=td->td_rowsperstrip;
	if (rowsperstrip>td->td_imagelength)
		rowsperstrip=td->td_imagelength;
	stripsperplane=((td->td_imagelength+rowsperstrip-1)/rowsperstrip);
	stripinplane=(strip%stripsperplane);
	plane=(uint16)(strip/stripsperplane);
	rows=td->td_imagelength-stripinplane*rowsperstrip;
	if (rows>rowsperstrip)
		rows=rowsperstrip;
	stripsize=TIFFVStripSize(tif,rows);
	if (stripsize==0)
		return((tmsize_t)(-1));

    /* shortcut to avoid an extra memcpy() */
    if( td->td_compression == COMPRESSION_NONE &&
        size!=(tmsize_t)(-1) && size >= stripsize &&
        !isMapped(tif) &&
        ((tif->tif_flags&TIFF_NOREADRAW)==0) )
    {
        if (TIFFReadRawStrip1(tif, strip, buf, stripsize, module) != stripsize)
            return ((tmsize_t)(-1));

        if (!isFillOrder(tif, td->td_fillorder) &&
            (tif->tif_flags & TIFF_NOBITREV) == 0)
            TIFFReverseBits(buf,stripsize);

        (*tif->tif_postdecode)(tif,buf,stripsize);
        return (stripsize);
    }

	if ((size!=(tmsize_t)(-1))&&(size<stripsize))
		stripsize=size;
	if (!TIFFFillStrip(tif,strip))
		return((tmsize_t)(-1));
	if ((*tif->tif_decodestrip)(tif,buf,stripsize,plane)<=0)
		return((tmsize_t)(-1));
	(*tif->tif_postdecode)(tif,buf,stripsize);
	return(stripsize);
}

/* ==========================================================================
 * Harness main()
 *
 * Input encoding (this harness's own, since a direct call bypasses the real
 * TIFF-file/IFD parser entirely): 16 raw bytes, four little-endian uint32
 * fields --
 *     [0:4)   strip
 *     [4:8)   td_nstrips
 *     [8:12)  td_rowsperstrip
 *     [12:16) td_imagelength
 * Short/absent fields read as 0 (never touches attacker bytes out of range).
 * ========================================================================== */
static uint32
rd_u32le(const uint8 *p, size_t n, size_t off)
{
	uint32 v = 0;
	if (off + 4 <= n) {
		v  =  (uint32) p[off];
		v |= ((uint32) p[off + 1]) << 8;
		v |= ((uint32) p[off + 2]) << 16;
		v |= ((uint32) p[off + 3]) << 24;
	}
	return v;
}

int
main(int argc, char** argv)
{
	FILE *f;
	long sz;
	uint8 *data;
	TIFF tif;
	void *buf;
	uint32 strip;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "rb");
	if (!f) { perror("fopen"); return 1; }
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	sz = ftell(f);
	if (sz < 0) sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* HEAP buffer for the attacker-controlled bytes (ASAN redzone directly
	 * past the real bytes) -- never a stack/global buffer. */
	data = (uint8*) malloc(sz > 0 ? (size_t) sz : 1);
	if (!data) { fclose(f); return 1; }
	if (sz > 0 && fread(data, 1, (size_t) sz, f) != (size_t) sz) {
		free(data); fclose(f); return 1;
	}
	fclose(f);

	memset(&tif, 0, sizeof(tif));
	tif.tif_name = (char*) "vb_dc";
	tif.tif_mode = O_RDONLY;      /* open-for-read handle */
	tif.tif_flags = 0;            /* not tiled, not mapped, bit-rev enabled */
	tif.tif_clientdata = NULL;
	strip                        = rd_u32le(data, (size_t) sz, 0);
	tif.tif_dir.td_nstrips       = rd_u32le(data, (size_t) sz, 4);
	tif.tif_dir.td_rowsperstrip  = rd_u32le(data, (size_t) sz, 8);
	tif.tif_dir.td_imagelength   = rd_u32le(data, (size_t) sz, 12);
	tif.tif_dir.td_compression   = COMPRESSION_NONE;
	tif.tif_dir.td_fillorder     = 0;

	/* Output buffer param -- also HEAP; unreached before either the crash
	 * or the function's own early return in every input this corpus uses. */
	buf = malloc(64);
	if (!buf) { free(data); return 1; }

	TIFFReadEncodedStrip(&tif, strip, buf, (tmsize_t) -1);

	free(buf);
	free(data);
	return 0;
}

/* ============================================================================
 * cve_20603f33 -- direct-call harness for libtiff `readContigStripsIntoBuffer()`
 * (tools/tiffcrop.c), CWE-787 heap-buffer-overflow WRITE.
 *
 * Fix commit 9657bbe3cdce4aaa90e07d50c1c70ae52da0ba6a (tools/tiffcrop.c):
 *     -                bufp += bytes_read;
 *     +                bufp += stripsize;
 * ChangeLog: "fix readContigStripsIntoBuffer() in -i (ignore) mode so that the
 * output buffer is correctly incremented to avoid write outside bounds."
 *
 * ROOT CAUSE -- 100% inside readContigStripsIntoBuffer's OWN body: when a
 * strip read errors (TIFFReadEncodedStrip returns -1) and the global
 * `ignore` flag is set, the function does NOT return (the
 * `bytes_read < 0 && !ignore` guard is false), so it falls through to
 * `bufp += bytes_read;` -- advancing bufp by a NEGATIVE amount instead of by
 * the fixed per-strip `stripsize`. bufp is left BEFORE where it should be
 * (buf-1 if the very first strip errors); the NEXT strip's
 * TIFFReadEncodedStrip() call then writes a full `stripsize` bytes starting
 * at that too-early pointer, understepping the allocation
 * (`buf = _TIFFmalloc(TIFFStripSize(in) * TIFFNumberOfStrips(in))` at the
 * real call site, tools/tiffcrop.c ~L6065 `buffsize = stsize * nstrips;`)
 * and landing partly or wholly BEFORE buf[0] -- a heap-buffer-overflow WRITE
 * that ASAN reports inside the REAL, verbatim COMPRESSION_NONE codec's
 * `_TIFFmemcpy`, called from the REAL, verbatim TIFFReadEncodedStrip(),
 * called from readContigStripsIntoBuffer() itself.
 *
 * FAITHFULNESS -- every "real"/"VERBATIM" item below is copied byte-for-byte
 * from source_code/libtiff/*.c in THIS bundle; every "STUB" is documented
 * with exactly what real code path it replaces and why that path is
 * immaterial to (or a provably-dead branch of) the memory-safety bug under
 * test:
 *
 *   - readContigStripsIntoBuffer() (target/original_function.c): 100%
 *     VERBATIM, byte-for-byte, no logic/name/signature changes.
 *   - TIFFCheckRead(), TIFFReadEncodedStrip() (tif_read.c): 100% VERBATIM.
 *     The write that manifests the bug happens INSIDE the real, verbatim
 *     TIFFReadEncodedStrip() -> (*tif->tif_decodestrip)() call chain,
 *     exactly as it would in the shipped library.
 *   - TIFFNumberOfStrips(), TIFFStripSize()/TIFFStripSize64(),
 *     TIFFVStripSize()/TIFFVStripSize64(), TIFFScanlineSize()/
 *     TIFFScanlineSize64() (tif_strip.c): 100% VERBATIM. These compute the
 *     exact `stripsize` value that BOTH readContigStripsIntoBuffer's own
 *     variable AND TIFFReadEncodedStrip's internal per-strip size use, so
 *     the write length below is the REAL library's number, not a harness
 *     guess.
 *   - DumpModeDecode() (tif_dumpmode.c), wired as tif->tif_decodestrip: 100%
 *     VERBATIM -- the REAL COMPRESSION_NONE ("dump mode") strip decoder
 *     (source_code/libtiff/tif_codec.c:84 registers TIFFInitDumpMode for
 *     COMPRESSION_NONE; TIFFInitDumpMode sets tif_decodestrip=
 *     DumpModeDecode). This is the function whose `_TIFFmemcpy(buf,
 *     tif->tif_rawcp, cc)` performs the actual out-of-bounds write.
 *   - _TIFFNoPostDecode() (tif_read.c), wired as tif->tif_postdecode: 100%
 *     VERBATIM (already a trivial no-op in the real library --
 *     TIFFDefaultDirectory's default assignment for non-swapped samples).
 *   - _TIFFmemcpy() (tif_unix.c), _TIFFMultiply32()/_TIFFMultiply64()
 *     (tif_aux.c), and the TIFFhowmany_32 / TIFFhowmany_32_maxuint_compat /
 *     TIFFhowmany_64 / TIFFhowmany8_64 / isUpSampled / isMapped /
 *     isFillOrder / isTiled macros (tiffiop.h): 100% VERBATIM (trivial,
 *     pulled in only because the verbatim functions above reference them).
 *   - TIFFError()/TIFFErrorExt() (tif_error.c): real signatures; bodies
 *     simplified to a direct vfprintf(stderr,...) instead of indirecting
 *     through the _TIFFerrorHandler(Ext) function-pointer chain (which
 *     exists purely so applications can install a custom handler --
 *     diagnostic output only, no memory-safety role either way).
 *   - TIFFFillStrip(): STUB. The REAL TIFFFillStrip (tif_read.c) reads raw
 *     strip bytes from an actual open file/mmap (td_stripoffset/
 *     td_stripbytecount, TIFFSeekProc/TIFFReadProc, _TIFFFillStriles's
 *     IFD-derived state) -- exactly the "elaborate object state" a
 *     direct-call harness bypasses by construction (there is no real file;
 *     the TIFF* is built from argv[1] alone, no IFD parsing). Its OUTPUT
 *     contract towards TIFFReadEncodedStrip/DumpModeDecode is narrow and is
 *     preserved exactly: on success, point tif_rawcp at raw bytes and set
 *     tif_rawcc to the available count; on failure, return 0 (mirrors the
 *     real function's own "Invalid strip byte count" / seek-error failure
 *     returns, which also return 0 without writing anything). The harness's
 *     per-strip fail-mask (parsed from argv[1], see main()) substitutes for
 *     a real file's StripByteCounts table / seek outcome -- this
 *     substitution is exactly what the task brief calls out as expected
 *     ("bypasses the real caller's IFD-parsing entirely"), not a shortcut
 *     through the actual bug: the bug is readContigStripsIntoBuffer's own
 *     `bufp += bytes_read` arithmetic, unchanged.
 *   - TIFFGetFieldDefaulted(): STUB. In readContigStripsIntoBuffer its
 *     return value is assigned to `rps`, which is NEVER READ AGAIN
 *     afterwards (dead store) -- provably no effect on control flow or
 *     memory safety, so a trivial stub that answers only the one tag this
 *     harness ever asks for (TIFFTAG_ROWSPERSTRIP) is exact, not an
 *     approximation.
 *   - TIFFReadRawStrip1(), TIFFReverseBits(): STUB, provably UNREACHED for
 *     every input in this corpus -- both calls sit inside the
 *     `size != (tmsize_t)(-1)` "shortcut" branch of TIFFReadEncodedStrip,
 *     and readContigStripsIntoBuffer ALWAYS calls
 *     TIFFReadEncodedStrip(...,-1) (target/original_function.c L17), so
 *     that branch's condition is always false and these bodies never
 *     execute.
 *   - `struct tiff` / `TIFFDirectory`: MINIMAL subsets of the real structs
 *     (tiffiop.h / tif_dir.h) -- only the fields the verbatim functions
 *     above dereference, real field names, real values (td_compression=
 *     COMPRESSION_NONE, td_planarconfig=PLANARCONFIG_CONTIG, td_photometric=
 *     a non-YCbCr value so TIFFVStripSize64/TIFFScanlineSize64 take their
 *     plain non-subsampled branch, tif_mode=O_RDONLY, tif_flags=0 i.e. not
 *     tiled/not mapped/bit-rev enabled -- a normal open-for-read,
 *     uncompressed handle).
 *   - main(): reads argv[1] into a HEAP buffer (malloc), decodes it with
 *     this harness's own compact encoding (there is no real TIFF-file/IFD
 *     parser here -- a direct call bypasses the real caller's parsing
 *     entirely, exactly as instructed) into {ignore, imagewidth,
 *     bitspersample, samplesperpixel, rowsperstrip, nstrips, per-strip
 *     fail-mask}, builds the minimal real TIFF/TIFFDirectory pair,
 *     HEAP-allocates `buf = malloc(TIFFStripSize(&tif) *
 *     TIFFNumberOfStrips(&tif))` -- the EXACT allocation-size formula the
 *     real caller uses (tools/tiffcrop.c ~L6065) with NO extra guard bytes,
 *     so ASAN's redzone sits immediately adjacent on both sides -- and
 *     calls readContigStripsIntoBuffer(&tif, buf) once, directly.
 * ============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>   /* O_RDONLY -- real open-mode constant tif_mode compares against */

/* ---------------------------------------------------------------------- *
 * Minimal REAL libtiff primitive typedefs (libtiff/tiff.h, libtiff/tiffio.h)
 * ---------------------------------------------------------------------- */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef int                 int32;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef long                tmsize_t;   /* tiffio.h: typedef TIFF_SSIZE_T tmsize_t (ssize_t-class -> `long` on LP64) */
typedef tmsize_t            tsize_t;    /* tiffio.h: typedef tmsize_t tsize_t */
typedef void*                thandle_t; /* tiffio.h, non-Win32 branch */
typedef uint32               ttag_t;    /* tiffio.h: directory tag */

/* ---- real constants (libtiff/tiff.h) ---- */
#define COMPRESSION_NONE        1   /* dump mode */
#define PLANARCONFIG_CONTIG     1   /* single image plane */
#define PLANARCONFIG_SEPARATE   2   /* separate planes of data */
#define PHOTOMETRIC_MINISBLACK  1
#define PHOTOMETRIC_YCBCR       6   /* !CCIR 601 */
#define TIFFTAG_ROWSPERSTRIP   278  /* rows per strip of data */
#define TIFFTAG_YCBCRSUBSAMPLING 530 /* !YCbCr subsampling factors -- referenced only by a
                                         provably-dead branch (td_photometric is never
                                         PHOTOMETRIC_YCBCR in this harness); kept for the
                                         verbatim body to compile unchanged. */

struct tiff;
typedef struct tiff TIFF;

/* ---- Minimal REAL TIFFDirectory (libtiff/tif_dir.h) -- only the fields
 * the verbatim functions below dereference, real names. ---- */
typedef struct {
	uint16  td_compression;
	uint16  td_fillorder;
	uint16  td_planarconfig;
	uint16  td_photometric;
	uint16  td_bitspersample;
	uint16  td_samplesperpixel;
	uint32  td_imagewidth;
	uint32  td_rowsperstrip;
	uint32  td_imagelength;
	uint32  td_nstrips;
} TIFFDirectory;

/* ---- method-pointer typedefs (libtiff/tiffiop.h) ---- */
typedef void (*TIFFPostMethod)(TIFF* tif, uint8* buf, tmsize_t cc);
typedef int  (*TIFFCodeMethod)(TIFF* tif, uint8* buf, tmsize_t size, uint16 sample);

/* ---- Minimal REAL `struct tiff` (libtiff/tiffiop.h) -- only the fields
 * the verbatim functions below dereference, real names/values. ---- */
struct tiff {
	char*            tif_name;         /* name of open file */
	int              tif_mode;         /* open mode (O_*) */
	uint32           tif_flags;
	#define TIFF_NOBITREV    0x00100U  /* inhibit bit reversal logic */
	#define TIFF_ISTILED     0x00400U  /* file is tile, not strip-based */
	#define TIFF_MAPPED      0x00800U  /* file is mapped into memory */
	#define TIFF_NOREADRAW   0x20000U  /* skip reading of raw uncompressed image data */
	#define TIFF_UPSAMPLED   0x04000U  /* library is doing data up-sampling */
	TIFFDirectory    tif_dir;          /* internal rep of current directory */
	thandle_t        tif_clientdata;   /* callback parameter */
	TIFFPostMethod   tif_postdecode;   /* post decoding routine */
	TIFFCodeMethod   tif_decodestrip;  /* strip decoding routine */
	uint8*           tif_rawcp;        /* current spot in raw data buffer */
	tmsize_t         tif_rawcc;        /* bytes unread from raw buffer */
	uint32           tif_row;          /* current scanline (DumpModeDecode's error print only) */
};

#define isTiled(tif)       (((tif)->tif_flags & TIFF_ISTILED) != 0)
#define isMapped(tif)      (((tif)->tif_flags & TIFF_MAPPED) != 0)
#define isFillOrder(tif,o) (((tif)->tif_flags & (o)) != 0)
#define isUpSampled(tif)   (((tif)->tif_flags & TIFF_UPSAMPLED) != 0)

/* ---- verbatim howmany helpers (libtiff/tiffiop.h) ---- */
#define TIFFhowmany_32(x, y) (((uint32)x < (0xffffffff - (uint32)(y-1))) ? \
			   ((((uint32)(x))+(((uint32)(y))-1))/((uint32)(y))) : \
			   0U)
#define TIFFhowmany_32_maxuint_compat(x, y) \
			   (((uint32)(x) / (uint32)(y)) + ((((uint32)(x) % (uint32)(y)) != 0) ? 1 : 0))
#define TIFFhowmany_64(x, y) ((((uint64)(x))+(((uint64)(y))-1))/((uint64)(y)))
#define TIFFhowmany8_64(x) (((x)&0x07)?((uint64)(x)>>3)+1:(uint64)(x)>>3)

/* ---------------------------------------------------------------------- *
 * Forward declarations (definition order below follows dependency order;
 * forward decls let the verbatim bodies reference each other freely, same
 * as the real headers do).
 * ---------------------------------------------------------------------- */
static void TIFFErrorExt(thandle_t fd, const char* module, const char* fmt, ...);
static void TIFFError(const char* module, const char* fmt, ...);
static uint32 _TIFFMultiply32(TIFF* tif, uint32 first, uint32 second, const char* where);
static uint64 _TIFFMultiply64(TIFF* tif, uint64 first, uint64 second, const char* where);
static void _TIFFmemcpy(void* d, const void* s, tmsize_t c);
static int TIFFGetFieldDefaulted(TIFF* tif, ttag_t tag, ...);
static int TIFFCheckRead(TIFF* tif, int tiles);
static uint32 TIFFNumberOfStrips(TIFF* tif);
static uint64 TIFFScanlineSize64(TIFF* tif);
static tmsize_t TIFFScanlineSize(TIFF* tif);
static uint64 TIFFVStripSize64(TIFF* tif, uint32 nrows);
static tmsize_t TIFFVStripSize(TIFF* tif, uint32 nrows);
static uint64 TIFFStripSize64(TIFF* tif);
static tmsize_t TIFFStripSize(TIFF* tif);
static int TIFFFillStrip(TIFF* tif, uint32 strip);
static tmsize_t TIFFReadRawStrip1(TIFF* tif, uint32 strip, void* buf, tmsize_t size, const char* module);
static void TIFFReverseBits(uint8* cp, tmsize_t n);
static int DumpModeDecode(TIFF* tif, uint8* buf, tmsize_t cc, uint16 s) __attribute__((noinline));
static void _TIFFNoPostDecode(TIFF* tif, uint8* buf, tmsize_t cc);
tmsize_t TIFFReadEncodedStrip(TIFF*, uint32, void*, tmsize_t) __attribute__((noinline));
static int readContigStripsIntoBuffer(TIFF*, uint8*) __attribute__((noinline));

/* ---------------------------------------------------------------------- *
 * project global -- tools/tiffcrop.c: `static int ignore = FALSE;` (its
 * `-i` command-line flag). readContigStripsIntoBuffer reads this exact
 * global; main() below sets it from argv[1]'s harness-own encoding.
 * ---------------------------------------------------------------------- */
static int ignore = 0;

/* ---------------------------------------------------------------------- *
 * TIFFErrorExt / TIFFError (tif_error.c) -- real signatures; diagnostic
 * output only (no memory-safety role). Real bodies indirect through the
 * _TIFFerrorHandler(Ext) function-pointer chain purely so an application
 * can install a custom handler; that indirection is elided here for a
 * direct fprintf, same as the sibling cve_842a533a harness.
 * ---------------------------------------------------------------------- */
static void
TIFFErrorExt(thandle_t fd, const char* module, const char* fmt, ...)
{
	va_list ap;
	(void) fd;
	va_start(ap, fmt);
	fprintf(stderr, "%s: ", module ? module : "(null)");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

static void
TIFFError(const char* module, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "%s: ", module ? module : "(null)");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

/* ---- _TIFFMultiply32/_TIFFMultiply64 (tif_aux.c): VERBATIM ---- */
static uint32
_TIFFMultiply32(TIFF* tif, uint32 first, uint32 second, const char* where)
{
	uint32 bytes = first * second;

	if (second && bytes / second != first) {
		TIFFErrorExt(tif->tif_clientdata, where, "Integer overflow in %s", where);
		bytes = 0;
	}

	return bytes;
}

static uint64
_TIFFMultiply64(TIFF* tif, uint64 first, uint64 second, const char* where)
{
	uint64 bytes = first * second;

	if (second && bytes / second != first) {
		TIFFErrorExt(tif->tif_clientdata, where, "Integer overflow in %s", where);
		bytes = 0;
	}

	return bytes;
}

/* ---- _TIFFmemcpy (tif_unix.c): VERBATIM ---- */
static void
_TIFFmemcpy(void* d, const void* s, tmsize_t c)
{
	memcpy(d, s, (size_t) c);
}

/* ---- TIFFGetFieldDefaulted: STUB (see file header). readContigStripsIntoBuffer's
 * only real call site is `TIFFGetFieldDefaulted(in, TIFFTAG_ROWSPERSTRIP, &rps)`
 * whose result (`rps`) is a dead store (never read again) -- this answers
 * that one tag with the real td_rowsperstrip (exact, not approximate) and
 * is otherwise inert; TIFFVStripSize64/TIFFScanlineSize64's
 * TIFFTAG_YCBCRSUBSAMPLING call site is provably unreached (td_photometric
 * is never PHOTOMETRIC_YCBCR here). ---- */
static int
TIFFGetFieldDefaulted(TIFF* tif, ttag_t tag, ...)
{
	va_list ap;
	va_start(ap, tag);
	if (tag == TIFFTAG_ROWSPERSTRIP) {
		uint32 *out = va_arg(ap, uint32*);
		if (out) *out = tif->tif_dir.td_rowsperstrip;
	}
	va_end(ap);
	return 1;
}

/* ---- TIFFCheckRead() (tif_read.c): VERBATIM. Gates entry to
 * TIFFReadEncodedStrip; not itself the fault site. ---- */
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

/* ---- TIFFNumberOfStrips() (tif_strip.c): VERBATIM ---- */
static uint32
TIFFNumberOfStrips(TIFF* tif)
{
	TIFFDirectory *td = &tif->tif_dir;
	uint32 nstrips;

	nstrips = (td->td_rowsperstrip == (uint32) -1 ? 1 :
	     TIFFhowmany_32(td->td_imagelength, td->td_rowsperstrip));
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE)
		nstrips = _TIFFMultiply32(tif, nstrips, (uint32)td->td_samplesperpixel,
		    "TIFFNumberOfStrips");
	return (nstrips);
}

/* ---- TIFFScanlineSize64()/TIFFScanlineSize() (tif_strip.c): VERBATIM.
 * readContigStripsIntoBuffer's own `scanline_size` local uses this value
 * only in a diagnostic %lu print (provably inert for memory safety), but
 * TIFFVStripSize64() below also calls it and THAT result IS load-bearing
 * (it is `stripsize`, the actual write length), so the real formula is
 * kept, not stubbed. ---- */
static uint64
TIFFScanlineSize64(TIFF* tif)
{
	static const char module[] = "TIFFScanlineSize64";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 scanline_size;
	if (td->td_planarconfig==PLANARCONFIG_CONTIG)
	{
		if ((td->td_photometric==PHOTOMETRIC_YCBCR)&&
		    (td->td_samplesperpixel==3)&&
		    (!isUpSampled(tif)))
		{
			uint16 ycbcrsubsampling[2];
			uint16 samplingblock_samples;
			uint32 samplingblocks_hor;
			uint64 samplingrow_samples;
			uint64 samplingrow_size;
			if(td->td_samplesperpixel!=3)
			{
                            TIFFErrorExt(tif->tif_clientdata,module,
                                         "Invalid td_samplesperpixel value");
                            return 0;
			}
			TIFFGetFieldDefaulted(tif,TIFFTAG_YCBCRSUBSAMPLING,
                                              ycbcrsubsampling+0,
                                              ycbcrsubsampling+1);
			if (((ycbcrsubsampling[0]!=1)&&(ycbcrsubsampling[0]!=2)&&(ycbcrsubsampling[0]!=4)) ||
			    ((ycbcrsubsampling[1]!=1)&&(ycbcrsubsampling[1]!=2)&&(ycbcrsubsampling[1]!=4)))
			{
                            TIFFErrorExt(tif->tif_clientdata,module,
                                         "Invalid YCbCr subsampling");
                            return 0;
			}
			samplingblock_samples = ycbcrsubsampling[0]*ycbcrsubsampling[1]+2;
			samplingblocks_hor = TIFFhowmany_32(td->td_imagewidth,ycbcrsubsampling[0]);
			samplingrow_samples = _TIFFMultiply64(tif,samplingblocks_hor,samplingblock_samples,module);
			samplingrow_size = TIFFhowmany_64(_TIFFMultiply64(tif,samplingrow_samples,td->td_bitspersample,module),8);
			scanline_size = (samplingrow_size/ycbcrsubsampling[1]);
		}
		else
		{
			uint64 scanline_samples;
			scanline_samples=_TIFFMultiply64(tif,td->td_imagewidth,td->td_samplesperpixel,module);
			scanline_size=TIFFhowmany_64(_TIFFMultiply64(tif,scanline_samples,td->td_bitspersample,module),8);
		}
	}
	else
        {
		scanline_size=TIFFhowmany_64(_TIFFMultiply64(tif,td->td_imagewidth,td->td_bitspersample,module),8);
        }
        if (scanline_size == 0)
        {
                TIFFErrorExt(tif->tif_clientdata,module,"Computed scanline size is zero");
                return 0;
        }
	return(scanline_size);
}
static tmsize_t
TIFFScanlineSize(TIFF* tif)
{
	static const char module[] = "TIFFScanlineSize";
	uint64 m;
	tmsize_t n;
	m=TIFFScanlineSize64(tif);
	n=(tmsize_t)m;
	if ((uint64)n!=m) {
		TIFFErrorExt(tif->tif_clientdata,module,"Integer arithmetic overflow");
		n=0;
	}
	return(n);
}

/* ---- TIFFVStripSize64()/TIFFVStripSize() (tif_strip.c): VERBATIM. This is
 * the function that computes the ACTUAL per-strip write length both the
 * outer `stripsize` (readContigStripsIntoBuffer) and TIFFReadEncodedStrip's
 * own internal per-strip `stripsize` use. ---- */
static uint64
TIFFVStripSize64(TIFF* tif, uint32 nrows)
{
	static const char module[] = "TIFFVStripSize64";
	TIFFDirectory *td = &tif->tif_dir;
	if (nrows==(uint32)(-1))
		nrows=td->td_imagelength;
	if ((td->td_planarconfig==PLANARCONFIG_CONTIG)&&
	    (td->td_photometric == PHOTOMETRIC_YCBCR)&&
	    (!isUpSampled(tif)))
	{
		uint16 ycbcrsubsampling[2];
		uint16 samplingblock_samples;
		uint32 samplingblocks_hor;
		uint32 samplingblocks_ver;
		uint64 samplingrow_samples;
		uint64 samplingrow_size;
		if(td->td_samplesperpixel!=3)
		{
			TIFFErrorExt(tif->tif_clientdata,module,
			    "Invalid td_samplesperpixel value");
			return 0;
		}
		TIFFGetFieldDefaulted(tif,TIFFTAG_YCBCRSUBSAMPLING,ycbcrsubsampling+0,
		    ycbcrsubsampling+1);
		if ((ycbcrsubsampling[0] != 1 && ycbcrsubsampling[0] != 2 && ycbcrsubsampling[0] != 4)
		    ||(ycbcrsubsampling[1] != 1 && ycbcrsubsampling[1] != 2 && ycbcrsubsampling[1] != 4))
		{
			TIFFErrorExt(tif->tif_clientdata,module,
				     "Invalid YCbCr subsampling (%dx%d)",
				     ycbcrsubsampling[0],
				     ycbcrsubsampling[1] );
			return 0;
		}
		samplingblock_samples=ycbcrsubsampling[0]*ycbcrsubsampling[1]+2;
		samplingblocks_hor=TIFFhowmany_32(td->td_imagewidth,ycbcrsubsampling[0]);
		samplingblocks_ver=TIFFhowmany_32(nrows,ycbcrsubsampling[1]);
		samplingrow_samples=_TIFFMultiply64(tif,samplingblocks_hor,samplingblock_samples,module);
		samplingrow_size=TIFFhowmany8_64(_TIFFMultiply64(tif,samplingrow_samples,td->td_bitspersample,module));
		return(_TIFFMultiply64(tif,samplingrow_size,samplingblocks_ver,module));
	}
	else
		return(_TIFFMultiply64(tif,nrows,TIFFScanlineSize64(tif),module));
}
static tmsize_t
TIFFVStripSize(TIFF* tif, uint32 nrows)
{
	static const char module[] = "TIFFVStripSize";
	uint64 m;
	tmsize_t n;
	m=TIFFVStripSize64(tif,nrows);
	n=(tmsize_t)m;
	if ((uint64)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

/* ---- TIFFStripSize64()/TIFFStripSize() (tif_strip.c): VERBATIM ---- */
static uint64
TIFFStripSize64(TIFF* tif)
{
	TIFFDirectory* td = &tif->tif_dir;
	uint32 rps = td->td_rowsperstrip;
	if (rps > td->td_imagelength)
		rps = td->td_imagelength;
	return (TIFFVStripSize64(tif, rps));
}
static tmsize_t
TIFFStripSize(TIFF* tif)
{
	static const char module[] = "TIFFStripSize";
	uint64 m;
	tmsize_t n;
	m=TIFFStripSize64(tif);
	n=(tmsize_t)m;
	if ((uint64)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

/* ---------------------------------------------------------------------- *
 * TIFFFillStrip(): STUB (see file header "TIFFFillStrip(): STUB" note).
 * g_fail_mask/g_stripbuf are the harness's own per-strip "raw data
 * availability" plan, substituting for a real file's StripByteCounts /
 * seek outcome. main() parses g_fail_mask straight from argv[1].
 * ---------------------------------------------------------------------- */
static uint32 g_fail_mask = 0;      /* bit i set => strip i's raw data is unavailable
                                        (simulated seek/read error) */
static uint8  g_stripbuf[4096];     /* backing bytes for tif_rawcp; contents are never
                                        inspected by readContigStripsIntoBuffer (only
                                        copied into the caller's buffer), and 4096 bytes
                                        comfortably covers every stripsize this harness's
                                        input encoding can produce (max 16 width * 4
                                        samples * 16 bps/8 = 128 B/row * 8 rows/strip =
                                        1024 B/strip). */

static int
TIFFFillStrip(TIFF* tif, uint32 strip)
{
	if (strip < 32 && (g_fail_mask & (1u << strip))) {
		return 0;   /* simulated read/seek error: writes nothing, mirrors the
		             * real TIFFFillStrip's own failure return */
	}
	tif->tif_rawcp = g_stripbuf;
	tif->tif_rawcc = (tmsize_t) sizeof(g_stripbuf);  /* "plenty available"; DumpModeDecode
	                                                     below only ever consumes exactly
	                                                     the `cc` bytes it is asked for */
	return 1;
}

/* ---- TIFFReadRawStrip1(), TIFFReverseBits(): STUB, provably UNREACHED
 * (see file header). ---- */
static tmsize_t
TIFFReadRawStrip1(TIFF* tif, uint32 strip, void* buf, tmsize_t size, const char* module)
{
	(void) tif; (void) strip; (void) buf; (void) size; (void) module;
	return 0; /* never invoked -- see file header */
}

static void
TIFFReverseBits(uint8* cp, tmsize_t n)
{
	(void) cp; (void) n; /* never invoked -- see file header */
}

/* ==========================================================================
 * DumpModeDecode() (tif_dumpmode.c): VERBATIM. The REAL COMPRESSION_NONE
 * strip decoder (tif_codec.c:84 `{ "None", COMPRESSION_NONE, TIFFInitDumpMode }`;
 * TIFFInitDumpMode sets tif_decodestrip=DumpModeDecode). Its `_TIFFmemcpy`
 * is the statement that performs the actual out-of-bounds WRITE when bufp
 * has been mis-advanced by readContigStripsIntoBuffer.
 * ========================================================================== */
static int
DumpModeDecode(TIFF* tif, uint8* buf, tmsize_t cc, uint16 s)
{
	static const char module[] = "DumpModeDecode";
	(void) s;
	if (tif->tif_rawcc < cc) {
		TIFFErrorExt(tif->tif_clientdata, module,
"Not enough data for scanline %lu, expected a request for at most %lld bytes, got a request for %lld bytes",
		             (unsigned long) tif->tif_row,
		             (signed long long) tif->tif_rawcc,
		             (signed long long) cc);
		return (0);
	}
	/*
	 * Avoid copy if client has setup raw
	 * data buffer to avoid extra copy.
	 */
	if (tif->tif_rawcp != buf)
		_TIFFmemcpy(buf, tif->tif_rawcp, cc);
	tif->tif_rawcp += cc;
	tif->tif_rawcc -= cc;
	return (1);
}

/* ---- _TIFFNoPostDecode() (tif_read.c): VERBATIM (already a no-op) ---- */
static void
_TIFFNoPostDecode(TIFF* tif, uint8* buf, tmsize_t cc)
{
    (void) tif; (void) buf; (void) cc;
}

/* ==========================================================================
 * TIFFReadEncodedStrip() -- VERBATIM from source_code/libtiff/tif_read.c,
 * byte-for-byte, no logic/name/signature changes (only the trailing
 * `__attribute__((noinline))` forward declaration above, so -O1 keeps its
 * own ASAN backtrace frame; the definition itself carries no attribute).
 * ========================================================================== */
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
	stripsperplane= TIFFhowmany_32_maxuint_compat(td->td_imagelength, rowsperstrip);
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
 * TARGET FUNCTION -- readContigStripsIntoBuffer(), VERBATIM from
 * target/original_function.c, byte-for-byte, no logic/name/signature
 * changes (checked below by the caller's byte-substring build; only the
 * `__attribute__((noinline))` forward declaration above is harness glue).
 * ========================================================================== */
static int readContigStripsIntoBuffer (TIFF* in, uint8* buf)
{
        uint8* bufp = buf;
        int32  bytes_read = 0;
        uint32 strip, nstrips   = TIFFNumberOfStrips(in);
        uint32 stripsize = TIFFStripSize(in);
        uint32 rows = 0;
        uint32 rps = TIFFGetFieldDefaulted(in, TIFFTAG_ROWSPERSTRIP, &rps);
        tsize_t scanline_size = TIFFScanlineSize(in);

        if (scanline_size == 0) {
                TIFFError("", "TIFF scanline size is zero!");    
                return 0;
        }

        for (strip = 0; strip < nstrips; strip++) {
                bytes_read = TIFFReadEncodedStrip (in, strip, bufp, -1);
                rows = bytes_read / scanline_size;
                if ((strip < (nstrips - 1)) && (bytes_read != (int32)stripsize))
                        TIFFError("", "Strip %d: read %lu bytes, strip size %lu",
                                  (int)strip + 1, (unsigned long) bytes_read,
                                  (unsigned long)stripsize);

                if (bytes_read < 0 && !ignore) {
                        TIFFError("", "Error reading strip %lu after %lu rows",
                                  (unsigned long) strip, (unsigned long)rows);
                        return 0;
                }
                bufp += bytes_read;
        }

        return 1;
}

/* ==========================================================================
 * Harness main()
 *
 * Input encoding (this harness's own, since a direct call bypasses the real
 * TIFF-file/IFD parser entirely): 28 raw bytes, seven little-endian uint32
 * fields --
 *     [0:4)   ignore_flag        (nonzero => global `ignore` = 1)
 *     [4:8)   imagewidth_raw     -> imagewidth = (raw % 16) + 1        [1,16]
 *     [8:12)  bps_raw            -> bitspersample = (raw % 2) ? 16 : 8
 *     [12:16) spp_raw            -> samplesperpixel = (raw % 4) + 1    [1,4]
 *     [16:20) rowsperstrip_raw   -> rowsperstrip = (raw % 8) + 1       [1,8]
 *     [20:24) nstrips_raw        -> nstrips = (raw % 4) + 2            [2,5]
 *     [24:28) fail_mask          -> g_fail_mask (bit i = strip i unavailable)
 * imagelength is DERIVED as rowsperstrip*nstrips (an exact multiple, so
 * every strip -- including the last -- is full-size; this harness never
 * exercises libtiff's separate "truncated last strip" arithmetic, which is
 * unrelated to this CVE). Short/absent fields read as 0.
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
	uint8 *buf;
	uint32 imagewidth, bps, spp, rowsperstrip, nstrips, imagelength;
	tmsize_t stripsize;
	size_t buffsize;

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

	ignore = (rd_u32le(data, (size_t) sz, 0) != 0);

	imagewidth   = (rd_u32le(data, (size_t) sz, 4)  % 16) + 1;
	bps          = (rd_u32le(data, (size_t) sz, 8)  % 2)  ? 16 : 8;
	spp          = (rd_u32le(data, (size_t) sz, 12) % 4)  + 1;
	rowsperstrip = (rd_u32le(data, (size_t) sz, 16) % 8)  + 1;
	nstrips      = (rd_u32le(data, (size_t) sz, 20) % 4)  + 2;
	g_fail_mask  =  rd_u32le(data, (size_t) sz, 24);
	imagelength  = rowsperstrip * nstrips;

	memset(&tif, 0, sizeof(tif));
	tif.tif_name = (char*) "vb_dc";
	tif.tif_mode = O_RDONLY;       /* open-for-read handle */
	tif.tif_flags = 0;             /* not tiled, not mapped, bit-rev enabled */
	tif.tif_clientdata = NULL;
	tif.tif_postdecode = _TIFFNoPostDecode;
	tif.tif_decodestrip = DumpModeDecode;
	tif.tif_rawcp = NULL;
	tif.tif_rawcc = 0;
	tif.tif_row = 0;

	tif.tif_dir.td_compression     = COMPRESSION_NONE;
	tif.tif_dir.td_fillorder       = 0;
	tif.tif_dir.td_planarconfig    = PLANARCONFIG_CONTIG;
	tif.tif_dir.td_photometric     = PHOTOMETRIC_MINISBLACK;  /* != YCBCR */
	tif.tif_dir.td_bitspersample   = (uint16) bps;
	tif.tif_dir.td_samplesperpixel = (uint16) spp;
	tif.tif_dir.td_imagewidth      = imagewidth;
	tif.tif_dir.td_rowsperstrip    = rowsperstrip;
	tif.tif_dir.td_imagelength     = imagelength;
	tif.tif_dir.td_nstrips         = TIFFNumberOfStrips(&tif);  /* keep in sync, like the
	                                                                real library's directory-
	                                                                read path does */

	stripsize = TIFFStripSize(&tif);
	if (stripsize <= 0) { free(data); return 0; }   /* degenerate encoding; not interesting */
	buffsize = (size_t) stripsize * (size_t) tif.tif_dir.td_nstrips;
	if (buffsize == 0) { free(data); return 0; }

	/* Output buffer -- also HEAP, sized EXACTLY like the real call site
	 * (tools/tiffcrop.c ~L6065 `buffsize = stsize * nstrips;`), no extra
	 * guard bytes, so ASAN's redzone sits immediately on both sides. */
	buf = (uint8*) malloc(buffsize);
	if (!buf) { free(data); return 1; }

	readContigStripsIntoBuffer(&tif, buf);

	free(buf);
	free(data);
	return 0;
}

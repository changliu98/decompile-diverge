/* cve_barebone direct-call harness for cve_ce7b7a26 (libtiff tools/tiffcrop.c)
 * Target: readContigStripsIntoBuffer
 * Bug class: CWE-787 heap-buffer-overflow WRITE.
 * Fixed by vadz/libtiff@9657bbe3cdce4aaa90e07d50c1c70ae52da0ba6a:
 *     -                bufp += bytes_read;
 *     +                bufp += stripsize;
 * ("fix readContigStripsIntoBuffer() in -i (ignore) mode so that the output buffer is
 *  correctly incremented to avoid write outside bounds"; bugzilla.maptools.org #2620).
 *
 * The bug: readContigStripsIntoBuffer() walks a caller-supplied buffer `buf` one strip at a
 * time via a cursor `bufp`, calling TIFFReadEncodedStrip(in, strip, bufp, -1) to decode each
 * strip directly into place, then advancing the cursor with
 *     bufp += bytes_read;
 * i.e. by however many bytes THAT call reports -- INCLUDING when it reports a negative error
 * sentinel. Ordinarily a negative bytes_read is caught immediately:
 *     if (bytes_read < 0 && !ignore) { ...; return 0; }
 * but tiffcrop's "-i" (ignore-errors) mode sets the file-scope flag `ignore = TRUE`
 * specifically so a corrupt strip does NOT abort the whole conversion -- and the very next
 * line unconditionally executes `bufp += bytes_read` anyway, walking the cursor BACKWARDS by
 * the sentinel's magnitude. If the FIRST strip's read fails, bufp retreats to `buf +
 * bytes_read` (bytes_read < 0) -- i.e. to a point strictly BEFORE the start of the heap
 * allocation -- and the very next strip's TIFFReadEncodedStrip() call decodes real strip data
 * straight into that out-of-bounds cursor: a heap-buffer-overflow write starting before
 * `buf`'s left redzone. The bug is entirely in this function's own bookkeeping of a value a
 * callee legitimately returned; TIFFReadEncodedStrip itself never inspects or bounds-checks
 * `buf` (it never has anywhere to get the allocation's size from), exactly as in real libtiff.
 *
 * Everything below TIFFReadEncodedStrip's real declared signature (tiffio.h) is a minimal
 * stand-in: it writes exactly `stripsize` bytes at the pointer it is given (a real strip
 * decode's effect) unless the harness has told it (via a global set from the input bytes) that
 * THIS strip index should simulate a decode failure, in which case it returns a negative
 * sentinel and writes nothing at all -- so the eventual out-of-bounds write is provably
 * produced by readContigStripsIntoBuffer's own cursor arithmetic, never by the stub itself
 * doing anything unsafe on its own. TIFFNumberOfStrips/TIFFStripSize/TIFFScanlineSize/
 * TIFFGetFieldDefaulted are harmless accessors (their real bodies just read TIFFGetField-style
 * directory state out of the opaque TIFF*, which readContigStripsIntoBuffer never touches
 * directly) so they return harness-controlled constants; TIFFGetFieldDefaulted's own result
 * (rps) is dead in this function (immediately shadowed, never read again) so its varargs out-
 * parameter is never written. TIFFError is diagnostic-only (never affects bufp/buf) so it is a
 * silent no-op that does not touch its varargs.
 *
 * Expected crash stack (dedup-relevant frames): TIFFReadEncodedStrip -- readContigStripsIntoBuffer
 * -- main. TIFFReadEncodedStrip is marked noinline and readContigStripsIntoBuffer is invoked
 * through a volatile function pointer in main() so neither can be inlined away and disappear
 * from the ASAN backtrace -- pure codegen hints, no behavior change, and neither touches the
 * target function's own source bytes.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real libtiff base typedefs (libtiff/tiff.h, libtiff/tiffio.h; TIFF_* resolved to their
 * standard x86-64/LP64 `configure` values: uint8=unsigned char, int32=int, uint32=unsigned int,
 * TIFF_SSIZE_T=long) ---- */
typedef unsigned char  uint8;    /* tiff.h:69  typedef TIFF_UINT8_T  uint8;  */
typedef int             int32;   /* tiff.h:74  typedef TIFF_INT32_T  int32;  */
typedef unsigned int   uint32;   /* tiff.h:75  typedef TIFF_UINT32_T uint32; */
typedef long          tmsize_t;  /* tiffio.h:67 typedef TIFF_SSIZE_T tmsize_t; */
typedef tmsize_t        tsize_t; /* tiffio.h:77 typedef tmsize_t tsize_t; -- i/o size in bytes */

/* tiffio.h:40 -- TIFF stays exactly this opaque: readContigStripsIntoBuffer only ever holds a
 * TIFF* and passes it through to the API calls below, never dereferencing it (identical to how
 * tiffcrop.c itself only ever sees this forward declaration, never libtiff's private
 * tiffiop.h). */
typedef struct tiff TIFF;

/* tools/tiffcrop.c:158-159 (verbatim, same file the target is drawn from) */
#define	TRUE	1
#define	FALSE	0

/* tiff.h:231 (verbatim) */
#define	TIFFTAG_ROWSPERSTRIP		278	/* rows per strip of data */

/* tools/tiffcrop.c:447 (verbatim): the file-scope flag the target function reads directly.
 * Real tiffcrop sets this TRUE only when the user passes "-i" on the command line
 * (tools/tiffcrop.c:1676: `case 'i': ignore = TRUE;`); the harness reproduces that exact
 * assignment from an input byte instead of argv parsing. */
static int    ignore = FALSE;		/* if true, ignore read errors */

/* ---- harness-controlled fake TIFF state --------------------------------------------------
 * TIFF* stays fully opaque (see above), so the state a real TIFF directory would carry lives
 * in plain harness globals instead of inside a (never-accessed) struct -- these are read by
 * the tiny stand-in accessors below, set from the input bytes in main() before the call. */
static uint32   g_nstrips;       /* TIFFNumberOfStrips() */
static uint32   g_stripsize;     /* TIFFStripSize(); also the byte count each successful
                                   * TIFFReadEncodedStrip() call actually writes */
static tmsize_t g_scanlinesize;  /* TIFFScanlineSize(); only needs to stay nonzero */
static int32    g_fail_strip;    /* strip index whose TIFFReadEncodedStrip() call simulates a
                                   * decode failure; -1 = no strip ever fails */
static int32    g_fail_ret;      /* the negative sentinel returned on that strip */

/* ---- TIFFNumberOfStrips: real signature `extern uint32 TIFFNumberOfStrips(TIFF*);`
 * (tiffio.h:465) ---- */
static uint32 TIFFNumberOfStrips(TIFF *tif)
{
    (void)tif;
    return g_nstrips;
}

/* ---- TIFFStripSize: real signature `extern tmsize_t TIFFStripSize(TIFF* tif);`
 * (tiffio.h:359) ---- */
static tmsize_t TIFFStripSize(TIFF *tif)
{
    (void)tif;
    return (tmsize_t)g_stripsize;
}

/* ---- TIFFScanlineSize: real signature `extern tmsize_t TIFFScanlineSize(TIFF* tif);`
 * (tiffio.h:355) ---- */
static tmsize_t TIFFScanlineSize(TIFF *tif)
{
    (void)tif;
    return g_scanlinesize;
}

/* ---- TIFFGetFieldDefaulted: real signature
 * `extern int TIFFGetFieldDefaulted(TIFF* tif, uint32 tag, ...);` (tiffio.h:349). In
 * readContigStripsIntoBuffer its result is assigned straight into `rps`, which is never read
 * again (dead), so the varargs out-parameter it would normally fill via va_arg is never
 * needed -- this stub is a faithful no-op that just reports "field present". ---- */
static int TIFFGetFieldDefaulted(TIFF *tif, uint32 tag, ...)
{
    (void)tif; (void)tag;
    return 1;
}

/* ---- TIFFError: real signature
 * `extern void TIFFError(const char*, const char*, ...) __attribute__((__format__
 * (__printf__,2,3))));` (tiffio.h:450). Diagnostic-only -- never affects bufp/buf -- so a
 * silent stub that does not touch the varargs is faithful. ---- */
static void TIFFError(const char *module, const char *fmt, ...)
{
    (void)module; (void)fmt;
}

/* ---- TIFFReadEncodedStrip: real signature
 * `extern tmsize_t TIFFReadEncodedStrip(TIFF* tif, uint32 strip, void* buf, tmsize_t size);`
 * (tiffio.h:466). noinline keeps it a distinct ASAN backtrace frame (see header comment). ---- */
__attribute__((noinline))
static tmsize_t TIFFReadEncodedStrip(TIFF *tif, uint32 strip, void *buf, tmsize_t size)
{
    (void)tif; (void)size;
    if ((int32)strip == g_fail_strip) {
        /* Simulate a real decode failure (e.g. a corrupt compressed strip): the decoder
         * detects the error and returns a negative sentinel WITHOUT having written anything --
         * the strictest, safest possible failure behavior, and exactly what exposes the
         * caller-side bug: readContigStripsIntoBuffer's own cursor arithmetic uses this
         * negative value regardless. */
        return (tmsize_t)g_fail_ret;
    }
    /* A real strip decode: writes exactly `stripsize` bytes at wherever the caller told it to
     * (bufp) and reports that count. TIFFReadEncodedStrip has no way to know how large the
     * caller's destination buffer actually is (real libtiff does not either) -- it simply
     * writes where it's told, exactly like here. */
    if (buf != NULL && g_stripsize > 0)
        memset(buf, 0xA5, (size_t)g_stripsize);
    return (tmsize_t)g_stripsize;
}

/* ============================================================================================
 * TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_ce7b7a26/target/original_function.c
 * ============================================================================================ */
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
/* ==== end verbatim target function ==== */

/* ---- driver ---------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) and derives readContigStripsIntoBuffer's
 * call parameters from its first 5 bytes:
 *   byte[0] bit0   -> ignore        (1 = tiffcrop's "-i" flag; 0 = normal abort-on-error mode)
 *   byte[1]        -> nstrips       = 2 + (byte1 % 15)                          (2..16)
 *   byte[2]        -> fail_strip    = -1 (never fails) if byte2==0xFF, else byte2 % nstrips
 *   byte[3]        -> fail_ret      = -(1 + byte3 % 8)                         (-1..-8)
 *   byte[4]        -> stripsize     = 16 + (byte4 % 64)                        (16..79)
 * A file shorter than 5 bytes can't carry a full header and exits clean.
 *
 * The output buffer is sized EXACTLY nstrips*stripsize bytes -- precisely enough for the FIXED
 * code's `bufp += stripsize` walk to land exactly on the end, so any deviation from that walk
 * (the unfixed `bufp += bytes_read` walk) is unambiguously a bounds violation, never an
 * artifact of an under/over-sized test buffer.
 */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 64; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 64; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

    size_t n = (size_t)fsz;
    unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!data) { fclose(fp); return 64; }
    size_t got = n ? fread(data, 1, n, fp) : 0;
    fclose(fp);

    if (got < 5) { free(data); return 0; }   /* too short for a full header -> trivially safe */

    ignore = (data[0] & 1) ? TRUE : FALSE;
    uint32 nstrips = 2u + (uint32)(data[1] % 15);                    /* 2..16 */
    unsigned char fail_mode = data[2];
    int32 fail_strip = (fail_mode == 0xFF) ? -1 : (int32)(fail_mode % nstrips);
    int32 fail_ret   = -(1 + (int32)(data[3] % 8));                  /* -1..-8 */
    uint32 stripsize = 16u + (uint32)(data[4] % 64);                 /* 16..79 */

    g_nstrips      = nstrips;
    g_stripsize    = stripsize;
    g_scanlinesize = 8;     /* nonzero constant; `rows` is dead downstream in the target */
    g_fail_strip   = fail_strip;
    g_fail_ret     = fail_ret;

    size_t bufsize = (size_t)nstrips * (size_t)stripsize;
    uint8 *buf = (uint8 *)malloc(bufsize ? bufsize : 1);   /* HEAP, ASAN-guarded */
    if (!buf) { free(data); return 64; }
    memset(buf, 0, bufsize);

    TIFF *in = (TIFF *)malloc(sizeof(long));   /* opaque handle, never dereferenced -- exactly
                                                 * like the real TIFF* tiffcrop.c holds from
                                                 * TIFFOpen() and only ever passes around */
    if (!in) { free(buf); free(data); return 64; }

    /* Call through a volatile function pointer so readContigStripsIntoBuffer (a `static`,
     * single-call-site function -- an easy inline target even at -O1) can't be folded into
     * main() and disappear as a distinct ASAN backtrace frame. Changes nothing about how it is
     * called or its own bytes. */
    int (*volatile vb_call)(TIFF *, uint8 *) = readContigStripsIntoBuffer;
    (void)vb_call(in, buf);

    /* Only reached on a SAFE run (a triggering run aborts inside the call above). */
    free(buf);
    free(in);
    free(data);
    return 0;
}

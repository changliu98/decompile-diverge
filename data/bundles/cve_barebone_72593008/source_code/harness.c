/* cve_barebone isolation harness for Pillow CVE (PcxDecode) -- CWE-125 heap-buffer-overflow READ.
 *
 * Target: ImagingPcxDecode (src/libImaging/PcxDecode.c).
 *
 * The bug (fixed in Pillow commit 93b22b846e0269ee9594ff71a72bec02d2bea8fd,
 * vulnerable at a09acd0decd8a87ccce939d5ff65dab59e7d365b): ImagingPcxDecode only guards
 * `state->xsize` against `state->bytes` for 1-bit ("1") images
 * (`state->xsize > state->bytes * 8`). For palette ("P") images the analogous guard is
 * MISSING:
 *   } else if (strcmp(im->mode, "P") == 0 && state->xsize > state->bytes) {
 *       state->errcode = IMAGING_CODEC_OVERRUN; return -1;
 *   }
 * `state->buffer` is malloc'd with exactly `state->bytes` bytes (src/decode.c:
 * `state->buffer = (UINT8*) malloc(state->bytes)`). Once a full scanline has been
 * unpacked into `state->buffer` (state->x >= state->bytes), ImagingPcxDecode calls
 * `state->shuffle(dst, state->buffer, state->xsize)` -- for a "P"/"P" (mode/rawmode)
 * image the real shuffler wired by ImagingFindUnpacker is `copy1`
 * (src/libImaging/Unpack.c): `memcpy(out, in, pixels)`. When xsize > bytes this memcpy
 * over-reads `state->buffer` by (xsize - bytes) bytes -- a heap-buffer-overflow READ
 * reached directly from inside ImagingPcxDecode's own control flow (the call target
 * `state->shuffle` and its argument `state->xsize` are both decided by
 * ImagingPcxDecode's own logic, exactly the call the missing guard exists to prevent).
 *
 * Everything below the target function is copied VERBATIM (real names) from the
 * vulnerable Pillow tree:
 *   - UINT8            (src/libImaging/ImPlatform.h, non-Windows branch: `#define UINT8
 *                        unsigned char`)
 *   - struct ImagingMemoryInstance / ImagingCodecStateInstance, IMAGING_MODE_LENGTH,
 *     IMAGING_CODEC_OVERRUN, ImagingShuffler   (src/libImaging/Imaging.h)
 *   - copy1                                    (src/libImaging/Unpack.c -- the real
 *                        "P"-mode shuffler: `{"P", "P", 8, copy1}` in the unpackers
 *                        table, `void copy1(UINT8*out,const UINT8*in,int pixels){
 *                        memcpy(out,in,pixels);}`)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- src/libImaging/ImPlatform.h (non-Windows branch) ---- */
typedef unsigned char UINT8;
typedef long Py_ssize_t;

/* ---- src/libImaging/Imaging.h ---- */
typedef struct ImagingMemoryInstance* Imaging;
typedef struct ImagingCodecStateInstance *ImagingCodecState;
typedef void (*ImagingShuffler)(UINT8* out, const UINT8* in, int pixels);

#define IMAGING_MODE_LENGTH 6+1 /* Band names ("1", "L", "P", "RGB", "RGBA", "CMYK", "YCbCr", "BGR;xy") */
#define IMAGING_CODEC_OVERRUN   -1

struct ImagingMemoryInstance {

    /* Format */
    char mode[IMAGING_MODE_LENGTH];     /* Band names */
    int type;
    int depth;
    int bands;
    int xsize;
    int ysize;

    /* Colour palette (for "P" images only) -- not exercised by this harness */
    void *palette;

    /* Data pointers */
    UINT8 **image8;
    int32_t **image32;

    /* Internals */
    char **image;       /* Actual raster data. */
    char *block;
    void *blocks;

    int pixelsize;      /* Size of a pixel, in bytes (1, 2 or 4) */
    int linesize;        /* Size of a line, in bytes (xsize * pixelsize) */

    void (*destroy)(Imaging im);
};

struct ImagingCodecStateInstance {
    int count;
    int state;
    int errcode;
    int x, y;
    int ystep;
    int xsize, ysize, xoff, yoff;
    ImagingShuffler shuffle;
    int bits, bytes;
    UINT8 *buffer;
    void *context;
    void *fd;   /* PyObject*, unused in this direct-call harness */
};

/* ---- src/libImaging/Unpack.c: the real "P"-mode (rawmode "P") shuffler, wired via
 *      ImagingFindUnpacker({"P","P",8,copy1}). ---- */
static void
copy1(UINT8* out, const UINT8* in, int pixels)
{
    /* L, P */
    memcpy(out, in, pixels);
}

/* ============================================================================ */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from                                  */
/*   data_cve/cve_72593008/target/original_function.c                            */
/* ============================================================================ */
__attribute__((noinline))
int
ImagingPcxDecode(Imaging im, ImagingCodecState state, UINT8* buf, Py_ssize_t bytes)
{
    UINT8 n;
    UINT8* ptr;

    if (strcmp(im->mode, "1") == 0 && state->xsize > state->bytes * 8) {
        state->errcode = IMAGING_CODEC_OVERRUN;
        return -1;
    }

    ptr = buf;

    for (;;) {

	if (bytes < 1)
	    return ptr - buf;

	if ((*ptr & 0xC0) == 0xC0) {

	    /* Run */
	    if (bytes < 2)
		return ptr - buf;

	    n = ptr[0] & 0x3F;

	    while (n > 0) {
		if (state->x >= state->bytes) {
		    state->errcode = IMAGING_CODEC_OVERRUN;
		    break;
		}
		state->buffer[state->x++] = ptr[1];
		n--;
	    }

	    ptr += 2; bytes -= 2;

	} else {

	    /* Literal */
	    state->buffer[state->x++] = ptr[0];
	    ptr++; bytes--;

	}

	if (state->x >= state->bytes) {
        if (state->bytes % state->xsize && state->bytes > state->xsize) {
            int bands = state->bytes / state->xsize;
            int stride = state->bytes / bands;
            int i;
            for (i=1; i< bands; i++) {  // note -- skipping first band
                memmove(&state->buffer[i*state->xsize],
                        &state->buffer[i*stride],
                        state->xsize);
            }
        }
	    /* Got a full line, unpack it */
	    state->shuffle((UINT8*) im->image[state->y + state->yoff] +
			   state->xoff * im->pixelsize, state->buffer,
			   state->xsize);

	    state->x = 0;

	    if (++state->y >= state->ysize) {
		/* End of file (errcode = 0) */
		return -1;
	    }
	}

    }
}/* ==================== end verbatim target function ====================== */

/* Direct-call driver.
 *
 * argv[1] is read into a HEAP buffer (malloc, ASAN-guarded) and fed AS-IS as
 * ImagingPcxDecode's `buf`/`bytes` (the PCX run-length-encoded scanline bytes --
 * exactly what a real PCX file's row data looks like on the wire; this is the
 * attacker-controlled input in the real CVE, reached via Image.open(...).load()).
 *
 * The Imaging/ImagingCodecState scaffolding fixed here is the harness's stand-in for
 * the image-header state a real PCX decode already has by the time ImagingPcxDecode is
 * invoked (xsize/mode/etc. come from the PCX header, parsed upstream in PcxImagePlugin.py
 * -- out of scope for this direct-call harness). It reproduces the exact vulnerable
 * configuration: mode "P" with xsize (64) > bytes (8), the state the missing guard was
 * supposed to reject. Each row's destination scratch (ROWCAP=256) is generously sized so
 * the shuffle's WRITE side never overflows -- this isolates the fault to the READ side of
 * the undersized `state->buffer`, exactly the CVE's heap-buffer-overflow read.
 */
#define XSIZE   64
#define YSIZE   4
#define NBYTES  8      /* state->buffer / state->bytes: deliberately < XSIZE */
#define ROWCAP  256    /* destination row scratch */

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 64;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 64; }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 64; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 64; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 64; }

    /* heap-allocate the raw input bytes (ASAN-instrumented) */
    UINT8 *buf = (UINT8 *)malloc(sz > 0 ? (size_t)sz : 1);
    if (!buf) { fclose(f); return 64; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    struct ImagingMemoryInstance im_inst;
    memset(&im_inst, 0, sizeof(im_inst));
    strcpy(im_inst.mode, "P");
    im_inst.type = 0;      /* IMAGING_TYPE_UINT8 */
    im_inst.bands = 1;
    im_inst.xsize = XSIZE;
    im_inst.ysize = YSIZE;
    im_inst.pixelsize = 1;
    im_inst.linesize = XSIZE;

    UINT8 *rows[YSIZE];
    for (int i = 0; i < YSIZE; i++) {
        rows[i] = (UINT8 *)malloc(ROWCAP);
        memset(rows[i], 0, ROWCAP);
    }
    im_inst.image = (char **)rows;

    Imaging im = &im_inst;

    struct ImagingCodecStateInstance state_inst;
    memset(&state_inst, 0, sizeof(state_inst));
    state_inst.xsize = XSIZE;
    state_inst.ysize = YSIZE;
    state_inst.xoff = 0;
    state_inst.yoff = 0;
    state_inst.x = 0;
    state_inst.y = 0;
    state_inst.bits = 8;
    state_inst.bytes = NBYTES;
    state_inst.shuffle = copy1;
    /* the under-sized scanline buffer whose size (NBYTES) < xsize (XSIZE) is exactly
     * the missing-guard condition the CVE fix rejects for mode "P" */
    state_inst.buffer = (UINT8 *)malloc(NBYTES);
    memset(state_inst.buffer, 0, NBYTES);

    ImagingCodecState state = &state_inst;

    int rc = ImagingPcxDecode(im, state, buf, (Py_ssize_t)n);
    fprintf(stderr, "ImagingPcxDecode rc=%d errcode=%d x=%d y=%d n=%zu\n",
            rc, state->errcode, state->x, state->y, n);

    free(state_inst.buffer);
    for (int i = 0; i < YSIZE; i++) free(rows[i]);
    free(buf);
    return 0;
}

/* cve_barebone harness -- rdesktop CVE-2018-8793 / process_bitmap_updates
 * heap-based buffer overflow READ (CWE-125): process_bitmap_updates() trusts the
 * attacker-declared width/height/bpp and reads that many "pixel" bytes off the wire with NO
 * check that the stream actually holds them -- the exact bug class this fix commit adds
 * `s_check_rem()` guards for throughout rdp.c/mcs.c/cliprdr.c/cssp.c, including this same
 * function's compressed-path sibling (process_bitmap_data()).
 *
 * Isolated reproduction: process_bitmap_updates() is called directly on a hand-built byte
 * stream shaped exactly like the wire encoding of a single TS_UPDATE_BITMAP_DATA rectangle
 * (num_updates=1, then left/top/right/bottom/width/height/bpp/compress/bufsize as
 * little-endian uint16 fields, then raw "pixel" bytes) -- the same bytes the real
 * process_secondary_order()/rdp_process_data() dispatch chain would have handed the function
 * off a live RDP TCP stream, with no server/network/UI involved.
 *
 * Bug: with compress==0 (uncompressed bitmap):
 *     bmpdata = xmalloc(width * height * Bpp);
 *     for (y = 0; y < height; y++)
 *         in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 * `in_uint8a(s,v,n)` is `{ memcpy(v,(s)->p,n); (s)->p += n; }` -- it memcpy()s straight out of
 * the stream buffer with no comparison against how many bytes are actually left. If the input
 * (the TS_UPDATE_BITMAP_DATA PDU payload) is shorter than width*height*Bpp bytes, the LAST
 * scanline's memcpy reads past the end of the heap buffer backing the stream.
 *
 * TRIGGER: width*height*Bpp bytes of pixel data are DECLARED (via width/height/bpp) but the
 *          input file supplies fewer -> heap-buffer-overflow READ on the very last scanline
 *          that needed the missing bytes.
 * SAFE:    the input file supplies the FULL width*height*Bpp bytes the declared dimensions
 *          need (loop reads exactly what's there) -> clean exit; or the compressed path is
 *          taken (bitmap_decompress() stub always reports failure -- a normal, non-crashing
 *          outcome for a corrupt/short compressed block).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <endian.h>

/* ---- real primitive types (types.h, verbatim names) ---- */
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef int RD_BOOL;
#ifndef True
#define True  (1)
#define False (0)
#endif

/* ---- endianness auto-detect (rdesktop.h, verbatim -- picks the SAME branch the real build
 * takes on x86/x86_64: L_ENDIAN defined, NEED_ALIGN not) ---- */
#if !defined(L_ENDIAN) && !defined(B_ENDIAN)
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define L_ENDIAN
#elif __BYTE_ORDER == __BIG_ENDIAN
#define B_ENDIAN
#else
#error Unknown endianness. Edit rdesktop.h.
#endif
#endif
#if !defined(NEED_ALIGN)
#if !(defined(__x86__) || defined(__x86_64__) || \
      defined(__AMD64__) || defined(_M_IX86) || \
      defined(__i386__))
#define NEED_ALIGN
#endif
#endif

/* ---- real stream type (stream.h, verbatim) ---- */
typedef struct stream
{
	unsigned char *p;
	unsigned char *end;
	unsigned char *data;
	unsigned int size;

	unsigned char *iso_hdr;
	unsigned char *mcs_hdr;
	unsigned char *sec_hdr;
	unsigned char *rdp_hdr;
	unsigned char *channel_hdr;

}
 *STREAM;

/* ---- real parsing macros actually used by process_bitmap_updates (stream.h, verbatim,
 * L_ENDIAN branch -- matches the real build on this platform) ---- */
#if defined(L_ENDIAN) && !defined(NEED_ALIGN)
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#else
#define in_uint16_le(s,v)	{ v = *((s)->p++); v += *((s)->p++) << 8; }
#endif
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- real logging enums (utils.h, verbatim) + a no-op logger: process_bitmap_updates only
 * ever uses logger() for diagnostic text, never on the crash path. ---- */
typedef enum log_level_t
{
	Debug = 0,
	Verbose,
	Warning,
	Error,
	Notice
} log_level_t;

typedef enum log_subject_t
{
	GUI = 0,
	Keyboard,
	Clipboard,
	Sound,
	Protocol,
	Graphics,
	Core,
	SmartCard,
	Disk
} log_subject_t;

static void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
}

/* ---- xmalloc / xfree (rdesktop.c, verbatim: malloc-or-exit / free) ---- */
static void *
xmalloc(int size)
{
	void *mem = malloc(size);
	if (mem == NULL)
	{
		exit(1);
	}
	return mem;
}

static void
xfree(void *mem)
{
	free(mem);
}

/* ---- ui_paint_bitmap (proto.h signature): real callee on the SUCCESS path only, incidental
 * to the bug (a real X11 draw call has no meaning outside the UI) -- minimal no-op stub. ---- */
void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x;
	(void) y;
	(void) cx;
	(void) cy;
	(void) width;
	(void) height;
	(void) data;
}

/* ---- bitmap_decompress (bitmap.c signature: `RD_BOOL bitmap_decompress(uint8 *output, int
 * width, int height, uint8 *input, int size, int Bpp)`): a deep, independently-patched ~700
 * line RLE decoder in bitmap.c, not on this bug's path (it is only reached on the COMPRESSED
 * branch, which none of the triggering inputs use) -- a minimal always-fails stub per the
 * task's "deep callee" carve-out; process_bitmap_updates already handles a False return (logs
 * a warning, moves on) so this is a faithful, common real-world outcome. ---- */
static RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output;
	(void) width;
	(void) height;
	(void) input;
	(void) size;
	(void) Bpp;
	return False;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
void
process_bitmap_updates(STREAM s)
{
	uint16 num_updates;
	uint16 left, top, right, bottom, width, height;
	uint16 cx, cy, bpp, Bpp, compress, bufsize, size;
	uint8 *data, *bmpdata;
	int i;

	logger(Protocol, Debug, "%s()", __func__);

	in_uint16_le(s, num_updates);

	for (i = 0; i < num_updates; i++)
	{
		in_uint16_le(s, left);
		in_uint16_le(s, top);
		in_uint16_le(s, right);
		in_uint16_le(s, bottom);
		in_uint16_le(s, width);
		in_uint16_le(s, height);
		in_uint16_le(s, bpp);
		Bpp = (bpp + 7) / 8;
		in_uint16_le(s, compress);
		in_uint16_le(s, bufsize);

		cx = right - left + 1;
		cy = bottom - top + 1;

		logger(Graphics, Debug,
		       "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
		       left, top, right, bottom, width, height, Bpp, compress);

		if (!compress)
		{
			int y;
			bmpdata = (uint8 *) xmalloc(width * height * Bpp);
			for (y = 0; y < height; y++)
			{
				in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)],
					  width * Bpp);
			}
			ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
			xfree(bmpdata);
			continue;
		}


		if (compress & 0x400)
		{
			size = bufsize;
		}
		else
		{
			in_uint8s(s, 2);	/* pad */
			in_uint16_le(s, size);
			in_uint8s(s, 4);	/* line_size, final_size */
		}
		in_uint8p(s, data, size);
		bmpdata = (uint8 *) xmalloc(width * height * Bpp);
		if (bitmap_decompress(bmpdata, width, height, data, size, Bpp))
		{
			ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
		}
		else
		{
			logger(Graphics, Warning,
			       "process_bitmap_updates(), failed to decompress bitmap");
		}

		xfree(bmpdata);
	}
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;

    /* HEAP input, ASAN-guarded: the raw bytes an attacker-controlled RDP server would have
     * sent as the TS_UPDATE_BITMAP_DATA payload of a Server Fast-Path (or slow-path) Update
     * PDU, already stripped of every outer header process_bitmap_updates() itself does not
     * parse. */
    unsigned char *data = (unsigned char *)malloc(n ? n : 1);
    if (!data) { fclose(fp); return 2; }
    size_t got = n ? fread(data, 1, n, fp) : 0;
    fclose(fp);

    struct stream st;
    memset(&st, 0, sizeof(st));
    st.data = data;
    st.p = data;
    st.end = data + got;
    st.size = (unsigned int)got;

    STREAM s = &st;

    /* volatile function pointer: forbid the compiler from proving the call away / folding
     * process_bitmap_updates into main's own frame despite __attribute__((noinline)). */
    void (* volatile fn)(STREAM) = process_bitmap_updates;
    fn(s);

    free(data);
    return 0;
}

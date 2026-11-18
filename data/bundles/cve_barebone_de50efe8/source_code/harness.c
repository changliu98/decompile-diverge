/* cve_barebone harness -- rdesktop CVE-2018-20178 / process_bitmap_updates
 * heap-buffer-overflow WRITE (CWE-787).
 *
 * Isolated reproduction: process_bitmap_updates() is called directly on a hand-built
 * TS_UPDATE_BITMAP_DATA byte stream (the real wire format the function itself parses via
 * in_uint16_le/in_uint8a). No RDP session, no UI, no networking -- just the attacker-
 * controlled bytes this function reads.
 *
 * TRIGGER: width*height*Bpp (all attacker uint16-derived) is computed with plain 32-bit
 *          `int` arithmetic and used BOTH as the xmalloc() size AND (via the per-row
 *          `(height-y-1)*(width*Bpp)` offset) as write offsets into that same buffer --
 *          both wrap at 2**32 identically, so choosing width/height/Bpp so the *malloc*
 *          size wraps to a hair less than one row's size makes the very FIRST row copy
 *          (y=0, offset = malloc_size - rowsize, algebraically exact) write `rowsize`
 *          bytes starting a small number of bytes BEFORE the undersized allocation ->
 *          heap-buffer-overflow (underflow) WRITE, caught by ASAN inside
 *          process_bitmap_updates itself (the memcpy is the inlined in_uint8a macro).
 * SAFE:    small width/height/bpp with no overflow (width*height*Bpp computed and
 *          allocated correctly) -> the same loop fills the buffer exactly, no OOB.
 *
 * Wire format read by process_bitmap_updates (all little-endian uint16, verbatim macros):
 *   num_updates
 *   per update (num_updates times): left top right bottom width height bpp compress bufsize
 *   if compress==0: width*Bpp bytes per row, `height` rows (bottom-up)  <- what we use
 *   else: [pad(2) size(2) pad(4)] or size=bufsize, then `size` bytes    <- never used here
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- real base typedefs (types.h, verbatim) ---- */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef int RD_BOOL;

/* ---- real STREAM struct (stream.h, verbatim) ---- */
typedef struct stream
{
	unsigned char *p;
	unsigned char *end;
	unsigned char *data;
	unsigned int size;

	/* Offsets of various headers */
	unsigned char *iso_hdr;
	unsigned char *mcs_hdr;
	unsigned char *sec_hdr;
	unsigned char *rdp_hdr;
	unsigned char *channel_hdr;

}
 *STREAM;

/* ---- real parsing macros process_bitmap_updates uses (stream.h, L_ENDIAN branch verbatim
 * -- this box is x86_64, little-endian) ---- */
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- real logging enums (utils.h, verbatim) -- logger() itself is incidental (never on
 * the crash path: the crash happens inside the memcpy, logger is just diagnostic chatter). */
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

void logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c; (void) lvl; (void) format;
}

/* ---- ui_paint_bitmap: real signature (proto.h, verbatim); incidental (UI paint, only
 * reached on the SAFE uncompressed-path-completes case) -- minimal no-op stub. ---- */
void ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x; (void) y; (void) cx; (void) cy; (void) width; (void) height; (void) data;
}

/* ---- bitmap_decompress: real signature (proto.h, verbatim); incidental -- only referenced
 * by the compressed branch, which none of this corpus's inputs take (compress is always 0),
 * so this stub is never actually invoked. Needed only so the verbatim function body (which
 * still contains that branch's text) compiles standalone. ---- */
RD_BOOL bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output; (void) width; (void) height; (void) input; (void) size; (void) Bpp;
	return 0;
}

/* ---- xmalloc/xfree: real bodies (rdesktop.c, verbatim). xmalloc is ON the crash path --
 * it performs the integer-overflow-undersized allocation the bug is about. ---- */
#define EX_UNAVAILABLE 69

/* noinline: at -O1 clang inlines this trivial wrapper into process_bitmap_updates and (even
 * under -fwrapv) the resulting cross-function view lets the array-index computation land on
 * a WILD multi-GB offset instead of the intended narrow underflow (empirically verified: with
 * xmalloc inlined the crash flips from "heap-buffer-overflow, 4 bytes to the left" to no
 * crash at all for the very same inputs). Keeping xmalloc a real, un-inlined call is what
 * makes the size argument materialize as the plain 32-bit wrapped value a real ABI boundary
 * forces -- i.e. this restores the natural (non-inlined) compilation a normal multi-TU build
 * of rdesktop would have had, where xmalloc lives in a separate object file. */
__attribute__((noinline))
void *
xmalloc(int size)
{
	void *mem = malloc(size);
	if (mem == NULL)
	{
		logger(Core, Error, "xmalloc, failed to allocate %d bytes", size);
		exit(EX_UNAVAILABLE);
	}
	return mem;
}

__attribute__((noinline))
void
xfree(void *mem)
{
	free(mem);
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
	size_t n = (size_t) ln;

	/* HEAP input buffer, ASAN-guarded -- this backs the STREAM the target reads from. */
	unsigned char *data = (unsigned char *) malloc(n ? n : 1);
	size_t got = n ? fread(data, 1, n, fp) : 0;
	fclose(fp);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = data;
	st.p = data;
	st.end = data + got;
	st.size = (unsigned int) got;

	STREAM s = &st;

	/* volatile function pointer: forbid the compiler from proving the call away / inlining
	 * process_bitmap_updates into main's own frame despite __attribute__((noinline)). */
	void (* volatile fn)(STREAM) = process_bitmap_updates;
	fn(s);

	free(data);
	return 0;
}

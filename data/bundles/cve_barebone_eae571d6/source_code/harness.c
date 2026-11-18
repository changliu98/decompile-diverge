/* cve_barebone direct-call harness for cve_eae571d6 (rdesktop, CVE-2018-8791)
 * Target: process_bitmap_updates  (rdp.c)
 * Bug class: 32-bit `int` overflow in `width * height * Bpp` -> undersized xmalloc() ->
 *   heap-buffer-overflow WRITE (CWE-787) in the very next in_uint8a() row copy.
 *
 * fix_commit 4dca546d04321a610c1835010b5dad85163b65e1 split this function into
 * process_bitmap_data() (per-update) + a thin process_bitmap_updates() loop, and inserted,
 * right before the vulnerable xmalloc():
 *     if (Bpp == 0 || width == 0 || height == 0) rdp_protocol_error(...);
 *     if ((RD_UINT32_MAX / Bpp) <= (width * height)) rdp_protocol_error(...);
 * i.e. exactly an overflow guard on `width * height * Bpp`. The pre-fix body pasted below
 * (target/original_function.c, byte-for-byte) has NEITHER check.
 *
 * width/height/bpp are each an independent attacker-controlled uint16 read straight off the
 * wire (NOT derived from left/top/right/bottom). Bpp = (bpp+7)/8. In the `!compress` branch:
 *     bmpdata = xmalloc(width * height * Bpp);            // int arithmetic, 32-bit
 *     for (y = 0; y < height; y++)
 *         in_uint8a(s, &bmpdata[(height-y-1) * (width*Bpp)], width*Bpp);
 * width*height*Bpp is plain `int` math (all three operands are uint16 -> promoted to int),
 * so it silently wraps mod 2^32. E.g. width=40000, height=53688, bpp=16 (Bpp=2):
 *   true product  = 40000 * 53688 * 2 = 4,295,040,000   (> 2^32 = 4,294,967,296)
 *   xmalloc size  = 4,295,040,000 mod 2^32               = 72,704        (small, succeeds)
 *   y=0 row copy  = &bmpdata[(53688-1)*(40000*2) mod2^32 as int32], length 80000
 *                 = &bmpdata[-7296]
 * i.e. the FIRST row of the FIRST (only) update already writes 80000 bytes starting 7296
 * bytes BEFORE the 72704-byte heap buffer -- ASAN: "heap-buffer-overflow ... WRITE of size
 * 80000 ... located 7296 bytes to the left of a 72704-byte region". Six (width,height,bpp)
 * triples with this same shape (found by brute-forcing the 32-bit-wraparound arithmetic
 * over uint16 width/height, Bpp<=(65535+7)/8) drive the 25 triggering inputs below.
 *
 * Only the UNCOMPRESSED branch (compress==0) is exercised by every crafted packet -- the
 * branch containing the bug, needing no bitmap_decompress() call. bitmap_decompress /
 * ui_paint_bitmap are still textually referenced by the pasted function body (the
 * compressed branch, and the paint call after either branch), so the C compiler needs them
 * declared + defined; both are minimal faithful stand-ins (never exercised at runtime by
 * any crafted input here), matching their real prototypes verbatim from proto.h.
 *
 * REQUIRES harness.flags = "-fwrapv" (read automatically by dc_batch.py/dc_try.py). Without
 * it, clang -O1 uses the "signed overflow is UB" license to compute the array index
 * `(height-y-1) * (width*Bpp)` for the pointer-offset calculation in WIDENED (true, non-
 * 32-bit-wrapped) arithmetic -- the resulting address lands ~2^32 bytes away in unmapped
 * memory (an uninformative ASAN SEGV) instead of the small over/underflow this comment
 * derives. -fwrapv just makes the ordinary two's-complement wraparound every mainstream
 * compiler gives this exact code at normal (non-UBSan) settings -- and what the real
 * CVE-2018-8791 exploit depends on -- the compiler's guaranteed semantics; it touches no
 * target-function byte and adds no check.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 -fwrapv harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sysexits.h>

#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69   /* rdesktop.h fallback, verbatim */
#endif

/* ---- types.h, verbatim names ---- */
typedef int RD_BOOL;
#define True  (1)
#define False (0)
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

/* ---- stream.h: struct stream + the L_ENDIAN && !NEED_ALIGN macro set (verbatim) --
 * configure.ac's AC_C_BIGENDIAN defines L_ENDIAN on this x86_64 little-endian target, and
 * x86_64 never needs NEED_ALIGN. ---- */
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

#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- utils.h enum names process_bitmap_updates's logger() calls reference (Protocol,
 * Debug, Graphics, Warning); logger() itself is incidental (pure diagnostics, not on the
 * crash path) -- stubbed as a no-op. ---- */
typedef enum log_level_t
{ Debug = 0, Verbose, Warning, Error, Notice } log_level_t;
typedef enum log_subject_t
{ GUI = 0, Keyboard, Clipboard, Sound, Protocol, Graphics, Core, SmartCard, Disk } log_subject_t;
static void
logger(log_subject_t s, log_level_t lvl, char *format, ...)
{
	(void) s;
	(void) lvl;
	(void) format;
}

/* ---- rdesktop.c, verbatim: the allocator wrappers process_bitmap_updates calls directly. ---- */
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

void
xfree(void *mem)
{
	free(mem);
}

/* ---- proto.h prototypes; minimal faithful stand-ins for the two real callees on the
 * COMPRESSED branch / post-copy paint call -- never exercised at runtime here (every
 * crafted packet sets compress=0) but textually referenced, so the compiler needs them
 * defined to link. ---- */
RD_BOOL
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

/* Faithful minimal stand-in for the real UI callback: it is the SOLE downstream consumer
 * of bmpdata's freshly-written bytes. A pure no-op stub (`(void) data;`) lets an optimizing
 * compiler prove the whole xmalloc/write-loop/xfree sequence has no observable effect and
 * delete it outright -- confirmed at -O1: it does, vaporizing the crash along with it (the
 * write loop containing the bug never executes). So this stub performs a REAL read over the
 * buffer, exactly like a renderer blitting it to screen would, sinking the result into a
 * `volatile` so the read itself can't be optimized away either -- that keeps the write loop
 * (and therefore the overflow) live across optimization without inventing any behavior the
 * real ui_paint_bitmap() doesn't also have (it does read every byte, to paint it). */
static volatile unsigned long vb_paint_sink;

void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x;
	(void) y;
	(void) cx;
	(void) cy;
	unsigned long sum = 0;
	long n = (long) width *(long) height;
	if (data != NULL)
	{
		for (long k = 0; k < n; k++)
			sum += data[k];
	}
	vb_paint_sink = sum;
}

/* ================= TARGET (verbatim, byte-for-byte target/original_function.c) =================
 * noinline so the crash keeps its own named frame in the ASAN backtrace (dc_batch requires
 * the target function name to appear in the stack). */
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
int
main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 2;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp)
	{
		perror("fopen");
		return 2;
	}
	if (fseek(fp, 0, SEEK_END) != 0)
	{
		fclose(fp);
		return 2;
	}
	long ln = ftell(fp);
	if (ln < 0)
		ln = 0;
	if (fseek(fp, 0, SEEK_SET) != 0)
	{
		fclose(fp);
		return 2;
	}
	size_t n = (size_t) ln;

	/* HEAP-allocate the raw wire packet, ASAN-guarded to EXACTLY its own length -- these
	 * bytes ARE process_bitmap_updates's own on-wire TS_UPDATE_BITMAP_DATA input, consumed
	 * VERBATIM (no reinterpretation): num_updates, then per update
	 * left/top/right/bottom/width/height/bpp/compress/bufsize, then (compress==0) the raw
	 * row bytes -- exactly the wire layout in_uint16_le/in_uint8a walk. */
	unsigned char *buf = (unsigned char *) malloc(n > 0 ? n : 1);
	if (!buf)
	{
		fclose(fp);
		return 2;
	}
	size_t got = n > 0 ? fread(buf, 1, n, fp) : 0;
	fclose(fp);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = buf;
	st.p = buf;
	st.end = buf + got;
	st.size = (unsigned int) got;

	/* volatile function pointer: forbid the compiler from proving the call away / folding
	 * process_bitmap_updates into main's own frame despite __attribute__((noinline)). */
	void (*volatile fn) (STREAM) = process_bitmap_updates;
	fn(&st);

	free(buf);
	return 0;
}

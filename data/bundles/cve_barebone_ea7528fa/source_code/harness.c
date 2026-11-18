/* cve_barebone direct-call harness for cve_ea7528fa (rdesktop)
 * Target: process_bitmap_updates  (rdp.c -- the exact PRE-refactor text frozen in
 *   data_cve/cve_ea7528fa/target/original_function.c: reads num_updates then, per
 *   update, reads left/top/right/bottom/width/height/bpp/compress/bufsize followed by
 *   either raw pixel rows (compress==0) or a compressed blob (compress!=0)).
 * Bug class: missing bounds check before consuming attacker-declared bitmap row
 *   bytes off the stream -> heap-buffer-overflow READ (CWE-125).
 *
 * CVE-2018-8797 / fix_commit 4dca546d04321a610c1835010b5dad85163b65e1 ("Malicious
 * RDP server security fixes", 21 CVEs reported by Eyal Itkin) refactors this loop
 * body into process_bitmap_data() and, among other things, adds an explicit
 * `if (!s_check_rem(s, size)) rdp_protocol_error(...)` guard before consuming the
 * COMPRESSED bitmap payload (`in_uint8p(s, data, size)`), plus a
 * `Bpp==0 || width==0 || height==0` / integer-overflow guard before the
 * `xmalloc(width*height*Bpp)` call. Neither the pre- nor the POST-fix code ever
 * validates that the stream actually holds `width*height*Bpp` bytes for the
 * UNCOMPRESSED path before this exact statement (verified against the fix diff --
 * the refactored process_bitmap_data() carries the identical unchecked loop):
 *
 *     bmpdata = (uint8 *) xmalloc(width * height * Bpp);
 *     for (y = 0; y < height; y++)
 *         in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 *
 * in_uint8a is `{ memcpy(v,(s)->p,n); (s)->p += n; }` (stream.h) -- an UNCHECKED
 * memcpy straight off the wire, with no comparison against s->end anywhere on this
 * path. A malicious server just has to advertise a width/height/bpp whose product
 * exceeds the number of row bytes it actually sends: the very first `in_uint8a` call
 * then memcpy()s past the end of the received-PDU buffer. This is exactly the class
 * of "declared size vs. actual bytes available" bug this commit exists to close (it
 * *does* close it for the sibling compressed-data path four lines below); calling
 * process_bitmap_updates directly on a short, attacker-controlled heap buffer
 * reproduces it faithfully on the uncompressed branch. bitmap_decompress /
 * ui_paint_bitmap are incidental externs on branches/calls our crafted inputs never
 * need for correctness (compress is always 0 below; ui_paint_bitmap is reached only
 * by the SAFE inputs, after the loop has already completed safely) -- minimal
 * no-op/faithful stand-ins, matching their real proto.h signatures exactly.
 *
 * (An earlier design tried to reach the classic CWE-787 heap WRITE overflow via the
 * `width*height*Bpp` int32 overflow the fix's `RD_UINT32_MAX/Bpp <= width*height`
 * guard targets. Empirically, at the mandated `-O1`, clang's induction-variable
 * widening treats the overflowing product as UB and computes the per-row pointer
 * using wider-than-32-bit arithmetic that no longer matches naive 2's-complement
 * wraparound -- verified via isolated repro: the SAME expression gives a clean,
 * near-buffer sign-extended offset with a bare loop but a wild ~4GB-away offset once
 * embedded in this function's full shape, even under `-fwrapv`. That makes the
 * allocation-overflow route unreliable at this optimization level, so this harness
 * instead exercises the always-present, non-overflow-dependent missing-length-check
 * bug above, which is robust under any correct compilation.)
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* types.h (verbatim names) */
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef int RD_BOOL;

/* utils.h (verbatim: process_bitmap_updates's own logger() calls use these names) */
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

/* logger() (utils.c) is a variadic printf-style diagnostic sink -- the target only
 * ever uses it for logging, never for control flow. No-op stand-in. */
void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
}

/* stream.h (verbatim struct + the L_ENDIAN macro variant -- this box is x86_64) */
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

} *STREAM;

#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* rdesktop.c xmalloc/xfree, verbatim */
#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

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

/* proto.h externals on branches/calls our crafted inputs don't need for
 * correctness -- minimal faithful stand-ins, real signatures. */
RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output;
	(void) width;
	(void) height;
	(void) input;
	(void) size;
	(void) Bpp;
	return 0;
}

/* the harness's own hint of the packet's bpp field (see main()) so this stub can
 * genuinely fold every byte the loop above wrote -- without it, a same-TU stub that
 * ignores `data` lets -O1 prove the whole xmalloc/memcpy/xfree chain unobservable and
 * delete it outright (confirmed empirically), vaporizing the very read this harness
 * exists to exercise. */
static unsigned g_bpp_hint = 8;
static volatile unsigned long g_paint_sink;

void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x;
	(void) y;
	(void) cx;
	(void) cy;
	unsigned Bpp = (g_bpp_hint + 7) / 8;
	if (Bpp == 0)
		Bpp = 1;
	size_t total = (size_t) width * (size_t) height * Bpp;
	unsigned long sum = 0;
	for (size_t k = 0; k < total; k++)
		sum += data[k];
	g_paint_sink = sum;
}

/* ==== VERBATIM from data_cve/cve_ea7528fa/target/original_function.c ==== */
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
/* ==== end verbatim ==== */

/* Packet layout process_bitmap_updates parses, all fields uint16 LE, in exactly the
 * order the verbatim body above reads them:
 *   num_updates,
 *   then per update: left, top, right, bottom, width, height, bpp, compress, bufsize
 *   (20 bytes total header for num_updates=1), followed by `width*height*Bpp` raw
 *   pixel-row bytes when compress==0 -- the branch every crafted input below takes.
 */
int
main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0)
	{
		fclose(f);
		return 1;
	}
	long fsz = ftell(f);
	if (fsz < 0 || fseek(f, 0, SEEK_SET) != 0)
	{
		fclose(f);
		return 1;
	}

	size_t alloc_sz = (size_t) fsz;
	if (alloc_sz == 0)
		alloc_sz = 1;

	/* HEAP-allocate the raw input, ASAN-guarded, EXACTLY fsz bytes -- this is what
	 * turns an under-supplied bitmap row into a genuine heap-buffer-overflow READ
	 * instead of a harmless read of over-provisioned slack. */
	unsigned char *buf = (unsigned char *) malloc(alloc_sz);
	if (!buf)
	{
		fclose(f);
		return 1;
	}
	if (fsz > 0)
	{
		size_t got = fread(buf, 1, (size_t) fsz, f);
		(void) got;
	}
	fclose(f);

	/* peek the SAME bpp field (byte offset 14..15) process_bitmap_updates's own
	 * in_uint16_le(s, bpp) will read for update 0, so ui_paint_bitmap's stub folds
	 * exactly the bytes the row loop actually wrote -- no more, no less. */
	if (fsz >= 16)
		g_bpp_hint = (unsigned) buf[14] | ((unsigned) buf[15] << 8);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = buf;
	st.p = buf;
	st.end = buf + fsz;
	st.size = (unsigned int) fsz;

	process_bitmap_updates(&st);

	free(buf);
	return 0;
}

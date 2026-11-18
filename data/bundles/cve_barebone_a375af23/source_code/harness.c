/* Direct-call ASAN harness for cve_a375af23 (rdesktop process_bitmap_updates).
 *
 * Root cause (rdesktop commit 4dca546d, "Process TS_BITMAP_DATA" split): the vulnerable
 * process_bitmap_updates() computes
 *     bmpdata = (uint8 *) xmalloc(width * height * Bpp);
 * with width/height/Bpp all attacker-controlled uint16-derived values, using plain 32-bit
 * `int` arithmetic (xmalloc takes `int size`). width*height*Bpp can overflow the 32-bit
 * `int` and wrap to a small positive value, so xmalloc() allocates a tiny buffer -- but the
 * very next uncompressed-row copy loop
 *     in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 * still writes width*Bpp bytes per row for `height` rows, overflowing the undersized heap
 * chunk (CWE-787 heap out-of-bounds WRITE). The fix (this commit) adds an explicit
 * `(RD_UINT32_MAX / Bpp) <= (width * height)` overflow guard before allocating.
 *
 * This harness supplies only the minimal real type/macro/stub surface
 * process_bitmap_updates() needs (verbatim from rdesktop's types.h/stream.h/utils.h/
 * proto.h/rdesktop.c) so it links and runs standalone; process_bitmap_updates() itself is
 * pasted byte-for-byte from data_cve/cve_a375af23/target/original_function.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sysexits.h>

#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

/* ---- types.h (verbatim names) ---- */
typedef int RD_BOOL;
#ifndef True
#define True  (1)
#define False (0)
#endif

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

/* ---- stream.h (verbatim struct + macros actually used by process_bitmap_updates) ---- */
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

#define s_check(s)		((s)->p <= (s)->end)
#define s_check_rem(s,n)	((s)->p + n <= (s)->end)
#define s_check_end(s)		((s)->p == (s)->end)
#define s_length(s)		((s)->end - (s)->data)
#define s_left(s)               ((s)->size - ((s)->p - (s)->data))

#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8(s,v)		v = *((s)->p++);
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- utils.h (verbatim enums + logger signature) ---- */
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

/* logger() itself only formats a diagnostic string -- it never touches bmpdata, so a
 * no-op body is a faithful stub for this incidental callee (matches the real signature). */
void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
}

/* ---- rdesktop.c (verbatim, real callees on the crash path: xmalloc/xfree) ---- */
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

/* ---- proto.h declarations for the two incidental callees; neither is reached on the
 * uncompressed-branch overflow we trigger (bitmap_decompress only runs for compress!=0,
 * ui_paint_bitmap only runs after a successful, non-overflowing fill) -- minimal faithful
 * stubs matching their real signatures exactly. ---- */
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

/* ================= target/original_function.c, byte-for-byte ================= */
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
/* ================================================================================ */

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
	long len = ftell(f);
	if (len < 0)
	{
		fclose(f);
		return 1;
	}
	fseek(f, 0, SEEK_SET);

	/* HEAP-allocate the raw input bytes (ASAN-guarded) -- the arguments to
	 * process_bitmap_updates are built directly out of this buffer via a STREAM. */
	uint8 *buf = (uint8 *) malloc((size_t) len > 0 ? (size_t) len : 1);
	if (!buf)
	{
		fclose(f);
		return 1;
	}
	size_t rd = fread(buf, 1, (size_t) len, f);
	fclose(f);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = buf;
	st.p = buf;
	st.end = buf + rd;
	st.size = (unsigned int) rd;

	process_bitmap_updates(&st);

	free(buf);
	return 0;
}

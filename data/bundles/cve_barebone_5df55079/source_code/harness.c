/* Direct-call ASAN harness for CVE-2018-8799 (rdesktop process_bitmap_updates).
 *
 * Bug: process_bitmap_updates() reads a TS_UPDATE_BITMAP_DATA PDU with the raw
 * in_uint16_le()/in_uint8a() stream macros (stream.h), none of which bounds-check
 * against the stream's actual end (s->end). In the uncompressed-bitmap branch
 * (`if (!compress) { ... }`) the per-scanline copy
 *     in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 * expands to a raw `memcpy(dst, s->p, width*Bpp)` with NO check that the stream
 * actually has width*Bpp bytes left before s->end. A server that advertises a
 * width/height/bpp implying more scanline data than it actually sent makes this
 * memcpy read past the end of the PDU buffer: heap-buffer-overflow READ (CWE-125).
 *
 * Fixed upstream by splitting process_bitmap_updates() into process_bitmap_data()
 * plus a Bpp/width/height sanity check and (for the compressed path) an explicit
 * s_check_rem() guard before consuming bitmap bytes
 * (commit 4dca546d04321a610c1835010b5dad85163b65e1, "process_bitmap_data(),
 * consume of bitmap data from stream would overrun").  Note the fix does NOT add
 * an s_check_rem() to the uncompressed in_uint8a() loop either -- it relies on the
 * width==0/height==0/Bpp==0 and (RD_UINT32_MAX/Bpp)<=(width*height) guards to stop
 * the malformed sizes that let this loop run past the PDU in the first place; this
 * harness reproduces the pre-fix function exactly, so none of those guards exist.
 *
 * This harness is a single self-contained C file: it copies process_bitmap_updates()
 * byte-for-byte from target/original_function.c, provides the real STREAM struct /
 * stream-macro / type / log-enum definitions from stream.h / types.h / utils.h, the
 * real xmalloc()/xfree() bodies from rdesktop.c, and no-op stubs for the UI/decompress
 * callees that are not on the crash path we exercise (ui_paint_bitmap, bitmap_decompress,
 * logger). main() reads argv[1] into a heap buffer allocated to EXACTLY the file's byte
 * length and points the STREAM's `end` at that exact boundary, so any macro that walks
 * `p` past `end` without checking is caught by ASan's redzone.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- types.h (verbatim subset) ---- */
typedef int RD_BOOL;
#define True  (1)
#define False (0)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

/* ---- utils.h (verbatim subset) ---- */
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

void logger(log_subject_t c, log_level_t lvl, char *format, ...);

/* ---- stream.h (verbatim subset: struct + the macros process_bitmap_updates uses) ---- */
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

#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8(s,v)		v = *((s)->p++);
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- proto.h (verbatim declarations for the callees process_bitmap_updates uses) ---- */
RD_BOOL bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp);
void *xmalloc(int size);
void xfree(void *mem);
void ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data);

#define EX_UNAVAILABLE  69

/* ---- rdesktop.c (verbatim: real xmalloc/xfree bodies) ---- */
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

/* Compiler-escape barrier (harness-only helper, does NOT touch the target function):
 * at -O1 clang can see that ui_paint_bitmap()/bitmap_decompress() below never actually
 * read through the pointers they are handed, and that xfree()/free() don't either, so
 * it can prove the whole malloc+memcpy-loop+free sequence in process_bitmap_updates()
 * has no observable effect and dead-code-eliminate it -- silently turning this CVE's
 * real heap-buffer-overflow memcpy into a no-op. Force the compiler to assume `p` may
 * be read by unknown code so every write into it (and the out-of-bounds read that
 * feeds it) must actually execute. */
static void
vb_escape(void *p)
{
	__asm__ __volatile__("" : : "g"(p) : "memory");
}

/* ---- stubs for callees not on the crash path we exercise here ---- */
void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
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
	vb_escape(data);
}

RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) width;
	(void) height;
	(void) input;
	(void) size;
	(void) Bpp;
	vb_escape(output);
	return False;
}

/* ============ verbatim: data_cve/cve_5df55079/target/original_function.c ============ */
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
}/* ============ end verbatim ============ */

int
main(int argc, char **argv)
{
	FILE *f;
	long len;
	unsigned char *buf;
	size_t n;
	struct stream st;

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
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
	len = ftell(f);
	if (len < 0)
	{
		fclose(f);
		return 1;
	}
	fseek(f, 0, SEEK_SET);

	/* Heap-allocate EXACTLY `len` bytes, so ASan's redzone sits immediately past the
	 * real end of the PDU. `st.end` below is set to that exact boundary, so any
	 * stream macro that walks `st.p` past it without checking (process_bitmap_updates
	 * checks nothing) is caught as a heap-buffer-overflow by ASan. */
	buf = (unsigned char *) malloc(len > 0 ? (size_t) len : 1);
	if (!buf)
	{
		fclose(f);
		return 1;
	}

	n = fread(buf, 1, (size_t) len, f);
	fclose(f);
	(void) n;

	memset(&st, 0, sizeof(st));
	st.data = buf;
	st.p = buf;
	st.end = buf + len;
	st.size = (unsigned int) len;

	process_bitmap_updates(&st);

	free(buf);
	return 0;
}

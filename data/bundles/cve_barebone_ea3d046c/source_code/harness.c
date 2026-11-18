/* cve_barebone direct-call harness for cve_ea3d046c (rdesktop)
 * Target: process_bitmap_updates  (rdp.c -- exact text frozen in target/original_function.c)
 * Bug class: 32-bit int overflow in the xmalloc(width*height*Bpp) size computation ->
 * heap-buffer-overflow WRITE (CWE-787).
 *
 * fix_commit 4dca546d04321a610c1835010b5dad85163b65e1 split process_bitmap_updates into a
 * per-record process_bitmap_data() helper and added, among other hardening, this EXACT guard
 * (verbatim from the diff) that the vulnerable function below lacks entirely:
 *     if ((RD_UINT32_MAX / Bpp) <= (width * height))
 *         rdp_protocol_error("TS_BITMAP_DATA, unsafe size of bitmap data received from server", ..);
 * width/height/bpp are each attacker-controlled uint16 wire fields (bpp up to 65535 -> Bpp =
 * (bpp+7)/8 up to 8192); `width * height * Bpp` is plain 32-bit `int` arithmetic (the usual
 * arithmetic conversions promote each uint16 to int) with NO overflow check anywhere in
 * process_bitmap_updates's own body. Pick width/height/bpp so this product wraps past 2^32 and
 * `bmpdata = xmalloc(width*height*Bpp)` allocates a buffer of size N, while the
 * uncompressed-bitmap loop's very first iteration --
 *     in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 * -- computes an offset that (the SAME modular identity, N minus one row_bytes term) is a
 * small NEGATIVE index -- this harness's corpus picks parameters landing that exactly 16 bytes
 * before bmpdata (inside its always-present ASan left-redzone), and the width*Bpp-byte memcpy
 * write there runs forward through the redzone into (and filling exactly) the valid buffer: a
 * heap-buffer-overflow WRITE, entirely inside process_bitmap_updates's own generated code
 * (in_uint8a expands to an inline memcpy, no callee boundary). Built with `-fwrapv
 * -fno-builtin` (harness.flags) -- both empirically required for THIS overflow to manifest as
 * the C source actually specifies rather than as an optimizer reinterpretation of it; see the
 * module docstring for why.
 *
 * This harness feeds process_bitmap_updates a STREAM whose data/end are set from a
 * heap-allocated (ASAN-guarded) copy of argv[1]'s raw bytes -- exactly the role the real
 * network-receive buffer plays -- so a per-record header with a hostile width/height/bpp
 * reproduces the real-world "malicious server PDU" trigger verbatim, no synthetic scaffolding.
 *
 * Real type defs (struct stream + its accessor macros, uint8/uint16, log_subject_t/
 * log_level_t) copied verbatim from stream.h / types.h / utils.h (x86_64 is little-endian,
 * !NEED_ALIGN -- configure.ac's AC_C_BIGENDIAN defines L_ENDIAN on this host, so the
 * `*(uint16*)p` cast-and-read form below is the exact branch stream.h compiles to). xmalloc/
 * xfree copied verbatim from rdesktop.c/utils.c (the target calls both directly). logger() is
 * a faithful no-op stand-in (its only role here is a %s/%d-format debug print; whether it
 * actually prints is unobservable to the bug). ui_paint_bitmap (X11 rendering) and
 * bitmap_decompress (the *compressed*-bitmap RLE decoder, never exercised by this harness's
 * chosen inputs -- every crafted input takes the uncompressed branch) are incidental to this
 * specific integer-overflow bug and are stubbed minimally/no-op, matching their real proto.h
 * signatures exactly -- they never touch the crash path.
 *
 * Build (dc_batch/dc_try, in cvf-builder; harness.flags supplies the extra -fwrapv
 * -fno-builtin noted above):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 -fwrapv -fno-builtin harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sysexits.h>
#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

/* ---- types.h (verbatim subset actually used) ---- */
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

/* ---- stream.h (verbatim) ---- */
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
#define in_uint32_le(s,v)	{ v = *(uint32 *)((s)->p); (s)->p += 4; }
#define in_uint8(s,v)		v = *((s)->p++);
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- utils.h (verbatim enums + faithful no-op logger) ---- */
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
	(void) c;
	(void) lvl;
	(void) format;		/* debug-only print; not observable to the bug */
}

/* ---- process_bitmap_updates's other callees ---- */

/* rdesktop.c -- verbatim (the target calls xmalloc directly for bmpdata) */
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

/* utils.c -- verbatim */
void
xfree(void *mem)
{
	free(mem);
}

/* xwin.c's real ui_paint_bitmap() blits bmpdata to the X11 window -- pure rendering,
 * incidental to this memory-safety bug. Real signature (proto.h), no-op body. */
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

/* bitmap.c's real bitmap_decompress() is the RLE decoder for the *compressed* branch; every
 * input this harness crafts uses the uncompressed branch to reach the missing-bounds-check
 * bug, so bitmap_decompress is never actually invoked at runtime here (link-time symbol only
 * for the compressed-branch SAFE inputs below, which never reach a crash regardless of what
 * this returns). Real signature (proto.h), stub returns False (a legitimate real return:
 * "decompress failed"). */
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

/* ==== VERBATIM from data_cve/cve_ea3d046c/target/original_function.c ==== */
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

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0)
	{
		fclose(f);
		return 0;
	}
	long sz = ftell(f);
	if (sz < 0)
		sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0)
	{
		fclose(f);
		return 0;
	}

	/* HEAP-allocate the raw wire bytes (ASAN-guarded) -- this buffer plays exactly the role
	 * of the real TCP receive buffer that STREAM::data normally points into. The TRIGGERING
	 * records below carry a full, valid width*Bpp bytes of pixel data (so the memcpy's SOURCE
	 * read side is always in-bounds); the crash is the DESTINATION (bmpdata) side, from the
	 * width/height/bpp-driven xmalloc-size integer overflow -- see the module docstring. */
	size_t alloc_sz = (sz > 0) ? (size_t) sz : 1;
	unsigned char *buf = (unsigned char *) malloc(alloc_sz);
	if (!buf)
	{
		fclose(f);
		return 0;
	}
	size_t n = (sz > 0) ? fread(buf, 1, (size_t) sz, f) : 0;
	fclose(f);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = buf;
	st.p = buf;
	st.end = buf + n;
	st.size = (unsigned int) n;

	process_bitmap_updates(&st);

	free(buf);
	return 0;
}

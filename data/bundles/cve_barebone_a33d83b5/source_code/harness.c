/* cve_barebone direct-call harness -- rdesktop CVE-2018-8796-family
 * Target: process_bitmap_updates (rdp.c) -- heap-buffer-overflow READ (CWE-125)
 *
 * process_bitmap_updates() parses a TS_UPDATE_BITMAP_DATA PDU straight off the wire STREAM
 * with NO bounds checking anywhere in the loop -- in_uint16_le()/in_uint8a()/in_uint8p()
 * (stream.h) are bare pointer-advancing macros that never compare s->p against s->end. In
 * the uncompressed branch (compress == 0):
 *     bmpdata = xmalloc(width * height * Bpp);
 *     for (y = 0; y < height; y++)
 *         in_uint8a(s, &bmpdata[(height-y-1)*(width*Bpp)], width*Bpp);   // memcpy, no check
 * A server that advertises width/height/bpp implying more row bytes than it actually sent
 * makes in_uint8a's memcpy() read straight past the end of the heap buffer holding the wire
 * PDU. This is exactly the bug the fix commit (4dca546d) closes by adding s_check_rem()
 * guards throughout process_bitmap_data (the function's post-fix name) before every stream
 * consume.
 *
 * TRIGGER: the 20-byte record header is present but fewer than width*Bpp payload bytes
 *          follow it -> the first in_uint8a() call reads past the wire allocation.
 * SAFE:    the record carries the full height*width*Bpp bytes of row data it claims -> every
 *          in_uint8a() stays inside the allocation, no crash.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- primitive types (types.h, verbatim names) ---- */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef int RD_BOOL;

/* ---- wire-parsing stream (stream.h, verbatim field names/order) ---- */
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

/* ---- stream-consume macros (stream.h, verbatim -- the L_ENDIAN + !NEED_ALIGN path, which
 * is the one AC_C_BIGENDIAN(configure.ac) selects on this little-endian x86_64 host). NONE
 * of these bounds-check against s->end -- that omission IS the vulnerability. ---- */
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- logging (utils.h signature: void logger(log_subject_t, log_level_t, char*, ...)) --
 * real logger filters+writes to stderr by subject/level; purely diagnostic, not on any
 * crash path, so a no-op stand-in with the exact signature is faithful. ---- */
typedef enum log_level_t { Debug = 0, Verbose, Warning, Error, Notice } log_level_t;
typedef enum log_subject_t { GUI = 0, Keyboard, Clipboard, Sound, Protocol, Graphics, Core, SmartCard, Disk } log_subject_t;
static void logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c; (void) lvl; (void) format;
}

/* ---- allocation helpers (rdesktop.c bodies, trimmed of the exit()-on-OOM branch -- plain
 * malloc/free wrappers, no bearing on the bug). ---- */
static void *xmalloc(int size) { return malloc((size_t) size); }
static void xfree(void *mem) { free(mem); }

/* ---- incidental callees on the *compressed* branch (proto.h signatures, verbatim) --
 * never reached by any crafted input here (all set compress=0, the uncompressed/buggy
 * branch); bitmap_decompress is a bare stub since it is truly never called. ---- */
static RD_BOOL bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output; (void) width; (void) height; (void) input; (void) size; (void) Bpp;
	return 0;
}

/* ---- ui_paint_bitmap (proto.h signature, verbatim) -- display sink, only ever reached
 * AFTER the copy loop already finished. A bare no-op stub is UNSOUND here: it never
 * observes bmpdata's bytes, so at -O1 the optimizer can prove the whole
 * xmalloc/in_uint8a-copy/xfree sequence inside process_bitmap_updates has no observable
 * effect and delete it outright -- vaporizing the very memcpy this harness exists to
 * exercise (confirmed empirically: with a no-op stub, `objdump -d` shows zero `memcpy`
 * calls and every crafted TRIGGER input runs clean). So this stub genuinely READS through
 * `data`, folding it into a `volatile` sink, matching what the real X11 ui_paint_bitmap
 * (xwin.c) actually does (blits every byte). It reads width*height bytes -- a safe lower
 * bound on bmpdata's real width*height*Bpp size for every Bpp>=1 this harness's bpp choices
 * (8/16/24/32) ever produce, so the stub itself never reads out of bounds. ---- */
static volatile unsigned char vb_paint_sink;
static void ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x; (void) y; (void) cx; (void) cy;
	long n = (long) width *(long) height;
	unsigned char acc = 0;
	for (long i = 0; i < n; i++)
		acc ^= data[i];
	vb_paint_sink = acc;
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline so the ASAN report keeps process_bitmap_updates as its own frame (it is the sole
 * call site inside main(), which -O1 would otherwise happily inline away). */
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
/* ================= end verbatim ================= */

int main(int argc, char **argv)
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
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 0)
		ln = 0;
	size_t n = (size_t) ln;

	/* HEAP-allocate the wire PDU with EXACTLY the bytes the "server" sent -- no padding --
	 * so ASAN's redzone sits immediately after the last real byte. Any stream read past it
	 * (the vulnerability) is then caught deterministically. */
	unsigned char *wire = (unsigned char *) malloc(n ? n : 1);
	if (!wire)
	{
		fclose(fp);
		return 2;
	}
	size_t got = fread(wire, 1, n, fp);
	fclose(fp);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = wire;
	st.p = wire;
	st.end = wire + got;
	st.size = (unsigned int) got;

	STREAM s = &st;

	/* volatile function pointer: forbid the compiler from proving anything about the call
	 * (defense in depth alongside noinline). */
	void (*volatile fn) (STREAM) = process_bitmap_updates;
	fn(s);

	free(wire);
	return 0;
}

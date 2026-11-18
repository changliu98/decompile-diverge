/* cve_barebone harness -- CVE-2018-20175 / rdesktop process_bitmap_updates
 *
 * See scripts/gen_dc_cve_6998bbfd.py for the full writeup. Summary: width*height*Bpp
 * (three attacker uint16-derived `int`s) overflows 32-bit int in the xmalloc() size for
 * the uncompressed-bitmap path, then the unchecked in_uint8a() memcpy loop writes the
 * real (unwrapped) byte count into that undersized buffer -> heap-buffer-overflow WRITE
 * (CWE-787). Fixed 2018-12-10 (commit 4dca546d) by adding an explicit overflow guard
 * before the allocation; this harness reproduces the pre-fix code verbatim.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real base typedefs (types.h) ---- */
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

/* ---- real stream type + parsing macros (stream.h, verbatim subset -- L_ENDIAN, the
 * x86_64 path) ---- */
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

/* ---- real log enum (utils.h) + faithful no-op stub: logger() is pure diagnostics,
 * never on the crash path. ---- */
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

void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
}

/* ---- real xmalloc/xfree (rdesktop.c, verbatim behaviour -- the NULL-check exit() path
 * is never taken by any crafted input: every size we hand it is either the deliberately
 * undersized overflow residue, comfortably satisfiable by a real malloc(), or a normal
 * small safe-path size). ---- */
void *
xmalloc(int size)
{
	void *mem = malloc(size);
	if (mem == NULL)
	{
		fprintf(stderr, "xmalloc, failed to allocate %d bytes\n", size);
		exit(1);
	}
	return mem;
}

void
xfree(void *mem)
{
	free(mem);
}

/* ---- incidental callees: real prototypes (proto.h), faithful no-op stubs. Every
 * crafted input sets compress=0, so the *only* branch process_bitmap_updates takes is
 * `if (!compress) { ... continue; }` -- ui_paint_bitmap is called there (stubbed: real
 * rendering has no bearing on the OOB write, which already happened before this call),
 * and bitmap_decompress is declared (needed so the compressed branch still compiles) but
 * is NEVER invoked by any input in this corpus. ---- */
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

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
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

/* ================= driver =================
 * Reads argv[1] into a HEAP buffer and interprets it as a raw TS_UPDATE_BITMAP_DATA
 * wire record: num_updates(u16) then, per update, left/top/right/bottom/width/height/
 * bpp/compress/bufsize (u16 each) followed by the uncompressed row payload
 * (compress==0 -> height rows of width*Bpp bytes, bottom-up). Every crafted input in
 * this corpus uses num_updates=1 and compress=0.
 */
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
	fseek(fp, 0, SEEK_END);
	long fsz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (fsz < 0)
		fsz = 0;

	/* HEAP-allocate the raw wire buffer (ASAN-guarded). */
	unsigned char *raw = (unsigned char *) malloc((size_t) fsz ? (size_t) fsz : 1);
	size_t got = fread(raw, 1, (size_t) fsz, fp);
	fclose(fp);

	struct stream st;
	memset(&st, 0, sizeof(st));
	st.data = raw;
	st.p = raw;
	st.end = raw + got;
	st.size = (unsigned int) got;

	/* volatile function-pointer indirection: forbids the compiler from inlining
	 * process_bitmap_updates into main() at -O1, so it keeps its own stack frame
	 * (the harness classifier requires the target function name in the ASAN
	 * backtrace). */
	void (*volatile fn) (STREAM) = process_bitmap_updates;
	fn(&st);

	free(raw);
	return 0;
}

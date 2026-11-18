/* cve_barebone direct-call harness for cve_69d0976b (rdesktop)
 * Target: process_bitmap_updates  (rdp.c -- the pre-refactor, unbounded-read version
 *   frozen verbatim in target/original_function.c). fix_commit 4dca546d split this
 *   function into process_bitmap_data()+process_bitmap_updates() and added several
 *   `s_check_rem()` guards (e.g. before consuming the COMPRESSED bitmap bytes).
 * Bug class: missing stream-bounds check -> heap-buffer-overflow READ (CWE-125).
 *
 * process_bitmap_updates loops num_updates times; each iteration reads a
 * TS_BITMAP_DATA-shaped rectangle header (left/top/right/bottom/width/height/bpp/
 * compress/bufsize -- 9 little-endian uint16 fields) then, when compress==0, calls
 *     in_uint8a(s, &bmpdata[(height-y-1)*(width*Bpp)], width*Bpp)
 * `height` times to fill a `width*height*Bpp`-byte heap buffer. `in_uint8a`
 * (stream.h) is a bare `memcpy(dst, s->p, n); s->p += n;` with NO check that `n`
 * bytes actually remain in the stream (s_check_rem is never called on this
 * uncompressed-row path, in EITHER the vulnerable or the "fixed" source -- the fix
 * commit's new checks target a different read, the compressed-bitmap path's
 * in_uint8p). So a stream whose real backing buffer ends right after the header,
 * but whose header claims a nonzero width/height/bpp, makes in_uint8a() copy
 * width*Bpp bytes off the end of the (ASAN-guarded) heap allocation holding the
 * wire bytes -- a heap-buffer-overflow READ, attributed to process_bitmap_updates
 * itself (in_uint8a expands inline; no separate callee frame). width/height/bpp are
 * kept small (<=11, bpp<=32 => Bpp<=4, so width*height*Bpp <= 484) so the
 * xmalloc(width*height*Bpp) DESTINATION allocation itself is always small and never
 * overflows -- only the STREAM read is unbounded.
 *
 * xmalloc/xfree are pasted verbatim from rdesktop.c (the real allocator wrapper).
 * logger/ui_paint_bitmap/bitmap_decompress are minimal stand-ins for callees that
 * never sit on the crash path here: logger is pure I/O (format string only, no
 * pointer read that could fault), ui_paint_bitmap is a display sink only ever
 * reached AFTER a fully in-bounds copy already succeeded, and bitmap_decompress is
 * only reachable via the COMPRESSED branch (compress != 0), which no PoC below
 * takes (every crafted input uses compress == 0).
 *
 * ui_paint_bitmap's stub genuinely READS through its `data` pointer (folding it
 * into a volatile sink) rather than being a bare no-op: a no-op stub never
 * observes bmpdata's bytes, so -O1 can prove the whole xmalloc/in_uint8a-copy/
 * xfree sequence above has no observable effect and delete it outright --
 * vaporizing the very memcpy this harness exists to exercise (confirmed: it
 * does). Reading width*height bytes is a safe lower bound on bmpdata's real
 * width*height*Bpp size for every Bpp>=1 this harness ever constructs, so the
 * stub itself never reads out of bounds.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real rdesktop types, verbatim from types.h / stream.h / utils.h ---- */
typedef int RD_BOOL;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

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

/* stream.h, L_ENDIAN + !NEED_ALIGN branch (this box is x86_64, little-endian) --
 * the exact macros process_bitmap_updates is built with in a real rdesktop build. */
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* utils.h, verbatim enums */
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

/* stub: pure logging sink, no pointer dereference that could fault -- incidental. */
void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c; (void) lvl; (void) format;
}

/* verbatim from rdesktop.c: "malloc; exit if out of memory" */
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

/* verbatim from rdesktop.c */
void
xfree(void *mem)
{
	free(mem);
}

/* stub: display sink, only ever reached AFTER the copy loop already finished
 * in-bounds -- incidental to the memory-safety property under test. Genuinely
 * READS through `data` (see header comment) so the copy that fills it can't be
 * proven dead and deleted by the optimizer. */
static volatile unsigned char vb_paint_sink;
void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x; (void) y; (void) cx; (void) cy;
	long n = (long) width * (long) height;
	unsigned char acc = 0;
	for (long i = 0; i < n; i++)
		acc ^= data[i];
	vb_paint_sink = acc;
}

/* stub: only reachable via the compressed branch (compress != 0), which none of
 * this harness's PoCs take -- kept so the verbatim function still links. */
RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output; (void) width; (void) height; (void) input; (void) size; (void) Bpp;
	return 0;
}

/* ==== VERBATIM from data_cve/cve_69d0976b/target/original_function.c ==== */
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

int
main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the wire buffer, sized EXACTLY to the input file: this is the
	 * literal byte-for-byte STREAM contents process_bitmap_updates parses, so
	 * ASAN's redzone sits immediately past the real, attacker-controlled bytes. */
	unsigned char *buf = (unsigned char *) malloc((size_t) (fsz > 0 ? fsz : 1));
	if (!buf) { fclose(f); return 0; }
	size_t got = (fsz > 0) ? fread(buf, 1, (size_t) fsz, f) : 0;
	fclose(f);
	(void) got;

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

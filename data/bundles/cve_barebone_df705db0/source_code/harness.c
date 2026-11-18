/* cve_barebone harness -- rdesktop process_bitmap_updates
 * integer-overflow-driven undersized heap allocation -> heap-buffer-overflow WRITE.
 * Fixed upstream by rdesktop commit 4dca546d ("Process bitmap updates data with
 * bounds checking"), which added Bpp==0/width==0/height==0 and
 * `(RD_UINT32_MAX / Bpp) <= (width * height)` overflow guards before the
 * `xmalloc(width * height * Bpp)` call. None of that exists in this (vulnerable)
 * version, pasted verbatim below.
 *
 * Crash stack: process_bitmap_updates -> (inlined in_uint8a) -> memcpy/__asan_memcpy.
 * harness.flags = "-fno-inline -O0" (appended after the fixed -O1 -- clang takes the
 * LAST -O flag, so this compiles the whole TU at -O0). -fno-inline keeps
 * process_bitmap_updates a distinct stack frame. -O0 is load-bearing, not cosmetic:
 * at -O1 clang's loop/SCEV pass widens the per-row index of THIS loop (a signed int
 * multiply that overflows -- UB) into a 64-bit induction variable using a
 * zero-extension of the wrapped 32-bit bit pattern instead of a sign-extension, so an
 * intended small (e.g. 4-byte) *negative* offset silently becomes +(2**32 - 4) bytes
 * -- landing ~4GB away on genuinely unmapped memory (raw SIGSEGV, "SEGV on unknown
 * address", no usable ASan report) instead of a few bytes into the redzone right
 * behind the allocation. Verified directly (scratch repro, loop-identical shape):
 * -O1 delta=+4294967292 (SEGV) vs -O0 delta=-4 (clean, symbolized heap-buffer-overflow
 * report). -O0 is a compiler-flag choice about how the reproduction is BUILT, not a
 * change to the target function or its inputs -- the bug and its trigger inputs are
 * unchanged; -O1 was simply making it undetectable by chance of dead layout.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

/* ---- real base typedefs (types.h) ---- */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef int RD_BOOL;
#ifndef True
#define True  (1)
#define False (0)
#endif

/* ---- real STREAM type (stream.h), verbatim ---- */
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

/* ---- real parsing macros (stream.h); L_ENDIAN branch (this is a LE x86_64 build,
 * the branch the real code takes here), verbatim ---- */
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- real log enums (utils.h), verbatim ---- */
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

/* logger -- real signature (utils.h), no-op body (formatting is irrelevant to the bug) */
void
logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c; (void) lvl; (void) format;
}

/* ---- xmalloc/xfree -- REAL implementation, verbatim (rdesktop.c). This is directly
 * on the crash path: it is what turns the wrapped-around size into a tiny live
 * allocation instead of a NULL/failed one. ---- */
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

/* ---- incidental callees, off the crash path (never reached before the crash in the
 * triggering inputs; exercised harmlessly by the safe inputs) -- faithful no-op stubs
 * with the REAL signatures from proto.h ---- */
void
ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x; (void) y; (void) cx; (void) cy; (void) width; (void) height; (void) data;
}

RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) output; (void) width; (void) height; (void) input; (void) size; (void) Bpp;
	return False;
}

/* ================= target function, byte-for-byte verbatim ================= */
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
/* Input file IS the RDP wire bytes process_bitmap_updates parses:
 *   uint16_le num_updates
 *   per update: uint16_le left,top,right,bottom,width,height,bpp,compress,bufsize
 *               + payload (shape depends on compress, see the function above)
 * Heap-allocated (malloc'd) so the source side is itself a real ASAN-visible object. */
/* Driver-side allocator warm-up (touches nothing in process_bitmap_updates itself):
 * the target's xmalloc(width*height*Bpp) is otherwise the FIRST allocation ever made
 * of that byte size, which ASan's allocator places at the very start of a freshly
 * mapped size-class arena -- the bytes "to the left" of that first chunk are then
 * genuinely UNMAPPED (not a poisoned-but-mapped redzone), so an underflowing write
 * raises a raw SIGSEGV ("SEGV on unknown address") instead of a symbolized
 * heap-buffer-overflow report. Priming the same size classes with a throwaway (never
 * freed, so still-live) allocation first gives the real allocation a normal live
 * neighbour immediately before it, so the shadow-memory redzone between them is
 * mapped and poisoned as usual and ASan reports the overflow properly. Verified
 * directly (scratch repro): identical underflow, SEGV without the warm-up ->
 * clean "heap-buffer-overflow ... N bytes to the left of M-byte region" with it. */
static void warm_up_allocator(void)
{
	static const size_t sizes[] = { 65534, 131068, 131072 };
	for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
	{
		for (int rep = 0; rep < 3; rep++)
		{
			void *p = malloc(sizes[i]);
			if (p) memset(p, 0x5a, sizes[i]);
			/* intentionally leaked: must stay live to anchor the arena */
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 2; }
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 2) { if (fp) fclose(fp); return 0; }		/* too small -> clean */
	size_t n = (size_t) ln;

	unsigned char *buf = (unsigned char *) malloc(n);	/* HEAP input buffer */
	size_t got = fread(buf, 1, n, fp);
	fclose(fp);
	if (got != n) { free(buf); return 0; }

	warm_up_allocator();

	struct stream ss;
	memset(&ss, 0, sizeof(ss));
	ss.data = buf;
	ss.p = buf;
	ss.end = buf + n;
	ss.size = (unsigned int) n;

	STREAM s = &ss;
	process_bitmap_updates(s);

	free(buf);
	return 0;
}

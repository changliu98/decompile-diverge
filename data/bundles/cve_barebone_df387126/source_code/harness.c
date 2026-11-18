/* cve_barebone direct-call harness for CVE-2018-20177 (rdesktop RDP client)
 * Target: process_bitmap_updates  (rdp.c)
 * Bug class: CWE-787 heap-buffer-overflow WRITE (root cause CWE-190/CWE-680 integer overflow ->
 * undersized allocation).
 *
 * See generator script (scripts/gen_dc_cve_df387126.py) docstring for the full derivation of the
 * trigger parameters. Summary: in the uncompressed-bitmap branch,
 *     bmpdata = (uint8 *) xmalloc(width * height * Bpp);
 *     for (y = 0; y < height; y++)
 *         in_uint8a(s, &bmpdata[(height - y - 1) * (width * Bpp)], width * Bpp);
 * computes the allocation size and the per-row write length/offset from the SAME attacker uint16
 * fields but via DIFFERENT 32-bit multiplication groupings ((width*height)*Bpp vs
 * height*(width*Bpp)) with no overflow/range check -- picking width/height/bpp so the former
 * wraps to a small value while the per-row write stays a sane, unwrapped value turns this into a
 * small, deterministic heap-buffer-overflow on the very first row copy.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sysexits.h>

#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE 69
#endif

/* ---- real types.h primitive typedefs (verbatim) ---- */
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

typedef int RD_BOOL;

/* ---- real stream.h STREAM descriptor (verbatim, stream.h) ---- */
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

/* ---- real stream.h parsing macros process_bitmap_updates uses (verbatim, the
 * `defined(L_ENDIAN) && !defined(NEED_ALIGN)` branch -- what configure.ac's AC_C_BIGENDIAN
 * actually selects on a little-endian x86-64 build, which does not require aligned access) ---- */
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;

/* ---- real utils.h log enums + logger() signature (verbatim, utils.h). Body is a no-op stub:
 * logger is pure tracing, never touches process_bitmap_updates's buffers or control flow. ---- */
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
	(void) format;
}

/* ---- xmalloc / xfree: VERBATIM (rdesktop.c) -- these ARE on the crash path (their ordinary,
 * unmodified "just malloc/free" behaviour is exactly what lets an undersized allocation happen
 * and later be freed without complaint). ---- */
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

/* ---- vb_escape: a standard, semantically-inert "used elsewhere" compiler barrier (the same
 * technique as e.g. Google Benchmark's DoNotOptimize) -- tells the optimizer a pointer may have
 * been read, without itself reading/writing anything. Needed below for fidelity: the REAL
 * ui_paint_bitmap genuinely reads bmpdata (it draws it to the screen), so in the real program the
 * vulnerable copy is never "dead". A literal no-op stub is UNFAITHFUL here -- at -O1 the
 * optimizer can prove bmpdata's bytes are never observed before xfree() and delete the whole
 * xmalloc+in_uint8a-loop as dead code, silently masking the real bug. This restores that one
 * real fact (the buffer escapes to the UI layer) without simulating any actual drawing. */
static inline void
vb_escape(const void *p)
{
	__asm__ __volatile__("" : : "r"(p) : "memory");
}

/* ---- bitmap_decompress / ui_paint_bitmap: real prototypes (proto.h), minimal stubs. Both are
 * INCIDENTAL to this bug: every input this harness generates takes the UNCOMPRESSED branch
 * (compress == 0), so bitmap_decompress is never even called; it is stubbed only so the
 * COMPRESSED branch still present in process_bitmap_updates's own (verbatim, unedited) body
 * links. Neither stub READS OR WRITES its buffer arguments (only vb_escape()s the pointers), so
 * neither can mask or fake the real bug, which lives entirely in the uncompressed-branch
 * xmalloc+in_uint8a above. ---- */
RD_BOOL
bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
{
	(void) width;
	(void) height;
	(void) size;
	(void) Bpp;
	vb_escape(output);
	vb_escape(input);
	return 0;
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

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_df387126/target/original_function.c */
/* ======================================================================================== */
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
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), points a STREAM descriptor at it
 * exactly like rdp_recv()'s caller does (p = start, end = start+n, data = start), and calls
 * process_bitmap_updates(&s) -- its real, single-argument signature. Called through a volatile
 * function pointer purely so this externally-linked (non-static) function cannot be inlined into
 * main() and disappear as a distinct ASAN backtrace frame; this changes nothing about how it is
 * called or its own bytes. */
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 64;
	}
	FILE *fp = fopen(argv[1], "rb");
	if (!fp)
	{
		perror("fopen");
		return 64;
	}
	if (fseek(fp, 0, SEEK_END) != 0)
	{
		fclose(fp);
		return 64;
	}
	long fsz = ftell(fp);
	if (fsz <= 0)
	{
		fclose(fp);
		return 64;
	}
	if (fseek(fp, 0, SEEK_SET) != 0)
	{
		fclose(fp);
		return 64;
	}

	size_t n = (size_t) fsz;
	unsigned char *buf = (unsigned char *) malloc(n);
	if (!buf)
	{
		fclose(fp);
		return 64;
	}
	size_t rn = fread(buf, 1, n, fp);
	fclose(fp);

	struct stream s;
	memset(&s, 0, sizeof(s));
	s.data = buf;
	s.p = buf;
	s.end = buf + rn;
	s.size = (unsigned int) rn;

	void (*volatile vb_call)(STREAM) = process_bitmap_updates;
	vb_call(&s);

	/* Only reached on a SAFE run (a triggering run aborts inside the call above). */
	free(buf);
	return 0;
}

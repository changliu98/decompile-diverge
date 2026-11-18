/* cve_barebone harness -- rdesktop CVE-2018-8796 / process_bitmap_updates
 * heap-buffer-overflow WRITE (CWE-787). See module docstring of gen_dc_cve_5c9dceb7.py for the
 * full bug writeup. process_bitmap_updates is called directly on a STREAM wrapping raw file
 * bytes -- exactly how the real RDP client invokes it on attacker-controlled network data.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* x86-64 is little-endian, no alignment restriction: this is exactly what rdesktop's own
 * configure.ac (AC_C_BIGENDIAN) defines on this platform. */
#define L_ENDIAN 1

/* ---- types.h (verbatim): RD_BOOL, True/False, uint8/sint8/uint16/sint16/uint32/sint32 ---- */
typedef int RD_BOOL;

#ifndef True
#define True  (1)
#define False (0)
#endif

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

/* ---- stream.h (verbatim): struct stream / STREAM + in_uint16_le/in_uint8a/in_uint8p/
 * in_uint8s (selects the L_ENDIAN, !NEED_ALIGN branch via the #if above, same as the real
 * autoconf'd build on x86-64) ---- */
/* Parser state */
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

void s_realloc(STREAM s, unsigned int size);
void s_free(STREAM s);
void s_reset(STREAM s);

void out_utf16s(STREAM s, const char *string);
void out_utf16s_padded(STREAM s, const char *string, size_t width, unsigned char pad);
void out_utf16s_no_eos(STREAM s, const char *string);

size_t in_ansi_string(STREAM s, char *string, size_t len);


#define s_push_layer(s,h,n)	{ (s)->h = (s)->p; (s)->p += n; }
#define s_pop_layer(s,h)	(s)->p = (s)->h;
#define s_mark_end(s)		(s)->end = (s)->p;
#define s_check(s)		((s)->p <= (s)->end)
#define s_check_rem(s,n)	((s)->p + n <= (s)->end)
#define s_check_end(s)		((s)->p == (s)->end)
#define s_length(s)		((s)->end - (s)->data)
#define s_left(s)               ((s)->size - ((s)->p - (s)->data))

#if defined(L_ENDIAN) && !defined(NEED_ALIGN)
#define in_uint16_le(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint32_le(s,v)	{ v = *(uint32 *)((s)->p); (s)->p += 4; }
#define out_uint16_le(s,v)	{ *(uint16 *)((s)->p) = v; (s)->p += 2; }
#define out_uint32_le(s,v)	{ *(uint32 *)((s)->p) = v; (s)->p += 4; }
#else
#define in_uint16_le(s,v)	{ v = *((s)->p++); v += *((s)->p++) << 8; }
#define in_uint32_le(s,v)	{ in_uint16_le(s,v) \
				v += *((s)->p++) << 16; v += *((s)->p++) << 24; }
#define out_uint16_le(s,v)	{ *((s)->p++) = (v) & 0xff; *((s)->p++) = ((v) >> 8) & 0xff; }
#define out_uint32_le(s,v)	{ out_uint16_le(s, (v) & 0xffff); out_uint16_le(s, ((v) >> 16) & 0xffff); }
#endif

#define out_uint64_le(s,v)	{ out_uint32_le(s, (v) & 0xffffffff); out_uint32_le(s, ((v) >> 32) & 0xffffffff); }

#if defined(B_ENDIAN) && !defined(NEED_ALIGN)
#define in_uint16_be(s,v)	{ v = *(uint16 *)((s)->p); (s)->p += 2; }
#define in_uint32_be(s,v)	{ v = *(uint32 *)((s)->p); (s)->p += 4; }
#define out_uint16_be(s,v)	{ *(uint16 *)((s)->p) = v; (s)->p += 2; }
#define out_uint32_be(s,v)	{ *(uint32 *)((s)->p) = v; (s)->p += 4; }

#define B_ENDIAN_PREFERRED
#define in_uint16(s,v)		in_uint16_be(s,v)
#define in_uint32(s,v)		in_uint32_be(s,v)
#define out_uint16(s,v)		out_uint16_be(s,v)
#define out_uint32(s,v)		out_uint32_be(s,v)

#else
#define in_uint16_be(s,v)	{ v = *((s)->p++); next_be(s,v); }
#define in_uint32_be(s,v)	{ in_uint16_be(s,v); next_be(s,v); next_be(s,v); }
#define out_uint16_be(s,v)	{ *((s)->p++) = ((v) >> 8) & 0xff; *((s)->p++) = (v) & 0xff; }
#define out_uint32_be(s,v)	{ out_uint16_be(s, ((v) >> 16) & 0xffff); out_uint16_be(s, (v) & 0xffff); }
#endif

#ifndef B_ENDIAN_PREFERRED
#define in_uint16(s,v)		in_uint16_le(s,v)
#define in_uint32(s,v)		in_uint32_le(s,v)
#define out_uint16(s,v)		out_uint16_le(s,v)
#define out_uint32(s,v)		out_uint32_le(s,v)
#endif

#define in_uint8(s,v)		v = *((s)->p++);
#define in_uint8p(s,v,n)	{ v = (s)->p; (s)->p += n; }
#define in_uint8a(s,v,n)	{ memcpy(v,(s)->p,n); (s)->p += n; }
#define in_uint8s(s,n)		(s)->p += n;
#define in_skip(s,n)		in_uint8s(s,n)
#define out_uint8(s,v)		*((s)->p++) = v;
#define out_uint8p(s,v,n)	{ memcpy((s)->p,v,n); (s)->p += n; }
#define out_uint8a(s,v,n)	out_uint8p(s,v,n);
#define out_uint8s(s,n)		{ memset((s)->p,0,n); (s)->p += n; }
#define out_stream(s, v)        out_uint8p(s, (v)->data, s_length((v)))

#define next_be(s,v)		v = ((v) << 8) + *((s)->p++);

/* ---- utils.h (verbatim): log_level_t, log_subject_t, logger() prototype ---- */
typedef enum log_level_t
{
	Debug = 0,
	Verbose,
	Warning,
	Error,
	Notice			/* special message level for end user messages with prefix */
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

/* ---- rdesktop.h (verbatim): EX_UNAVAILABLE ---- */
#ifndef EX_UNAVAILABLE
#define EX_UNAVAILABLE  69
#endif

/* ---- logger: incidental (pure diagnostic output, never touches memory the bug depends on)
 * -- minimal no-op stub, real name+signature. ---- */
void logger(log_subject_t c, log_level_t lvl, char *format, ...)
{
	(void) c;
	(void) lvl;
	(void) format;
}

/* ---- xmalloc / xfree: VERBATIM (rdesktop.c) -- the real allocator the bug's undersized
 * allocation goes through. noinline is a pure codegen hint (body byte-identical to rdesktop.c;
 * same technique used elsewhere in this harness family, e.g. gen_dc_cve_c7dbd731.py's
 * skb_add_rx_frag) added ONLY because at -O1 clang was willing to inline this tiny function
 * into process_bitmap_updates, and once inlined it further folded the (already -fwrapv-
 * wrapped) allocation-size arithmetic into the loop's address computation in a way that made
 * the intended out-of-bounds write disappear entirely (confirmed empirically: identical input,
 * identical target bytes, only inlining differs) -- forbidding the inline keeps xmalloc's own
 * 32-bit-wrapping `malloc(size)` call architecturally separate from the address arithmetic in
 * process_bitmap_updates's copy loop, exactly like the real, separately-compiled-in-practice
 * rdesktop.c: xmalloc). ---- */
__attribute__((noinline))
/* malloc; exit if out of memory */
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

/* free */
void
xfree(void *mem)
{
	free(mem);
}

/* ---- ui_paint_bitmap / bitmap_decompress: incidental (proto.h real names+signatures).
 * ui_paint_bitmap is only reached AFTER a successful (non-crashing) uncompressed decode --
 * real body draws to an X11 window, irrelevant here. bitmap_decompress belongs to the OTHER
 * (compressed) branch, never exercised by this corpus (all inputs use the uncompressed path,
 * where the bug lives) -- kept only so the function reference resolves. ---- */
void ui_paint_bitmap(int x, int y, int cx, int cy, int width, int height, uint8 * data)
{
	(void) x;
	(void) y;
	(void) cx;
	(void) cy;
	(void) width;
	(void) height;
	(void) data;
}

RD_BOOL bitmap_decompress(uint8 * output, int width, int height, uint8 * input, int size, int Bpp)
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

/* ================= driver ================= */
/* The input file IS the wire payload process_bitmap_updates parses: uint16 num_updates, then
 * per update uint16 left/top/right/bottom/width/height/bpp/compress/bufsize, then (compress==0)
 * width*height*Bpp bytes of raw pixel data -- exactly the crafted io/input/<N> files below. */
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
	unsigned char *buf = (unsigned char *) malloc(n ? n : 1);	/* HEAP input, ASAN-guarded */
	size_t got = fread(buf, 1, n, fp);
	fclose(fp);
	if (got < 20)
	{
		free(buf);	/* too short for even one fixed per-update header -> clean exit */
		return 0;
	}

	struct stream st;
	memset(&st, 0, sizeof st);
	st.data = buf;
	st.p = buf;
	st.end = buf + got;
	st.size = (unsigned int) got;

	/* volatile function pointer: keep process_bitmap_updates a real stack frame (dc_batch
	 * needs it in the ASAN backtrace) and forbid -O1 from inlining it away. */
	void (*volatile fn) (STREAM) = process_bitmap_updates;
	fn(&st);

	free(buf);
	return 0;
}

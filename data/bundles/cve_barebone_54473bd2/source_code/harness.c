/* Direct-call harness for cvf_54473bd2 (CVE-2015-8784, libtiff libtiff/tif_next.c)
 *
 * Target: NeXTDecode() (embedded VERBATIM, byte-identical to
 * dataset/cvf_54473bd2/target/original_function.c) -- the NeXT 2-bit
 * grey-scale run-length decoder. Baseline dedup_token
 * "NeXTDecode--TIFFReadEncodedTile--TIFFReadTile", CWE-787
 * heap-buffer-overflow WRITE, ASan summary
 * "AddressSanitizer: heap-buffer-overflow tif_next.c:126:6 in NeXTDecode".
 *
 * Real upstream fix (b18012dae552f85dcc5c57d3bf4e997a15b1cc1c) confirms the
 * mechanism: in the run-mode ("default:") branch of the decode switch, the
 * SETPIXEL() loop advances `op` (the write cursor into the caller-supplied
 * `buf`/`row`) purely as a function of `npixels < imagewidth` -- imagewidth
 * comes from tif->tif_dir.td_imagewidth / td_tilewidth (attacker-controlled
 * TIFF tags), completely independent of `scanline`
 * (tif->tif_scanlinesize, i.e. how many bytes `row` actually has). When
 * imagewidth's pixel count needs more than `scanline` packed bytes
 * (SETPIXEL packs 4 two-bit pixels per byte), `op` walks straight past the
 * end of the `scanline`-sized row -- and on the *last* row of the decode
 * call, straight past the end of the `occ`-sized `buf` allocation itself.
 * The fix adds a `op_offset < scanline` bound to the same while loop plus
 * an explicit `op_offset >= scanline` error return; NONE of that exists in
 * this (vulnerable, pre-fix) copy of the function, which is exactly what is
 * embedded below, verbatim.
 *
 * Faithfulness / minimality of the surrounding scaffolding:
 *  - SETPIXEL/LITERALROW/LITERALSPAN/WHITE are the real macros that
 *    immediately precede NeXTDecode in libtiff/tif_next.c (reproduced
 *    verbatim from dataset/cvf_54473bd2/source_code/libtiff/tif_next.c;
 *    confirmed byte-identical to the frozen target/original_function.c
 *    starting right after these macros).
 *  - `struct tiff`/`TIFFDirectory`/`TIFF_ISTILED`/`isTiled()` are trimmed
 *    down to just the fields NeXTDecode itself dereferences
 *    (tif_rawcp/tif_rawcc/tif_scanlinesize/tif_dir.td_imagewidth/
 *    tif_dir.td_tilewidth/tif_clientdata/tif_row/tif_flags), using the
 *    REAL field names and REAL types from
 *    source_code/libtiff/{tiffiop.h,tif_dir.h} (TIFF is opaque upstream --
 *    `struct tiff` is only ever used through a pointer by client code, so
 *    supplying our own definition with a matching subset of fields is
 *    exactly how every other decoder in this codebase is unit-testable).
 *  - `_TIFFmemcpy` is libtiff's own thin `memcpy` wrapper
 *    (source_code/libtiff/tif_unix.c:338), reproduced verbatim.
 *  - `TIFFErrorExt` is a no-op-but-real-signature stub (the target only
 *    calls it on the "bad"/error paths, i.e. never on a payload that
 *    actually reaches the vulnerable write).
 *
 * main() reads argv[1] into a HEAP buffer (never a stack/global buffer for
 * attacker data), parses a tiny fixed header out of it
 * (scanline, imagewidth, tiled-flag) plus a raw payload tail, allocates a
 * SEPARATE tightly-sized HEAP `buf` of exactly `occ == scanline` bytes
 * (single scanline/row per call -- so any run-mode overrun manifests
 * immediately as a heap-buffer-overflow past the *whole* allocation, the
 * same way the real bug manifests on a tile/strip's last row), wires up a
 * `struct tiff` whose tif_rawcp/tif_rawcc point at the (also heap, exactly
 * sized) payload tail, and calls NeXTDecode() exactly once.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* ---- real libtiff typedefs (tiff.h / tiffconf.h), reproduced verbatim ---- */
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long long uint64;
typedef long tmsize_t;                 /* TIFF_SSIZE_T on a 64-bit host */
typedef void *thandle_t;               /* client data handle (tiffio.h, non-Win32) */

/* ---- TIFF is opaque upstream (tiffio.h: "typedef struct tiff TIFF;") ---- */
typedef struct tiff TIFF;

/* ---- TIFFDirectory (tif_dir.h): only the two fields NeXTDecode reads,
 * real field names/types, rest of the real struct omitted (not referenced
 * by the target function). ---- */
typedef struct {
	uint32  td_imagewidth;
	uint32  td_tilewidth;
} TIFFDirectory;

/* ---- struct tiff (tiffiop.h): only the fields NeXTDecode dereferences,
 * real field names/types/order, rest of the real (much larger) struct
 * omitted. ---- */
struct tiff {
	uint32         tif_flags;
	TIFFDirectory  tif_dir;
	uint32         tif_row;
	tmsize_t       tif_scanlinesize;
	uint8         *tif_rawcp;
	tmsize_t       tif_rawcc;
	thandle_t      tif_clientdata;
};

/* tiffiop.h:117 */
#define TIFF_ISTILED     0x00400U
/* tiffiop.h:214, verbatim */
#define isTiled(tif) (((tif)->tif_flags & TIFF_ISTILED) != 0)

/* tif_unix.c:338, verbatim thin wrapper */
static void
_TIFFmemcpy(void* d, const void* s, tmsize_t c)
{
	memcpy(d, s, (size_t)c);
}

/* tiffio.h:451 signature; real body is vsnprintf-and-report -- here just a
 * no-op stub with the correct signature (the vulnerable payloads below
 * never take the "bad"/error return path, so this is never exercised on
 * the triggering inputs; it IS exercised on the "goto bad" / early-return
 * safe inputs, where it must simply not crash). */
static void
TIFFErrorExt(thandle_t fd, const char* module, const char* fmt, ...)
{
	(void) fd;
	va_list ap;
	va_start(ap, fmt);
	if (module) fprintf(stderr, "%s: ", module);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

/* ============================================================
 * BEGIN verbatim from source_code/libtiff/tif_next.c
 * (macros immediately preceding NeXTDecode, then NeXTDecode itself --
 * byte-identical to dataset/cvf_54473bd2/target/original_function.c)
 * ============================================================ */

#define SETPIXEL(op, v) {			\
	switch (npixels++ & 3) {		\
	case 0:	op[0]  = (unsigned char) ((v) << 6); break;	\
	case 1:	op[0] |= (v) << 4; break;	\
	case 2:	op[0] |= (v) << 2; break;	\
	case 3:	*op++ |= (v);	   break;	\
	}					\
}

#define LITERALROW	0x00
#define LITERALSPAN	0x40
#define WHITE   	((1<<2)-1)

static int
NeXTDecode(TIFF* tif, uint8* buf, tmsize_t occ, uint16 s)
{
	static const char module[] = "NeXTDecode";
	unsigned char *bp, *op;
	tmsize_t cc;
	uint8* row;
	tmsize_t scanline, n;

	(void) s;
	/*
	 * Each scanline is assumed to start off as all
	 * white (we assume a PhotometricInterpretation
	 * of ``min-is-black'').
	 */
	for (op = (unsigned char*) buf, cc = occ; cc-- > 0;)
		*op++ = 0xff;

	bp = (unsigned char *)tif->tif_rawcp;
	cc = tif->tif_rawcc;
	scanline = tif->tif_scanlinesize;
	if (occ % scanline)
	{
		TIFFErrorExt(tif->tif_clientdata, module, "Fractional scanlines cannot be read");
		return (0);
	}
	for (row = buf; cc > 0 && occ > 0; occ -= scanline, row += scanline) {
		n = *bp++, cc--;
		switch (n) {
		case LITERALROW:
			/*
			 * The entire scanline is given as literal values.
			 */
			if (cc < scanline)
				goto bad;
			_TIFFmemcpy(row, bp, scanline);
			bp += scanline;
			cc -= scanline;
			break;
		case LITERALSPAN: {
			tmsize_t off;
			/*
			 * The scanline has a literal span that begins at some
			 * offset.
			 */
			if( cc < 4 )
				goto bad;
			off = (bp[0] * 256) + bp[1];
			n = (bp[2] * 256) + bp[3];
			if (cc < 4+n || off+n > scanline)
				goto bad;
			_TIFFmemcpy(row+off, bp+4, n);
			bp += 4+n;
			cc -= 4+n;
			break;
		}
		default: {
			uint32 npixels = 0, grey;
			uint32 imagewidth = tif->tif_dir.td_imagewidth;
            if( isTiled(tif) )
                imagewidth = tif->tif_dir.td_tilewidth;

			/*
			 * The scanline is composed of a sequence of constant
			 * color ``runs''.  We shift into ``run mode'' and
			 * interpret bytes as codes of the form
			 * <color><npixels> until we've filled the scanline.
			 */
			op = row;
			for (;;) {
				grey = (uint32)((n>>6) & 0x3);
				n &= 0x3f;
				/*
				 * Ensure the run does not exceed the scanline
				 * bounds, potentially resulting in a security
				 * issue.
				 */
				while (n-- > 0 && npixels < imagewidth)
					SETPIXEL(op, grey);
				if (npixels >= imagewidth)
					break;
				if (cc == 0)
					goto bad;
				n = *bp++, cc--;
			}
			break;
		}
		}
	}
	tif->tif_rawcp = (uint8*) bp;
	tif->tif_rawcc = cc;
	return (1);
bad:
	TIFFErrorExt(tif->tif_clientdata, module, "Not enough data for scanline %ld",
	    (long) tif->tif_row);
	return (0);
}

/* ============================================================
 * END verbatim
 * ============================================================ */

/*
 * Harness input format (all our own, parsed from the HEAP-resident
 * argv[1] file; NeXTDecode itself never sees any of this parsing --
 * it only ever sees the fields of `fake` and the `bp`/`raw` payload
 * bytes, exactly as it would from a real TIFF library caller):
 *
 *   byte 0     : scanline in [1,64]        (tif_scanlinesize / row size)
 *   bytes 1-4  : imagewidth, little-endian (tif_dir.td_imagewidth/td_tilewidth)
 *   byte 5     : tiled flag (bit0)          (tif_flags & TIFF_ISTILED)
 *   bytes 6..  : raw compressed payload      (tif_rawcp / tif_rawcc)
 *
 * occ is always exactly `scanline` (a single row per call), so the decode
 * loop's outer `for` body runs at most once and `buf` is allocated to
 * exactly that many bytes -- a run-mode overrun therefore always walks off
 * the end of the *entire* heap allocation, never just into a subsequent
 * (still-allocated) row.
 */
int main(int argc, char **argv)
{
	if (argc < 2) return 0;

	FILE *f = fopen(argv[1], "rb");
	if (!f) return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 0; }
	rewind(f);

	uint8 *raw = (uint8 *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!raw) { fclose(f); return 1; }
	size_t n = (fsz > 0) ? fread(raw, 1, (size_t)fsz, f) : 0;
	fclose(f);

	if (n < 6) { free(raw); return 0; }

	uint32 scanline = raw[0];
	if (scanline < 1) scanline = 1;
	if (scanline > 64) scanline = 64;

	uint32 imagewidth = (uint32)raw[1] | ((uint32)raw[2] << 8) |
	                    ((uint32)raw[3] << 16) | ((uint32)raw[4] << 24);
	int tiled = raw[5] & 1;

	size_t hdrlen = 6;
	size_t rawlen = (n > hdrlen) ? (n - hdrlen) : 0;

	/* payload buffer: HEAP, sized exactly to the attacker-supplied tail
	 * (tif_rawcc == rawlen, so NeXTDecode's own `cc` bookkeeping matches
	 * the true allocation -- any OOB access of *this* buffer would be an
	 * unrelated read bug, not the CWE-787 write under test). */
	uint8 *rawbuf = NULL;
	if (rawlen > 0) {
		rawbuf = (uint8 *)malloc(rawlen);
		if (!rawbuf) { free(raw); return 1; }
		memcpy(rawbuf, raw + hdrlen, rawlen);
	}
	free(raw);

	/* destination buffer: HEAP, TIGHTLY sized to occ == scanline (single
	 * row) -- this is the buffer the CVE-2015-8784 write overruns. */
	tmsize_t occ = (tmsize_t)scanline;
	uint8 *buf = (uint8 *)malloc((size_t)occ);
	if (!buf) { free(rawbuf); return 1; }

	struct tiff fake;
	memset(&fake, 0, sizeof(fake));
	fake.tif_flags = tiled ? TIFF_ISTILED : 0;
	fake.tif_dir.td_imagewidth = imagewidth;
	fake.tif_dir.td_tilewidth = imagewidth;
	fake.tif_row = 0;
	fake.tif_scanlinesize = (tmsize_t)scanline;
	fake.tif_rawcp = rawbuf;
	fake.tif_rawcc = (tmsize_t)rawlen;
	fake.tif_clientdata = NULL;

	(void) NeXTDecode(&fake, buf, occ, 0);

	free(rawbuf);
	free(buf);
	return 0;
}

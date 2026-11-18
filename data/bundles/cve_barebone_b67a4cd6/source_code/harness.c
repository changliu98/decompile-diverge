/*
 * Direct-call crash harness for cvf_b67a4cd6 (deark, CVE-2021-28856).
 *
 * Target: fmtutil_macbitmap_read_pixmap_only_fields (src/fmtutil.c, embedded VERBATIM below).
 * Bug: unchecked, input-derived `bi->pixelsize` (read at pos+18 as a big-endian u16) is used
 * as a divisor at `bi->pdwidth = (bi->rowbytes*8)/bi->pixelsize;` with no zero-check.
 * pixelsize == 0 -> integer divide-by-zero -> SIGFPE, caught by AddressSanitizer's default
 * handle_sigfpe handler and reported as "AddressSanitizer: FPE ... in
 * fmtutil_macbitmap_read_pixmap_only_fields" -- exactly the frozen baseline dedup/summary
 * (case.json: baseline.summary = "AddressSanitizer: FPE ... in
 * fmtutil_macbitmap_read_pixmap_only_fields", bug_class "FPE").
 *
 * All supporting types/helpers below are copied VERBATIM (or trimmed to the MEMBUF-only path,
 * with identical bounds-checking logic) from the real deark sources so the target function's
 * body needs zero modification:
 *   - struct fmtutil_macbitmap_info : src/deark-fmtutil.h:558-573 (verbatim, full field list)
 *   - dbuf_read / dbuf_getu16be / dbuf_getu32be / dbuf_geti32be / de_get*_direct :
 *     src/deark-dbuf.c (verbatim logic; dbuf_read's DBUF_TYPE_IFILE/IDBUF branches removed
 *     since our harness only ever constructs a DBUF_TYPE_MEMBUF -- same bounds-check semantics
 *     as the real function on that path: any read past f->len is zero-filled, never OOB)
 *   - pict_read_fixed : modules/pict.c:48-56 (verbatim; a real callee of the target function)
 *   - de_dbg / de_dbg_indent : stubbed no-ops (pure debug-log helpers, not part of the fault;
 *     the real versions dereference a fully-populated `deark*` context we don't construct)
 *
 * main() reads argv[1] into a HEAP buffer (malloc), wraps it in a MEMBUF dbuf (len == bytes
 * read, so dbuf_read's real bounds check is exact -- no synthetic OOB), sets up a
 * fmtutil_macbitmap_info the way a real caller would after fmtutil_macbitmap_read_rowbytes_and_bounds
 * (bi->rowbytes/npwidth nonzero), and calls the target function ONCE with pos=0, so file offset
 * N == function offset "pos+N" directly.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- src/deark.h integer type macros (verbatim) ---- */
#define i64 int64_t
#define u64 uint64_t
#define i32 int32_t
#define u32 uint32_t
#define i16 int16_t
#define u16 uint16_t
#define u8 unsigned char

#define DE_CHAR_TIMES "\xc3\x97"

/* opaque deark context -- only ever passed as NULL to the stubbed de_dbg* helpers below */
struct deark_struct { int dummy; };
typedef struct deark_struct deark;

/* ---- src/deark-private.h: struct dbuf_struct, reduced to the fields the MEMBUF path of
 * dbuf_read touches, real field names/types unchanged ---- */
#define DBUF_TYPE_MEMBUF  3
struct dbuf_struct {
	int btype;
	deark *c;
	i64 len;
	u8 *cache;
	i64 cache_bytes_used;
	u8 *membuf_buf;
};
typedef struct dbuf_struct dbuf;

/* ---- src/deark-fmtutil.h:558-573, VERBATIM ---- */
typedef u32 de_color;
struct fmtutil_macbitmap_info {
	i64 rowbytes; // The rowBytes field
	i64 rowspan; // Actual number of bytes/row
	i64 npwidth, pdwidth, height;
	int is_uncompressed;
	i64 packing_type;
	i64 pixeltype, pixelsize;
	i64 cmpcount, cmpsize;
	double hdpi, vdpi;
	u32 pmTable;
	int pixmap_flag;
	int has_colortable; // Does the file contain a colortable for this bitmap?
	int uses_pal; // Are we using the palette below?
	i64 num_pal_entries;
	de_color pal[256];
};

/* ---- stubbed debug-log helpers (not part of the fault; real versions need a live deark* ctx) ---- */
static void de_dbg(deark *c, const char *fmt, ...) { (void)c; (void)fmt; }
static void de_dbg_indent(deark *c, int n) { (void)c; (void)n; }

/* ---- src/deark-dbuf.c, VERBATIM helpers used by dbuf_read ---- */
static void de_zeromem(void *mem, size_t n) { memset(mem, 0, n); }
static void de_memcpy(void *dst, const void *src, size_t n) { memcpy(dst, src, n); }

/* src/deark-dbuf.c:86 dbuf_read(), trimmed to the DBUF_TYPE_MEMBUF branch only (the only
 * btype this harness ever constructs); the pos<0 / bytes_to_read clamping logic that precedes
 * the switch -- the part that actually enforces the bounds check -- is UNCHANGED. */
static void dbuf_read(dbuf *f, u8 *buf, i64 pos, i64 len)
{
	i64 bytes_read = 0;
	i64 bytes_to_read;

	if(pos < 0) {
		if((-pos) >= len) {
			// All requested bytes are before the beginning of the file
			de_zeromem(buf, (size_t)len);
			return;
		}
		// Some requested bytes are before the beginning of the file.
		// Zero out the ones that are:
		de_zeromem(buf, (size_t)(-pos));
		// And adjust the parameters:
		buf += (-pos);
		len -= (-pos);
		pos = 0;
	}

	bytes_to_read = len;
	if(pos >= f->len) {
		bytes_to_read = 0;
	}
	else if(pos + bytes_to_read > f->len) {
		bytes_to_read = f->len - pos;
	}

	if(bytes_to_read<1) {
		goto done_read;
	}

	switch(f->btype) {
	case DBUF_TYPE_MEMBUF:
		de_memcpy(buf, &f->membuf_buf[pos], (size_t)bytes_to_read);
		bytes_read = bytes_to_read;
		break;
	default:
		goto done_read;
	}

done_read:
	// Zero out any requested bytes that were not read.
	if(bytes_read < len) {
		de_zeromem(buf+bytes_read, (size_t)(len - bytes_read));
	}
}

/* src/deark-dbuf.c, VERBATIM */
static i64 de_getu16be_direct(const u8 *m)
{
	return (i64)(((u32)m[1]) | (((u32)m[0])<<8));
}

static i64 dbuf_getu16be(dbuf *f, i64 pos)
{
	u8 m[2];
	dbuf_read(f, m, pos, 2);
	return de_getu16be_direct(m);
}

static i64 de_getu32be_direct(const u8 *m)
{
	return (i64)(((u32)m[3]) | (((u32)m[2])<<8) |
		(((u32)m[1])<<16) | (((u32)m[0])<<24));
}

static i64 dbuf_getu32be(dbuf *f, i64 pos)
{
	u8 m[4];
	dbuf_read(f, m, pos, 4);
	return de_getu32be_direct(m);
}

static i64 dbuf_geti32be(dbuf *f, i64 pos)
{
	i64 n;
	n = dbuf_getu32be(f, pos);
	return (i64)(i32)(u32)n;
}

/* ---- modules/pict.c:48-56, VERBATIM (real callee of the target function) ---- */
static double pict_read_fixed(dbuf *f, i64 pos)
{
	i64 n;

	// I think QuickDraw's "Fixed point" numbers are signed, but I don't know
	// how negative numbers are handled.
	n = dbuf_geti32be(f, pos);
	return ((double)n)/65536.0;
}

/* =====================================================================
 * TARGET FUNCTION -- src/fmtutil.c:1590-1636, VERBATIM, byte-for-byte.
 * Do not modify logic/names/signature.
 * ===================================================================== */
void fmtutil_macbitmap_read_pixmap_only_fields(deark *c, dbuf *f, struct fmtutil_macbitmap_info *bi,
	i64 pos)
{
	i64 pixmap_version;
	i64 pack_size;
	i64 plane_bytes;
	i64 n;

	de_dbg(c, "additional PixMap header fields, at %d", (int)pos);
	de_dbg_indent(c, 1);

	pixmap_version = dbuf_getu16be(f, pos+0);
	de_dbg(c, "pixmap version: %d", (int)pixmap_version);

	bi->packing_type = dbuf_getu16be(f, pos+2);
	de_dbg(c, "packing type: %d", (int)bi->packing_type);

	pack_size = dbuf_getu32be(f, pos+4);
	de_dbg(c, "pixel data length: %d", (int)pack_size);

	bi->hdpi = pict_read_fixed(f, pos+8);
	bi->vdpi = pict_read_fixed(f, pos+12);
	de_dbg(c, "dpi: %.2f"DE_CHAR_TIMES"%.2f", bi->hdpi, bi->vdpi);

	bi->pixeltype = dbuf_getu16be(f, pos+16);
	bi->pixelsize = dbuf_getu16be(f, pos+18);
	bi->cmpcount = dbuf_getu16be(f, pos+20);
	bi->cmpsize = dbuf_getu16be(f, pos+22);
	de_dbg(c, "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
		(int)bi->pixeltype, (int)bi->pixelsize, (int)bi->cmpcount, (int)bi->cmpsize);

	bi->pdwidth = (bi->rowbytes*8)/bi->pixelsize;
	if(bi->pdwidth < bi->npwidth) {
		bi->pdwidth = bi->npwidth;
	}

	plane_bytes = dbuf_getu32be(f, pos+24);
	de_dbg(c, "plane bytes: %d", (int)plane_bytes);

	bi->pmTable = (u32)dbuf_getu32be(f, pos+28);
	de_dbg(c, "pmTable: 0x%08x", (unsigned int)bi->pmTable);

	n = dbuf_getu32be(f, pos+32);
	de_dbg(c, "pmReserved: 0x%08x", (unsigned int)n);

	de_dbg_indent(c, -1);
}

/* =====================================================================
 * main() -- direct-call driver.
 * ===================================================================== */
int main(int argc, char **argv)
{
	FILE *fp;
	long sz;
	u8 *buf;
	size_t rd;
	dbuf f;
	struct fmtutil_macbitmap_info bi;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "rb");
	if (!fp) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	sz = ftell(fp);
	if (sz < 0) sz = 0;
	fseek(fp, 0, SEEK_SET);

	/* Attacker-controlled data MUST live in a heap allocation so ASAN's redzones/allocator
	 * instrumentation are in play (never a stack/global buffer). */
	buf = (u8 *)malloc((size_t)(sz > 0 ? sz : 1));
	if (!buf) {
		fclose(fp);
		return 1;
	}
	rd = fread(buf, 1, (size_t)sz, fp);
	fclose(fp);

	memset(&f, 0, sizeof(f));
	f.btype = DBUF_TYPE_MEMBUF;
	f.c = NULL;
	f.len = (i64)rd;
	f.cache = NULL;
	f.cache_bytes_used = 0;
	f.membuf_buf = buf;

	/* Mirror the real caller (fmtutil_macbitmap_read_rowbytes_and_bounds, called before this
	 * function in every real call site: modules/pict.c, modules/macrsrc.c) which always sets
	 * a nonzero bi->rowbytes/bi->npwidth from the file's rowBytes/bounds fields before this
	 * function runs. Fixed plausible nonzero values here -- only bi->pixelsize (read from the
	 * heap buffer at pos+18, fully attacker-controlled) determines whether the division faults. */
	memset(&bi, 0, sizeof(bi));
	bi.rowbytes = 8;
	bi.npwidth = 4;

	fmtutil_macbitmap_read_pixmap_only_fields(NULL, &f, &bi, 0);

	free(buf);
	return 0;
}

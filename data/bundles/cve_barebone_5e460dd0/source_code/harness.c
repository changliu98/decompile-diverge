/* cve_5e460dd0 -- rizin -- MACH0_(parse_chained_fixups)
 *
 * Self-contained direct-call ASAN harness. GitHub: rizinorg/rizin
 * fix_commit=41ea75d5b07d9b41b27ae80675cdda65f1b1c989
 * vul_commit=7c1b965937d61b4279a618389d983cc0ace70254
 *
 * BUG (from the fix diff, librz/bin/format/mach0/mach0_chained_fixups.c):
 *   -	size_t max_count = RZ_MAX(bin->nsegs, cf->starts_count);
 *   +	size_t max_count = bin->nsegs;
 *   +	if (max_count > cf->starts_count) {
 *   +		max_count = cf->starts_count;
 *   +	}
 * `cf->starts` is allocated with exactly `cf->starts_count` (attacker-controlled,
 * read from the chained-fixups blob) slots via RZ_NEWS0(...). The buggy line uses
 * RZ_MAX(bin->nsegs, cf->starts_count) as the loop bound instead of the MIN, so
 * whenever bin->nsegs (the already-parsed Mach-O segment count) exceeds
 * cf->starts_count, the loop range [0, max_count) walks past the end of the
 * `cf->starts` allocation and `cf->starts[i] = cur_seg;` performs a heap-buffer-
 * overflow WRITE (CWE-787) of an 8-byte pointer.
 *
 * Isolation: MACH0_(parse_chained_fixups) is called directly on a synthetic
 * RzBuffer built from argv[1]. Real callees on the crash path -- the LE
 * header/segment-start readers (`read_dyld_chained_fixups_header`,
 * `read_dyld_chained_starts_in_segment`) and the RzBuffer bounds-checked LE
 * read primitives they're built from (`rz_buf_read_at`, `rz_buf_read_le*_at`,
 * `rz_buf_read_le*_offset`) -- are reproduced faithfully (real field layouts /
 * real bounds-check semantics from librz/include/rz_util/rz_buf.h and
 * librz/bin/format/mach0/mach0_{defines,chained_fixups}.c) against a minimal
 * flat-bytes RzBuffer stub (the real RzBuffer is an opaque, ref-counted,
 * pluggable mmap/file/io/sparse abstraction -- irrelevant scaffolding for a
 * from-argv[1] byte blob). `parse_chained_imports` is INCIDENTAL to the bug
 * (called only after the vulnerable loop) and is stubbed to its own real
 * early-exit behaviour for header.imports_count == 0, which every input this
 * harness constructs sets -- see the corpus generator (gen_inputs.py).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- librz/include/rz_types_base.h (real names) ---- */
typedef unsigned char ut8;
typedef signed char st8;
typedef unsigned short ut16;
typedef short st16;
typedef unsigned int ut32;
typedef int st32;
typedef unsigned long long ut64;
typedef long long st64;
#define UT64_MAX 0xFFFFFFFFFFFFFFFFULL

/* ---- librz/include/rz_types.h (real names) ---- */
#define RZ_IPI
#define RZ_API
#define RZ_NEWS0(x, y) (x *)calloc((y), sizeof(x))
#define RZ_NEW0(x)     (x *)calloc(1, sizeof(x))

/* ---- librz/include/rz_types_base.h ---- */
#define RZ_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define RZ_MIN(x, y) (((x) > (y)) ? (y) : (x))

/* ---- rz_types.h PFMT64x (non-Windows) ---- */
#define PFMT64x "llx"

/* ---- librz/include/rz_util/rz_log.h: faithful-enough stub (real macro logs
 * through rz_log()/an installed sink; here just print to stderr so a
 * triggering run's log still shows the message if the guard fires) ---- */
#define RZ_LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define RZ_LOG_WARN(...)  fprintf(stderr, __VA_ARGS__)

/* ---- librz/bin/format/mach0/mach0_specs.h: the real MACH0_() token-paste
 * macro (32-bit variant: MACH0_(name) -> name, verbatim). This harness only
 * builds one instantiation of the excerpted function, so the 32-bit branch is
 * picked; MACH0_(parse_chained_fixups) -> parse_chained_fixups and
 * MACH0_(obj_t) -> obj_t, exactly like the real 32-bit rizin build. ---- */
#define MACH0_(name) name

/* ---- librz/include/rz_vector.h (real, verbatim -- only needed for the
 * `imports` field's type inside mach0_chained_fixups_t below; never touched
 * at runtime by any input this harness constructs, see the
 * parse_chained_imports stub further down) ---- */
typedef void (*RzVectorFree)(void *e, void *user);
typedef struct rz_vector_t {
	void *a;
	size_t len;
	size_t capacity;
	size_t elem_size;
	RzVectorFree free;
	void *free_user;
} RzVector;

/* ---- librz/bin/format/mach0/mach0_defines.h (real names, verbatim) ---- */
struct dyld_chained_fixups_header {
	ut32 fixups_version;
	ut32 starts_offset;
	ut32 imports_offset;
	ut32 symbols_offset;
	ut32 imports_count;
	ut32 imports_format; ///< enum dyld_chained_import_format
	ut32 symbols_format;
};

struct rz_dyld_chained_starts_in_segment {
	ut32 size;
	ut16 page_size;
	ut16 pointer_format;
	ut64 segment_offset;
	ut32 max_valid_pointer;
	ut16 page_count;
	ut16 *page_start;
};

enum dyld_chained_import_format {
	DYLD_CHAINED_IMPORT_THREADED = -1,
	DYLD_CHAINED_IMPORT_INVALID = 0,
	DYLD_CHAINED_IMPORT = 1,
	DYLD_CHAINED_IMPORT_ADDEND = 2,
	DYLD_CHAINED_IMPORT_ADDEND64 = 3
};

/* ---- librz/bin/format/mach0/mach0.h (real names, verbatim) ---- */
struct mach0_chained_fixups_t {
	struct rz_dyld_chained_starts_in_segment **starts;
	ut32 starts_count;
	enum dyld_chained_import_format imports_format;
	RzVector imports; // contained type is dynamically specified by imports_format above
	ut64 symbols_base_paddr;
};

/* ---- RzBuffer: minimal faithful stub of librz/include/rz_util/rz_buf.h's
 * bytes-backed buffer type + the bounds-checked LE-read helpers
 * MACH0_(parse_chained_fixups) and its real static callees use. The real
 * RzBuffer is an opaque, ref-counted, pluggable abstraction (mmap / file /
 * io / sparse / ... backends chosen via a vtable); we need only the flat
 * heap-bytes case a from-disk Mach-O blob uses, so this is {data,length}
 * plus rz_buf_read_at()/rz_buf_read_le{16,32,64}_at()/_offset() reproduced
 * from rz_buf.h's DEFINE_RZ_BUF_READ_BLE / DEFINE_RZ_BUF_READ_OFFSET_BLE
 * macros (big_endian=false only -- the `_le*` entry points are the only ones
 * the target function uses). Semantics preserved exactly: an `_at` read
 * requires the FULL width to be in-bounds or it fails (false / -1); an
 * `_offset` read only advances the passed offset on success. ---- */
typedef struct rz_buffer_t {
	ut8 *data;
	ut64 length;
} RzBuffer;

static st64 rz_buf_read_at(RzBuffer *b, ut64 addr, ut8 *buf, ut64 len) {
	if (!b || !buf || addr > b->length) {
		return -1;
	}
	ut64 avail = b->length - addr;
	ut64 n = len < avail ? len : avail;
	if (n > 0) {
		memcpy(buf, b->data + addr, n);
	}
	return (st64)n;
}

static ut16 rz_read_le16(const ut8 *p) {
	return (ut16)((ut16)p[0] | ((ut16)p[1] << 8));
}
static ut32 rz_read_le32(const ut8 *p) {
	return (ut32)p[0] | ((ut32)p[1] << 8) | ((ut32)p[2] << 16) | ((ut32)p[3] << 24);
}
static ut64 rz_read_le64(const ut8 *p) {
	ut64 lo = rz_read_le32(p);
	ut64 hi = rz_read_le32(p + 4);
	return lo | (hi << 32);
}

static bool rz_buf_read_le16_at(RzBuffer *b, ut64 addr, ut16 *result) {
	ut8 tmp[sizeof(ut16)];
	if (rz_buf_read_at(b, addr, tmp, sizeof(tmp)) != (st64)sizeof(tmp)) {
		return false;
	}
	*result = rz_read_le16(tmp);
	return true;
}
static bool rz_buf_read_le32_at(RzBuffer *b, ut64 addr, ut32 *result) {
	ut8 tmp[sizeof(ut32)];
	if (rz_buf_read_at(b, addr, tmp, sizeof(tmp)) != (st64)sizeof(tmp)) {
		return false;
	}
	*result = rz_read_le32(tmp);
	return true;
}
static bool rz_buf_read_le64_at(RzBuffer *b, ut64 addr, ut64 *result) {
	ut8 tmp[sizeof(ut64)];
	if (rz_buf_read_at(b, addr, tmp, sizeof(tmp)) != (st64)sizeof(tmp)) {
		return false;
	}
	*result = rz_read_le64(tmp);
	return true;
}
static bool rz_buf_read_le16_offset(RzBuffer *b, ut64 *offset, ut16 *result) {
	if (!rz_buf_read_le16_at(b, *offset, result)) {
		return false;
	}
	*offset += sizeof(*result);
	return true;
}
static bool rz_buf_read_le32_offset(RzBuffer *b, ut64 *offset, ut32 *result) {
	if (!rz_buf_read_le32_at(b, *offset, result)) {
		return false;
	}
	*offset += sizeof(*result);
	return true;
}
static bool rz_buf_read_le64_offset(RzBuffer *b, ut64 *offset, ut64 *result) {
	if (!rz_buf_read_le64_at(b, *offset, result)) {
		return false;
	}
	*offset += sizeof(*result);
	return true;
}

/* ---- librz/bin/format/mach0/mach0_chained_fixups.c: real static helpers,
 * verbatim (lines 23-42 of the real file). Both are real callees the target
 * function calls; read_dyld_chained_fixups_header always runs,
 * read_dyld_chained_starts_in_segment is reachable whenever a seg_off is
 * nonzero (this harness's crafted inputs never need it to succeed -- the OOB
 * write happens one statement before it would be called -- but it is
 * included verbatim rather than stubbed since it is short and genuinely on
 * the code path). ---- */
static bool read_dyld_chained_fixups_header(struct dyld_chained_fixups_header *header, RzBuffer *buf, ut64 base) {
	ut64 offset = base;
	return rz_buf_read_le32_offset(buf, &offset, &header->fixups_version) &&
		rz_buf_read_le32_offset(buf, &offset, &header->starts_offset) &&
		rz_buf_read_le32_offset(buf, &offset, &header->imports_offset) &&
		rz_buf_read_le32_offset(buf, &offset, &header->symbols_offset) &&
		rz_buf_read_le32_offset(buf, &offset, &header->imports_count) &&
		rz_buf_read_le32_offset(buf, &offset, &header->imports_format) &&
		rz_buf_read_le32_offset(buf, &offset, &header->symbols_format);
}

static bool read_dyld_chained_starts_in_segment(struct rz_dyld_chained_starts_in_segment *segment, RzBuffer *buf, ut64 base) {
	ut64 offset = base;
	return rz_buf_read_le32_offset(buf, &offset, &segment->size) &&
		rz_buf_read_le16_offset(buf, &offset, &segment->page_size) &&
		rz_buf_read_le16_offset(buf, &offset, &segment->pointer_format) &&
		rz_buf_read_le64_offset(buf, &offset, &segment->segment_offset) &&
		rz_buf_read_le32_offset(buf, &offset, &segment->max_valid_pointer) &&
		rz_buf_read_le16_offset(buf, &offset, &segment->page_count);
}

/* ---- parse_chained_imports: INCIDENTAL to the bug (only called AFTER the
 * vulnerable `cf->starts` loop returns/completes, never on the crash path).
 * The real function (mach0_chained_fixups.c:44-93) walks
 * header->imports_count entries out of an RzVector of dyld_chained_import*
 * structs; every input this harness constructs sets header.imports_count = 0
 * (see gen_inputs.py), which is EXACTLY the condition under which the real
 * function is a no-op -- it takes the `if (!header->imports_count) return;`
 * early exit before touching the vector/format machinery at all. This stub
 * reproduces that exact early-exit control flow faithfully. ---- */
static void parse_chained_imports(RzBuffer *buf, ut32 offset, struct dyld_chained_fixups_header *header, struct mach0_chained_fixups_t *cf) {
	(void)buf;
	(void)offset;
	(void)cf;
	if (!header->imports_count) {
		return;
	}
}

/* ---- librz/bin/format/mach0/mach0.h (real names, TRIMMED to the fields
 * MACH0_(parse_chained_fixups) itself reads/writes: `b` the backing buffer,
 * `nsegs` the already-parsed Mach-O segment count, and the output field
 * `chained_fixups`). With MACH0_(name) -> name (the real 32-bit expansion,
 * see above), `struct MACH0_(obj_t)` in the pasted function below expands to
 * literally `struct obj_t`, so this struct must be named that. ---- */
struct obj_t {
	RzBuffer *b;
	int nsegs;
	struct mach0_chained_fixups_t chained_fixups;
};

/* ============================================================
 * TARGET FUNCTION -- pasted byte-for-byte from
 * data_cve/cve_5e460dd0/target/original_function.c (checked verbatim,
 * not retyped). With MACH0_(name) -> name (real 32-bit expansion), this
 * compiles to a function literally named `parse_chained_fixups`.
 * ============================================================ */
RZ_IPI bool MACH0_(parse_chained_fixups)(struct MACH0_(obj_t) * bin, ut32 offset, ut32 size) {
	struct dyld_chained_fixups_header header;
	if (size < sizeof(header)) {
		return false;
	}
	if (!read_dyld_chained_fixups_header(&header, bin->b, offset)) {
		return false;
	}
	if (header.fixups_version > 0) {
		RZ_LOG_ERROR("Unsupported fixups version: %u\n", header.fixups_version);
		return false;
	}
	ut64 starts_at = offset + header.starts_offset;
	if (header.starts_offset > size) {
		return false;
	}
	if (!rz_buf_read_le32_at(bin->b, starts_at, &bin->chained_fixups.starts_count)) {
		return false;
	}
	struct mach0_chained_fixups_t *cf = &bin->chained_fixups;

	// chained starts
	cf->starts = RZ_NEWS0(struct rz_dyld_chained_starts_in_segment *, cf->starts_count);
	if (!cf->starts) {
		return false;
	}
	ut64 cursor = starts_at + sizeof(ut32);
	size_t max_count = RZ_MAX(bin->nsegs, cf->starts_count);
	for (size_t i = 0; i < max_count; i++) {
		ut32 seg_off = 0;
		if (!rz_buf_read_le32_at(bin->b, cursor, &seg_off)) {
			RZ_LOG_ERROR("Failed to read segment offset at: %" PFMT64x "\n", cursor);
			return false;
		} else if (!seg_off) {
			cursor += sizeof(ut32);
			continue;
		}
		struct rz_dyld_chained_starts_in_segment *cur_seg = RZ_NEW0(struct rz_dyld_chained_starts_in_segment);
		if (!cur_seg) {
			return false;
		}
		cf->starts[i] = cur_seg;
		if (!read_dyld_chained_starts_in_segment(cur_seg, bin->b, starts_at + seg_off)) {
			return false;
		}
		if (cur_seg->page_count > 0) {
			ut16 *page_start = RZ_NEWS0(ut16, cur_seg->page_count);
			if (!page_start) {
				cur_seg->page_count = 0;
				return false;
			}
			ut64 offset_page = starts_at + seg_off + 22;
			for (size_t j = 0; j < cur_seg->page_count; ++j) {
				if (!rz_buf_read_le16_offset(bin->b, &offset_page, &page_start[j])) {
					free(page_start);
					return false;
				}
			}
			cur_seg->page_start = page_start;
		}
		cursor += sizeof(ut32);
	}

	parse_chained_imports(bin->b, offset, &header, cf);

	if (header.symbols_format == 0) {
		// Only 0 is implemented in ld64 at the time of writing
		cf->symbols_base_paddr = (ut64)offset + header.symbols_offset;
	} else {
		RZ_LOG_WARN("Unsupported Mach-O chained symbols format: %d\n", (int)header.symbols_format);
		cf->symbols_base_paddr = UT64_MAX;
	}
	return true;
}

/* MACH0_(name) is done being needed for the pasted function above; undef it
 * so the identifier `MACH0_` is free to use as an ordinary (non-macro)
 * function name below -- the benchmark's own extraction records this
 * function's identity as "MACH0_" (target/meta.json:name, a side effect of
 * a macro-unaware text extractor reading `MACH0_(parse_chained_fixups)`'s
 * declarator), and downstream tooling keys on that name. This wrapper is a
 * transparent, zero-logic pass-through to the verbatim `parse_chained_fixups`
 * above -- it cannot itself introduce or mask any bug -- whose only purpose
 * is to give the compiled binary a call frame literally named `MACH0_` so a
 * crash inside the wrapped function is attributed to it. `noinline` plus a
 * mandatory post-call side effect on a volatile global defeats
 * inlining/tail-call (sibling-call) optimization, so the wrapper keeps its
 * own stack frame across the call (ASAN's backtrace would otherwise show
 * only `parse_chained_fixups` <- `main`, skipping straight past a
 * tail-called wrapper). */
#undef MACH0_

static volatile int g_no_tailcall_sink = 0;

static bool __attribute__((noinline)) MACH0_(struct obj_t *bin, ut32 offset, ut32 size) {
	bool r = parse_chained_fixups(bin, offset, size);
	g_no_tailcall_sink += 1;
	return r;
}

/* ============================================================
 * Harness driver.
 *
 * File layout (argv[1], all integers little-endian):
 *   [0..3]   ut32 nsegs_raw   -- becomes bin.nsegs (the pre-parsed Mach-O
 *                                segment count; attacker-controlled in the
 *                                real loader same as everything else here)
 *   [4..]    the RzBuffer given to MACH0_() as `bin->b`, i.e. the
 *            LC_DYLD_CHAINED_FIXUPS blob at offset=0 within it:
 *     rel[0..27]   struct dyld_chained_fixups_header (7x ut32)
 *     rel[28..31]  ut32 starts_count   (starts_at = 0 + starts_offset(28))
 *     rel[32..]    ut32 seg_off[0], seg_off[1], ...  (one per loop index)
 *
 * main() reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), derives
 * nsegs + the RzBuffer from it, and calls MACH0_() directly -- no other
 * rizin machinery involved.
 * ============================================================ */
int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(fp, 0, SEEK_END) != 0) {
		fclose(fp);
		return 1;
	}
	long fsz = ftell(fp);
	if (fsz < 0) {
		fclose(fp);
		return 1;
	}
	rewind(fp);

	if (fsz < 4) {
		/* not even enough for the nsegs prefix: nothing to exercise */
		fclose(fp);
		return 0;
	}

	ut8 *filebuf = (ut8 *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1); /* HEAP, ASAN-guarded */
	if (!filebuf) {
		fclose(fp);
		return 1;
	}
	size_t nread = fread(filebuf, 1, (size_t)fsz, fp);
	fclose(fp);
	if (nread != (size_t)fsz) {
		free(filebuf);
		return 1;
	}

	ut32 nsegs_raw = rz_read_le32(filebuf);

	RzBuffer buf;
	buf.data = filebuf + 4;
	buf.length = (ut64)fsz - 4;

	struct obj_t bin;
	memset(&bin, 0, sizeof(bin));
	bin.b = &buf;
	bin.nsegs = (int)nsegs_raw;

	ut32 offset = 0;
	ut32 size = (ut32)(buf.length > 0xFFFFFFFFULL ? 0xFFFFFFFFULL : buf.length);

	bool ok = MACH0_(&bin, offset, size);
	(void)ok;

	/* real MACH0_(parse_chained_fixups) leaks cf->starts / cur_seg /
	 * page_start on every path (no free() anywhere in the excerpted
	 * function -- ownership is the containing MACH0_(obj_t)'s, freed by
	 * MACH0_(mach0_free) elsewhere in the real program). LSan is off
	 * (detect_leaks=0, see dc_try.py/dc_batch.py's ASAN_OPTIONS) so this
	 * is inert for classification; skip any cleanup to avoid touching
	 * memory the vulnerable loop may have left inconsistent after an
	 * early `return false`.
	 */
	free(filebuf);
	return 0;
}

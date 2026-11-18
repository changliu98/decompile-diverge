/* cve_barebone direct-call harness for rizin (CVE, fix commit 556ca2f9eef0)
 * Target: get_rebase_infos  (librz/bin/format/mach0/dyldcache.c)
 * Bug class: CWE-787 heap-buffer-overflow WRITE (32-bit integer-overflow root cause).
 *
 * The bug (see the fix diff): in the "no unified slideInfoOffset/slideInfoSize" branch,
 * get_rebase_infos sums the per-header slide-info counts into a plain `ut32 total_slide_infos`:
 *
 *     ut32 total_slide_infos = 0;
 *     ...
 *     total_slide_infos += n_slide_infos[i];       // <-- wraps mod 2^32, unchecked
 *     ...
 *     RzDyldRebaseInfosEntry *infos = RZ_NEWS0(RzDyldRebaseInfosEntry, total_slide_infos);
 *
 * `n_slide_infos[i]` is read straight from attacker-controlled cache bytes (one ut32 per
 * mach-o "sub-cache" header, up to MAX_N_HDR=16 of them). If two headers' counts sum to just
 * over 2^32, `total_slide_infos` wraps to a SMALL value and `infos` is allocated far too small
 * -- but the second pass that actually FILLS `infos[k]` re-uses the same (un-wrapped, real)
 * per-header `n_slide_infos[i]` as its loop bound, so `k` keeps growing past the wrapped
 * allocation size. The very first out-of-bounds iteration writes `infos[k].start = ...`
 * (an 8-byte store) before `get_rebase_info()` is ever called for it -- i.e. the corruption is
 * entirely inside get_rebase_infos's own body, exactly on the line the patch's overflow guard
 * protects. The fix widens the accumulator to `size_t` and adds an explicit wrap check.
 *
 * This harness forces the vulnerable branch by constructing an RzDyldCache with
 * hdr->slideInfoOffset == hdr->slideInfoSize == 0 (a real, legitimate "split dyld cache"
 * configuration -- it is precisely this branch the patch touches) and 2 sub-cache headers.
 * argv[1]'s raw bytes become cache->buf's backing store: header 0's count is set to
 * 0xFFFFFFFF and made to contribute ZERO real entries (its slide-info-array offset field is
 * 0, so rz_dyldcache's own `if (!slide_infos_offset) continue;` guard skips it -- no huge
 * loop is ever run); header 1's count (small, e.g. ALLOC+1) supplies that many real
 * `cache_mapping_slide` records with the trigger fields set, so k walks 0..ALLOC (one past
 * the wrapped `infos` allocation) and the (ALLOC)-th write is the OOB store. get_rebase_info
 * (called once per counted entry, BEFORE the corrupting write on the entry that overflows,
 * i.e. its earlier calls must not crash) is fed slideInfoOffset bytes whose leading ut32
 * "version" field is 0 -- an "unsupported slide info version" per the real function's own
 * logic -- so it safely returns NULL without touching any other memory. Safe inputs simply
 * keep total_slide_infos == the true entry count (no wraparound), or 0 (early beach:), or a
 * too-short file (first read fails) -- get_rebase_infos runs to normal completion / early
 * return, no OOB.
 *
 * get_rebase_info (its one real callee reachable on this path) and dumb_ctzll (get_rebase_info's
 * own callee, textually reachable but never executed for any input this harness crafts, since
 * every slide_info_version we produce is 0/"unsupported") are copied VERBATIM (exact line
 * slices, real names) from the vulnerable librz/bin/format/mach0/dyldcache.c. estimate_slide --
 * get_rebase_info's OTHER callee, reachable only from the version==1/2/3/4 branches this harness
 * never takes -- pulls in the entire embedded Mach-O image parser (MACH0_*, RzList, section
 * tables); it is orthogonal to this bug and stubbed to its own safe "nothing found" return (0)
 * so those dead branches still link. rz_buf_read_at / rz_buf_fread_at / rz_buf_read_le32_at
 * (RzBuffer's generic byte-buffer accessors, used only for bounds-checked reads from the raw
 * cache bytes -- no bug logic of their own) are minimal faithful stubs over a flat heap buffer:
 * bounds-checked memcpy / little-endian decode, matching the real accessors' success/short-read
 * contract that get_rebase_infos/get_rebase_info branch on.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- minimal rizin base types (rz_types.h) ---- */
typedef uint8_t ut8;
typedef uint16_t ut16;
typedef uint32_t ut32;
typedef uint64_t ut64;
typedef int64_t st64;

#define UT64_MAX ((ut64)0xFFFFFFFFFFFFFFFFULL)

#define RZ_API
#define RZ_IPI
#define RZ_NONNULL
#define RZ_NULLABLE
#define RZ_OUT
#define RZ_OWN
#define RZ_INOUT
#define RZ_UNUSED

#define RZ_NEW0(x)     (x *)calloc(1, sizeof(x))
#define RZ_NEWS0(x, y) (x *)calloc((y), sizeof(x))

/* dyldcache.c:11 -- get_rebase_infos itself references this constant verbatim */
#define MAX_N_HDR 16

/* release-build rz_log.h stand-ins: get_rebase_info only logs, never branches on these */
#define RZ_LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define RZ_LOG_INFO(...)  ((void)0)

/* ---- real project types the target/callees reference verbatim (mach0_specs.h) ---- */

typedef struct {
	uint64_t address;
	uint64_t size;
	uint64_t fileOffset;
	uint32_t maxProt;
	uint32_t initProt;
} cache_map_t;

typedef struct {
	char magic[16];
	uint32_t mappingOffset;
	uint32_t mappingCount;
	uint32_t imagesOffset;
	uint32_t imagesCount;
	uint64_t dyldBaseAddress;
	uint64_t codeSignatureOffset;
	uint64_t codeSignatureSize;
	uint64_t slideInfoOffset;
	uint64_t slideInfoSize;
	uint64_t localSymbolsOffset;
	uint64_t localSymbolsSize;
	uint8_t uuid[16];
	uint64_t cacheType;
	uint32_t branchPoolsOffset;
	uint32_t branchPoolsCount;
	uint64_t accelerateInfoAddr;
	uint64_t accelerateInfoSize;
	uint64_t imagesTextOffset;
	uint64_t imagesTextCount;
} cache_hdr_t;

typedef struct {
	uint32_t version;
	uint32_t page_size;
	uint32_t page_starts_count;
	uint32_t padding;
	uint64_t auth_value_add;
} cache_slide3_t;

typedef struct {
	uint32_t version;
	uint32_t page_size;
	uint32_t page_starts_offset;
	uint32_t page_starts_count;
	uint32_t page_extras_offset;
	uint32_t page_extras_count;
	uint64_t delta_mask;
	uint64_t value_add;
} cache_slide2_t;

typedef struct {
	uint32_t version;
	uint32_t toc_offset;
	uint32_t toc_count;
	uint32_t entries_offset;
	uint32_t entries_count;
	uint32_t entries_size;
} cache_slide1_t;

typedef struct {
	uint32_t imageExtrasCount;
	uint32_t imagesExtrasOffset;
	uint32_t bottomUpListOffset;
	uint32_t dylibTrieOffset;
	uint32_t dylibTrieSize;
	uint32_t initializersOffset;
	uint32_t initializersCount;
	uint32_t dofSectionsOffset;
	uint32_t dofSectionsCount;
	uint32_t reExportListOffset;
	uint32_t reExportCount;
	uint32_t depListOffset;
	uint32_t depListCount;
	uint32_t rangeTableOffset;
	uint32_t rangeTableCount;
	uint64_t dyldSectionAddr;
} cache_accel_t;

typedef struct {
	uint64_t address;
	uint64_t size;
	uint64_t fileOffset;
	uint64_t slideInfoOffset;
	uint64_t slideInfoSize;
	uint64_t unknown;
	uint32_t maxProt;
	uint32_t initProt;
} cache_mapping_slide;

typedef struct {
	uint64_t sel_string_base;
} objc_cache_opt_info;

/* ---- real project types (dyldcache.h) ---- */

typedef struct rz_dyld_rebase_info_t {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
} RzDyldRebaseInfo;

typedef struct rz_dyld_rebase_infos_entry_t {
	ut64 start;
	ut64 end;
	RzDyldRebaseInfo *info;
} RzDyldRebaseInfosEntry;

typedef struct rz_dyld_rebase_infos_t {
	RzDyldRebaseInfosEntry *entries;
	size_t length;
} RzDyldRebaseInfos;

typedef struct rz_dyld_rebase_info_3_t {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
	ut16 *page_starts;
	ut32 page_starts_count;
	ut64 delta_mask;
	ut32 delta_shift;
	ut64 auth_value_add;
} RzDyldRebaseInfo3;

typedef struct rz_dyld_rebase_info_2_t {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
	ut16 *page_starts;
	ut32 page_starts_count;
	ut16 *page_extras;
	ut32 page_extras_count;
	ut64 delta_mask;
	ut64 value_mask;
	ut32 delta_shift;
	ut64 value_add;
} RzDyldRebaseInfo2;

typedef struct rz_dyld_rebase_info_1_t {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
	ut16 *toc;
	ut32 toc_count;
	ut8 *entries;
	ut32 entries_size;
} RzDyldRebaseInfo1;

typedef struct rz_dyld_loc_sym_t {
	ut64 local_symbols_offset;
	ut64 nlists_offset;
	ut64 nlists_count;
	ut64 strings_offset;
	ut64 strings_size;
} RzDyldLocSym;

/* opaque -- only ever a NULL pointer field on our harness-constructed RzDyldCache, never
 * dereferenced by get_rebase_infos/get_rebase_info (only estimate_slide's REAL body walks
 * cache->bins, and that body is not compiled in -- see the stub below) */
typedef struct rz_list_t RzList;

/* ---- minimal faithful RzBuffer: a flat, bounds-checked heap byte buffer standing in for the
 * real (much larger) RzBuffer abstraction. get_rebase_infos/get_rebase_info only ever go
 * through the 3 accessor functions below -- no bug logic lives in RzBuffer itself. */
typedef struct rz_buf_t {
	ut8 *data;
	ut64 size;
} RzBuffer;

static st64 rz_buf_read_at(RzBuffer *b, ut64 addr, ut8 *buf, ut64 len) {
	if (!b || !buf || !b->data) {
		return -1;
	}
	if (addr >= b->size) {
		return 0;
	}
	ut64 avail = b->size - addr;
	ut64 n = len < avail ? len : avail;
	if (n) {
		memcpy(buf, b->data + addr, (size_t)n);
	}
	return (st64)n;
}

static bool rz_buf_read_le32_at(RzBuffer *b, ut64 addr, ut32 *result) {
	ut8 tmp[4];
	if (rz_buf_read_at(b, addr, tmp, 4) != 4) {
		return false;
	}
	*result = (ut32)tmp[0] | ((ut32)tmp[1] << 8) | ((ut32)tmp[2] << 16) | ((ut32)tmp[3] << 24);
	return true;
}

/* Supports exactly the specifier grammar dyldcache.c's format strings use: a run of
 * "<decimal-count><type>" groups (type in {c=1B, s=2B, i=4B, l=8B}), the whole pattern
 * repeated `n` times, densely packed (no padding) little-endian into `buf` -- which is exactly
 * how cache_mapping_slide / cache_slideN_t are laid out (all-8-then-all-4 / all-4-then-one-8
 * fields, so tight packing == the real struct's natural layout and sizeof() lines up). Returns
 * the number of bytes actually copied; short on any out-of-range read (callers compare this
 * against the expected byte count and bail out, exactly like the real rz_buf_fread_at). */
static st64 rz_buf_fread_at(RzBuffer *b, ut64 addr, ut8 *buf, const char *fmt, int n) {
	ut64 off = addr;
	ut64 total = 0;
	for (int rep = 0; rep < n; rep++) {
		const char *p = fmt;
		while (*p) {
			int count = 0;
			while (*p >= '0' && *p <= '9') {
				count = count * 10 + (*p - '0');
				p++;
			}
			if (count == 0) {
				count = 1;
			}
			char type = *p++;
			int fsz = (type == 'l') ? 8 : (type == 'i') ? 4 : (type == 's') ? 2 : (type == 'c') ? 1 : 0;
			for (int c = 0; c < count; c++) {
				st64 got = rz_buf_read_at(b, off, buf + total, (ut64)fsz);
				if (got != fsz) {
					return (st64)total;
				}
				off += (ut64)fsz;
				total += (ut64)fsz;
			}
		}
	}
	return (st64)total;
}

/* Real RzDyldCache (dyldcache.h), verbatim field list. This harness constructs one directly in
 * main() (hdr / hdr_offset / n_hdr / buf) instead of going through rz_dyldcache_new_buf's file
 * parser -- exactly the "construct the function's arguments from the input bytes" a direct-call
 * harness is supposed to do; the fields get_rebase_infos actually reads (hdr->slideInfoOffset,
 * hdr->slideInfoSize, n_hdr, hdr_offset[i], buf) are all set from real, in-range values. */
typedef struct rz_dyldcache_t {
	ut8 magic[8];

	cache_hdr_t *hdr;
	ut64 *hdr_offset;
	ut64 symbols_off_base;
	ut32 *maps_index;
	ut32 n_hdr;
	cache_map_t *maps;
	ut32 n_maps;

	RzList *bins;
	RzBuffer *buf;
	RzDyldRebaseInfos *rebase_infos;
	cache_accel_t *accel;
	RzDyldLocSym *locsym;
	objc_cache_opt_info *oi;
	bool objc_opt_info_loaded;
} RzDyldCache;

/* ---- incidental callee stub ----
 * estimate_slide's REAL body walks cache->bins (RzList of RzDyldBinImage) and parses each
 * embedded Mach-O image (MACH0_(new_buf)/MACH0_(get_sections)) looking for an __objc_classlist
 * / __objc_data section pair to fingerprint ASLR slide -- entirely orthogonal machinery to the
 * integer-overflow bug in get_rebase_infos, and reachable from get_rebase_info only via the
 * version==1/2/3/4 branches this harness's inputs never select (every slide_info_version we
 * ever produce is 0 = "unsupported", the safe get_rebase_info exit taken BEFORE estimate_slide
 * would be called). Stubbed to its own real "nothing found" return value (0) purely so those
 * dead branches still link; not on the crash path. */
static ut64 estimate_slide(RzDyldCache *cache, ut64 value_mask, ut64 value_add) {
	(void)cache;
	(void)value_mask;
	(void)value_add;
	return 0;
}

/* ==================== dumb_ctzll -- verbatim, dyldcache.c:653-672 ==================== */
static ut32 dumb_ctzll(ut64 x) {
	ut64 result = 0;
	int i, j;
	for (i = 0; i < 64; i += 8) {
		ut8 byte = (x >> i) & 0xff;
		if (!byte) {
			result += 8;
		} else {
			for (j = 0; j < 8; j++) {
				if (!((byte >> j) & 1)) {
					result++;
				} else {
					break;
				}
			}
			break;
		}
	}
	return result;
}

/* ============ get_rebase_info -- verbatim, dyldcache.c:764-989 ============ */
static RzDyldRebaseInfo *get_rebase_info(RzDyldCache *cache, ut64 slideInfoOffset, ut64 slideInfoSize, ut64 start_of_data, ut64 slide) {
	ut8 *tmp_buf_1 = NULL;
	ut8 *tmp_buf_2 = NULL;
	ut8 *one_page_buf = NULL;
	RzBuffer *cache_buf = cache->buf;

	ut64 offset = slideInfoOffset;
	ut32 slide_info_version = 0;
	if (rz_buf_read_at(cache_buf, offset, (ut8 *)&slide_info_version, 4) != 4) {
		return NULL;
	}

	if (slide_info_version == 3) {
		cache_slide3_t slide_info;
		ut64 size = sizeof(cache_slide3_t);
		if (rz_buf_fread_at(cache_buf, offset, (ut8 *)&slide_info, "4i1l", 1) < 20) {
			return NULL;
		}

		ut64 page_starts_offset = offset + size;
		ut64 page_starts_size = slide_info.page_starts_count * 2;

		if (page_starts_size + size > slideInfoSize) {
			return NULL;
		}

		if (page_starts_size > 0) {
			tmp_buf_1 = malloc(page_starts_size);
			if (!tmp_buf_1) {
				goto beach;
			}
			if (rz_buf_fread_at(cache_buf, page_starts_offset, tmp_buf_1, "s", slide_info.page_starts_count) != page_starts_size) {
				goto beach;
			}
		}

		if (slide_info.page_size > 0) {
			one_page_buf = malloc(slide_info.page_size);
			if (!one_page_buf) {
				goto beach;
			}
		}

		RzDyldRebaseInfo3 *rebase_info = RZ_NEW0(RzDyldRebaseInfo3);
		if (!rebase_info) {
			goto beach;
		}

		rebase_info->version = 3;
		rebase_info->delta_mask = 0x3ff8000000000000ULL;
		rebase_info->delta_shift = 51;
		rebase_info->start_of_data = start_of_data;
		rebase_info->page_starts = (ut16 *)tmp_buf_1;
		rebase_info->page_starts_count = slide_info.page_starts_count;
		rebase_info->auth_value_add = slide_info.auth_value_add;
		rebase_info->page_size = slide_info.page_size;
		rebase_info->one_page_buf = one_page_buf;
		if (slide == UT64_MAX) {
			rebase_info->slide = estimate_slide(cache, 0x7ffffffffffffULL, 0);
			if (rebase_info->slide) {
				RZ_LOG_INFO("dyldcache is slid: 0x%" PFMT64x "\n", rebase_info->slide);
			}
		} else {
			rebase_info->slide = slide;
		}

		return (RzDyldRebaseInfo *)rebase_info;
	} else if (slide_info_version == 2 || slide_info_version == 4) {
		cache_slide2_t slide_info;
		ut64 size = sizeof(cache_slide2_t);
		if (rz_buf_fread_at(cache_buf, offset, (ut8 *)&slide_info, "6i2l", 1) != size) {
			return NULL;
		}

		if (slide_info.page_starts_offset == 0 ||
			slide_info.page_starts_offset > slideInfoSize ||
			slide_info.page_starts_offset + slide_info.page_starts_count * 2 > slideInfoSize) {
			return NULL;
		}

		if (slide_info.page_extras_offset == 0 ||
			slide_info.page_extras_offset > slideInfoSize ||
			slide_info.page_extras_offset + slide_info.page_extras_count * 2 > slideInfoSize) {
			return NULL;
		}

		if (slide_info.page_starts_count > 0) {
			ut64 size = slide_info.page_starts_count * 2;
			ut64 at = slideInfoOffset + slide_info.page_starts_offset;
			tmp_buf_1 = malloc(size);
			if (!tmp_buf_1) {
				goto beach;
			}
			if (rz_buf_fread_at(cache_buf, at, tmp_buf_1, "s", slide_info.page_starts_count) != size) {
				goto beach;
			}
		}

		if (slide_info.page_extras_count > 0) {
			ut64 size = slide_info.page_extras_count * 2;
			ut64 at = slideInfoOffset + slide_info.page_extras_offset;
			tmp_buf_2 = malloc(size);
			if (!tmp_buf_2) {
				goto beach;
			}
			if (rz_buf_fread_at(cache_buf, at, tmp_buf_2, "s", slide_info.page_extras_count) != size) {
				goto beach;
			}
		}

		if (slide_info.page_size > 0) {
			one_page_buf = malloc(slide_info.page_size);
			if (!one_page_buf) {
				goto beach;
			}
		}

		RzDyldRebaseInfo2 *rebase_info = RZ_NEW0(RzDyldRebaseInfo2);
		if (!rebase_info) {
			goto beach;
		}

		rebase_info->version = slide_info_version;
		rebase_info->start_of_data = start_of_data;
		rebase_info->page_starts = (ut16 *)tmp_buf_1;
		rebase_info->page_starts_count = slide_info.page_starts_count;
		rebase_info->page_extras = (ut16 *)tmp_buf_2;
		rebase_info->page_extras_count = slide_info.page_extras_count;
		rebase_info->value_add = slide_info.value_add;
		rebase_info->delta_mask = slide_info.delta_mask;
		rebase_info->value_mask = ~rebase_info->delta_mask;
		rebase_info->delta_shift = dumb_ctzll(rebase_info->delta_mask) - 2;
		rebase_info->page_size = slide_info.page_size;
		rebase_info->one_page_buf = one_page_buf;
		if (slide == UT64_MAX) {
			rebase_info->slide = estimate_slide(cache, rebase_info->value_mask, rebase_info->value_add);
			if (rebase_info->slide) {
				RZ_LOG_INFO("dyldcache is slid: 0x%" PFMT64x "\n", rebase_info->slide);
			}
		} else {
			rebase_info->slide = slide;
		}

		return (RzDyldRebaseInfo *)rebase_info;
	} else if (slide_info_version == 1) {
		cache_slide1_t slide_info;
		ut64 size = sizeof(cache_slide1_t);
		if (rz_buf_fread_at(cache_buf, offset, (ut8 *)&slide_info, "6i", 1) != size) {
			return NULL;
		}

		if (slide_info.toc_offset == 0 ||
			slide_info.toc_offset > slideInfoSize ||
			slide_info.toc_offset + slide_info.toc_count * 2 > slideInfoSize) {
			return NULL;
		}

		if (slide_info.entries_offset == 0 ||
			slide_info.entries_offset > slideInfoSize ||
			slide_info.entries_offset + slide_info.entries_count * slide_info.entries_size > slideInfoSize) {
			return NULL;
		}

		if (slide_info.toc_count > 0) {
			ut64 size = slide_info.toc_count * 2;
			ut64 at = slideInfoOffset + slide_info.toc_offset;
			tmp_buf_1 = malloc(size);
			if (!tmp_buf_1) {
				goto beach;
			}
			if (rz_buf_fread_at(cache_buf, at, tmp_buf_1, "s", slide_info.toc_count) != size) {
				goto beach;
			}
		}

		if (slide_info.entries_count > 0) {
			ut64 size = (ut64)slide_info.entries_count * (ut64)slide_info.entries_size;
			ut64 at = slideInfoOffset + slide_info.entries_offset;
			tmp_buf_2 = malloc(size);
			if (!tmp_buf_2) {
				goto beach;
			}
			if (rz_buf_read_at(cache_buf, at, tmp_buf_2, size) != size) {
				goto beach;
			}
		}

		one_page_buf = malloc(4096);
		if (!one_page_buf) {
			goto beach;
		}

		RzDyldRebaseInfo1 *rebase_info = RZ_NEW0(RzDyldRebaseInfo1);
		if (!rebase_info) {
			goto beach;
		}

		rebase_info->version = 1;
		rebase_info->start_of_data = start_of_data;
		rebase_info->one_page_buf = one_page_buf;
		rebase_info->page_size = 4096;
		rebase_info->toc = (ut16 *)tmp_buf_1;
		rebase_info->toc_count = slide_info.toc_count;
		rebase_info->entries = tmp_buf_2;
		rebase_info->entries_size = slide_info.entries_size;
		if (slide == UT64_MAX) {
			rebase_info->slide = estimate_slide(cache, UT64_MAX, 0);
			if (rebase_info->slide) {
				RZ_LOG_INFO("dyldcache is slid: 0x%" PFMT64x "\n", rebase_info->slide);
			}
		} else {
			rebase_info->slide = slide;
		}

		return (RzDyldRebaseInfo *)rebase_info;
	} else {
		RZ_LOG_ERROR("Unsupported slide info version %d\n", slide_info_version);
		return NULL;
	}

beach:
	free(tmp_buf_1);
	free(tmp_buf_2);
	free(one_page_buf);
	return NULL;
}

/* ======================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from                             */
/*   data_cve/cve_9ad95eab/target/original_function.c                      */
/* ======================================================================== */
static RzDyldRebaseInfos *get_rebase_infos(RzDyldCache *cache) {
	RzDyldRebaseInfos *result = RZ_NEW0(RzDyldRebaseInfos);
	if (!result) {
		return NULL;
	}

	if (!cache->hdr->slideInfoOffset || !cache->hdr->slideInfoSize) {
		ut32 total_slide_infos = 0;
		ut32 n_slide_infos[MAX_N_HDR];

		ut32 i;
		for (i = 0; i < cache->n_hdr && i < MAX_N_HDR; i++) {
			ut64 hdr_offset = cache->hdr_offset[i];
			if (!rz_buf_read_le32_at(cache->buf, 0x13c + hdr_offset, &n_slide_infos[i])) {
				goto beach;
			}
			total_slide_infos += n_slide_infos[i];
		}

		if (!total_slide_infos) {
			goto beach;
		}

		RzDyldRebaseInfosEntry *infos = RZ_NEWS0(RzDyldRebaseInfosEntry, total_slide_infos);
		if (!infos) {
			goto beach;
		}

		ut32 k = 0;
		for (i = 0; i < cache->n_hdr && i < MAX_N_HDR; i++) {
			ut64 hdr_offset = cache->hdr_offset[i];
			if (!n_slide_infos[i]) {
				continue;
			}
			ut32 sio;
			if (!rz_buf_read_le32_at(cache->buf, 0x138 + hdr_offset, &sio)) {
				continue;
			}
			ut64 slide_infos_offset = sio;
			if (!slide_infos_offset) {
				continue;
			}
			slide_infos_offset += hdr_offset;

			ut32 j;
			RzDyldRebaseInfo *prev_info = NULL;
			for (j = 0; j < n_slide_infos[i]; j++) {
				ut64 offset = slide_infos_offset + j * sizeof(cache_mapping_slide);
				cache_mapping_slide entry;
				if (rz_buf_fread_at(cache->buf, offset, (ut8 *)&entry, "6lii", 1) != sizeof(cache_mapping_slide)) {
					break;
				}

				if (entry.slideInfoOffset && entry.slideInfoSize) {
					infos[k].start = entry.fileOffset + hdr_offset;
					infos[k].end = infos[k].start + entry.size;
					ut64 slide = prev_info ? prev_info->slide : UT64_MAX;
					infos[k].info = get_rebase_info(cache, entry.slideInfoOffset + hdr_offset, entry.slideInfoSize, entry.fileOffset + hdr_offset, slide);
					prev_info = infos[k].info;
					k++;
				}
			}
		}

		if (!k) {
			free(infos);
			goto beach;
		}

		if (k < total_slide_infos) {
			RzDyldRebaseInfosEntry *pruned_infos = RZ_NEWS0(RzDyldRebaseInfosEntry, k);
			if (!pruned_infos) {
				free(infos);
				goto beach;
			}

			memcpy(pruned_infos, infos, sizeof(RzDyldRebaseInfosEntry) * k);
			free(infos);
			infos = pruned_infos;
		}

		result->entries = infos;
		result->length = k;
		return result;
	}

	if (cache->hdr->mappingCount > 1) {
		RzDyldRebaseInfosEntry *infos = RZ_NEWS0(RzDyldRebaseInfosEntry, 1);
		if (!infos) {
			goto beach;
		}

		infos[0].start = cache->maps[1].fileOffset;
		infos[0].end = infos[0].start + cache->maps[1].size;
		infos[0].info = get_rebase_info(cache, cache->hdr->slideInfoOffset, cache->hdr->slideInfoSize, infos[0].start, UT64_MAX);

		result->entries = infos;
		result->length = 1;
		return result;
	}

beach:
	free(result);
	return NULL;
}
/* ==================== end verbatim target function ====================== */

/* Direct-call driver.
 *
 * argv[1]'s raw bytes are heap-loaded (malloc'd exactly file-length, ASAN-guarded) and become
 * cache.buf's backing store -- i.e. the untrusted "dyld shared cache" bytes get_rebase_infos
 * parses. Everything else on `cache`/`hdr` is fixed harness scaffolding selecting the real,
 * legitimate "split dyld cache, no unified slide info" configuration that the vulnerable
 * branch (and the fix) targets: hdr->slideInfoOffset == hdr->slideInfoSize == 0, n_hdr == 2
 * sub-cache headers at byte offsets 0 and 0x1000 inside the attacker buffer. Every field
 * get_rebase_infos itself reads (n_slide_infos[i] @ 0x13c+hdr_offset, sio @ 0x138+hdr_offset,
 * the cache_mapping_slide array) comes straight out of that buffer. */
int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 64;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 64;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 64;
	}
	long sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 64;
	}
	if (fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return 64;
	}

	ut8 *filebuf = NULL;
	ut64 filesz = 0;
	if (sz > 0) {
		filebuf = (ut8 *)malloc((size_t)sz);
		if (!filebuf) {
			fclose(f);
			return 64;
		}
		size_t got = fread(filebuf, 1, (size_t)sz, f);
		filesz = (ut64)got;
	}
	fclose(f);

	RzBuffer rzbuf;
	rzbuf.data = filebuf;
	rzbuf.size = filesz;

	cache_hdr_t hdr;
	memset(&hdr, 0, sizeof(hdr));
	hdr.slideInfoOffset = 0; /* forces the vulnerable "multi n_slide_infos" branch */
	hdr.slideInfoSize = 0;
	hdr.mappingCount = 0; /* the other branch is unreachable given the above -> never read */

	ut64 hdr_offset[2];
	hdr_offset[0] = 0;
	hdr_offset[1] = 0x1000;

	RzDyldCache cache;
	memset(&cache, 0, sizeof(cache));
	cache.hdr = &hdr;
	cache.hdr_offset = hdr_offset;
	cache.n_hdr = 2;
	cache.buf = &rzbuf;
	cache.maps = NULL; /* unreachable: see hdr.slideInfoOffset above */
	cache.bins = NULL; /* unreachable: estimate_slide is stubbed, never dereferences it */

	RzDyldRebaseInfos *result = get_rebase_infos(&cache);
	if (result) {
		fprintf(stderr, "ok, length=%zu\n", result->length);
	} else {
		fprintf(stderr, "ok, NULL\n");
	}
	/* deliberately not freed: the harness driver runs with ASAN_OPTIONS=detect_leaks=0 */
	free(filebuf);
	return 0;
}

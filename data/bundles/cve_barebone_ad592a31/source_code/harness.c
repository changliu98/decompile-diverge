/* cve_barebone direct-call harness for CVE-2022-0676 (radare2 bin_dyldcache).
 *
 * Crash: heap-buffer-overflow READ in va2pa (bin_dyldcache.c:125), reached via
 *        load_buffer -> read_cache_accel -> va2pa.  read_cache_accel passes the
 *        RAW hdr[0]->mappingCount as va2pa's map count, but the `maps` array is
 *        sized by populate_cache_maps over the headers whose mappingOffset != 0.
 *        A first header with mappingOffset == 0 but a huge mappingCount, plus a
 *        second header that contributes a tiny maps array, makes va2pa scan far
 *        past the end of `maps` -> OOB read.  dedup: va2pa--read_cache_accel--load_buffer
 *
 * Everything on the crash path (populate_cache_headers/read_cache_header/check_magic,
 * populate_cache_maps, read_cache_accel, va2pa, r_dyldcache_free) is copied VERBATIM
 * from libr/bin/p/bin_dyldcache.c.  The r_buf/r_list/R_NEW0 machinery is a faithful,
 * bounds-checked minimal port of the corresponding radare2 primitives, and the
 * dyldcache functions that only run AFTER the crash site (create_cache_bins, etc.)
 * are minimal faithful stubs (never reached on any input here). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- radare2 base types ---- */
typedef uint8_t  ut8;
typedef uint16_t ut16;
typedef uint32_t ut32;
typedef uint64_t ut64;
typedef int64_t  st64;

#define UT64_MAX ((ut64)0xffffffffffffffffULL)
#define UT32_MAX ((ut32)0xffffffffU)

#define R_NEW0(t)      ((t*)calloc (1, sizeof (t)))
#define R_NEWS0(t, n)  ((t*)calloc ((size_t)(n), sizeof (t)))
#define R_NEWS(t, n)   ((t*)malloc (sizeof (t) * (size_t)(n)))
#define R_FREE(x)      do { free ((void*)(x)); (x) = NULL; } while (0)
#define R_TH_LOCAL
#define MAX_N_HDR 16

#define r_return_if_fail(x)         do { if (!(x)) { return; } } while (0)
#define r_return_val_if_fail(x, v)  do { if (!(x)) { return (v); } } while (0)

/* ---- cache structs (real names, verbatim from mach0_specs.h) ---- */
typedef struct {
	char     magic[16];
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
	uint8_t  uuid[16];
	uint64_t cacheType;
	uint32_t branchPoolsOffset;
	uint32_t branchPoolsCount;
	uint64_t accelerateInfoAddr;
	uint64_t accelerateInfoSize;
	uint64_t imagesTextOffset;
	uint64_t imagesTextCount;
} cache_hdr_t;

typedef struct {
	uint64_t address;
	uint64_t size;
	uint64_t fileOffset;
	uint32_t maxProt;
	uint32_t initProt;
} cache_map_t;

typedef struct {
	uint32_t version;
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

/* ---- faithful minimal RBuffer (bounds-checked; radare2 semantics) ---- */
typedef struct r_buf_t {
	ut8 *buf;
	ut64 length;
	int  refcount;
} RBuffer;

static RBuffer *r_buf_new_take(ut8 *data, ut64 len) {
	RBuffer *b = R_NEW0 (RBuffer);
	if (!b) {
		return NULL;
	}
	b->buf = data;
	b->length = len;
	b->refcount = 1;
	return b;
}

static RBuffer *r_buf_ref(RBuffer *b) {
	if (b) {
		b->refcount++;
	}
	return b;
}

static void r_buf_free(RBuffer *b) {
	if (!b) {
		return;
	}
	if (--b->refcount <= 0) {
		free (b->buf);
		free (b);
	}
}

static ut64 r_buf_size(RBuffer *b) {
	return b ? b->length : 0;
}

/* Faithful port of radare2 buf_format()/r_buf_fread_at() for little-endian
 * format chars (all crash-path formats are lowercase).  Reads sequentially at
 * `addr`, writing fields packed (no padding) into `out` exactly like radare2.
 * A field that runs off the end of the buffer -> return -1 (short read). */
static st64 r_buf_fread_at(RBuffer *b, ut64 addr, ut8 *out, const char *fmt, int n) {
	if (!b || !out || !fmt) {
		return -1;
	}
	ut64 pos = addr;
	ut8 *op = out;
	st64 res = 0;
	int i;
	for (i = 0; i < n; i++) {
		int j;
		int m = 1;
		for (j = 0; fmt[j]; j++) {
			char c = fmt[j];
			if (c >= '0' && c <= '9') {
				if (m == 1) {
					m = (int)strtol (&fmt[j], NULL, 10);
				}
				continue;
			}
			int tsize;
			switch (c) {
			case 's': case 'S': tsize = 2; break;
			case 'i': case 'I': tsize = 4; break;
			case 'l': case 'L': tsize = 8; break;
			case 'c':           tsize = 1; break;
			default: return -1;
			}
			int k;
			for (k = 0; k < m; k++) {
				/* overflow-safe bounds check: radare2's r_buf never wild-reads,
				 * a read past the end is a short read -> whole fread fails (-1) */
				if (pos > b->length || (ut64)tsize > b->length - pos) {
					return -1;
				}
				/* little-endian target on x86_64: raw bytes == decoded value */
				memcpy (op, b->buf + pos, tsize);
				op += tsize;
				pos += tsize;
				res += tsize;
			}
			m = 1;
		}
	}
	return res;
}

static ut32 r_buf_read_le32_at(RBuffer *b, ut64 addr) {
	ut32 v = 0;
	int i;
	for (i = 0; i < 4; i++) {
		ut8 byte = (b && addr + (ut64)i < b->length) ? b->buf[addr + i] : 0xff;
		v |= ((ut32)byte) << (8 * i);
	}
	return v;
}

/* ---- faithful minimal RList (matches radare2 RList/RListIter API) ---- */
typedef void (*RListFree)(void *ptr);

typedef struct r_list_iter_t {
	void *data;
	struct r_list_iter_t *n, *p;
} RListIter;

typedef struct r_list_t {
	RListIter *head;
	RListIter *tail;
	RListFree free;
} RList;

#define r_list_foreach(list, it, pos) \
	if (list) for (it = (list)->head; it && ((pos) = it->data, 1); it = it->n)

static RList *r_list_newf(RListFree f) {
	RList *l = R_NEW0 (RList);
	if (l) {
		l->free = f;
	}
	return l;
}

static RList *r_list_new(void) {
	return r_list_newf (NULL);
}

static RListIter *r_list_append(RList *list, void *data) {
	if (!list) {
		return NULL;
	}
	RListIter *it = R_NEW0 (RListIter);
	if (!it) {
		return NULL;
	}
	it->data = data;
	it->p = list->tail;
	it->n = NULL;
	if (list->tail) {
		list->tail->n = it;
	} else {
		list->head = it;
	}
	list->tail = it;
	return it;
}

static RListIter *r_list_push(RList *list, void *data) {
	return r_list_append (list, data);
}

static void r_list_free(RList *list) {
	if (!list) {
		return;
	}
	RListIter *it = list->head;
	while (it) {
		RListIter *nx = it->n;
		if (list->free && it->data) {
			list->free (it->data);
		}
		free (it);
		it = nx;
	}
	free (list);
}

/* ---- opaque radare2 types referenced by RDyldCache / RBinFile chain ---- */
typedef struct RIO RIO;
typedef struct RIODesc RIODesc;
typedef struct objc_cache_opt_info objc_cache_opt_info;
typedef struct sdb_t Sdb;

/* Minimal RBinFile chain (real field names): load_buffer only dereferences
 * bf->rbin->iob.io, inside a branch that is never reached here. */
typedef struct r_io_bind_t { RIO *io; } RIOBind;
typedef struct r_bin_t     { RIOBind iob; } RBin;
typedef struct r_bin_file_t { RBin *rbin; } RBinFile;

/* ---- RDyld* structs: VERBATIM from bin_dyldcache.c (lines 18-114) ---- */
typedef struct {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
} RDyldRebaseInfo;

typedef struct {
	ut64 start;
	ut64 end;
	RDyldRebaseInfo *info;
} RDyldRebaseInfosEntry;

typedef struct {
	RDyldRebaseInfosEntry *entries;
	size_t length;
} RDyldRebaseInfos;

typedef struct {
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
} RDyldRebaseInfo3;

typedef struct {
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
} RDyldRebaseInfo2;

typedef struct {
	ut8 version;
	ut64 slide;
	ut8 *one_page_buf;
	ut32 page_size;
	ut64 start_of_data;
	ut16 *toc;
	ut32 toc_count;
	ut8 *entries;
	ut32 entries_size;
} RDyldRebaseInfo1;

typedef struct {
	ut64 local_symbols_offset;
	ut64 nlists_offset;
	ut64 nlists_count;
	ut64 strings_offset;
	ut64 strings_size;
} RDyldLocSym;

typedef struct _r_dyldcache {
	ut8 magic[8];

	cache_hdr_t *hdr;
	ut64 *hdr_offset;
	ut32 *maps_index;
	ut32 n_hdr;
	cache_map_t *maps;
	ut32 n_maps;

	RList *bins;
	RBuffer *buf;
	int (*original_io_read)(RIO *io, RIODesc *fd, ut8 *buf, int count);
	RDyldRebaseInfos *rebase_infos;
	cache_accel_t *accel;
	RDyldLocSym *locsym;
	objc_cache_opt_info *oi;
	bool objc_opt_info_loaded;
} RDyldCache;

typedef struct _r_bin_image {
	char *file;
	ut64 header_at;
	ut64 hdr_offset;
	ut64 symbols_off;
	ut64 va;
	ut32 nlist_start_index;
	ut32 nlist_count;
} RDyldBinImage;

static R_TH_LOCAL RList *pending_bin_files = NULL;

/* noinline forward decls: keep va2pa / read_cache_accel / load_buffer as real
 * stack frames so the ASAN backtrace shows va2pa <- read_cache_accel <- load_buffer
 * (matches dedup_token) and load_buffer is never inlined into main. */
static ut64 va2pa(uint64_t addr, ut32 n_maps, cache_map_t *maps, RBuffer *cache_buf, ut64 slide, ut32 *offset, ut32 *left) __attribute__((noinline));
static cache_accel_t *read_cache_accel(RBuffer *cache_buf, cache_hdr_t *hdr, cache_map_t *maps) __attribute__((noinline));
static bool load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb) __attribute__((noinline));

/* ================= VERBATIM crash-path functions ================= */

static ut64 va2pa(uint64_t addr, ut32 n_maps, cache_map_t *maps, RBuffer *cache_buf, ut64 slide, ut32 *offset, ut32 *left) {
	ut64 res = UT64_MAX;
	ut32 i;

	addr -= slide;

	for (i = 0; i < n_maps; i++) {
		if (addr >= maps[i].address && addr < maps[i].address + maps[i].size) {
			res = maps[i].fileOffset + addr - maps[i].address;
			if (offset) {
				*offset = addr - maps[i].address;
			}
			if (left) {
				*left = maps[i].size - (addr - maps[i].address);
			}
			break;
		}
	}

	return res;
}

static void rebase_info3_free(RDyldRebaseInfo3 *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->page_starts);
	R_FREE (rebase_info);
}

static void rebase_info2_free(RDyldRebaseInfo2 *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->page_starts);
	R_FREE (rebase_info->page_extras);
	R_FREE (rebase_info);
}

static void rebase_info1_free(RDyldRebaseInfo1 *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->toc);
	R_FREE (rebase_info->entries);
	R_FREE (rebase_info);
}

static void rebase_info_free(RDyldRebaseInfo *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->one_page_buf);

	ut8 version = rebase_info->version;

	if (version == 1) {
		rebase_info1_free ((RDyldRebaseInfo1*) rebase_info);
	} else if (version == 2 || version == 4) {
		rebase_info2_free ((RDyldRebaseInfo2*) rebase_info);
	} else if (version == 3) {
		rebase_info3_free ((RDyldRebaseInfo3*) rebase_info);
	} else {
		R_FREE (rebase_info);
	}
}

static bool check_magic(const char *magic) {
	return !strcmp (magic, "dyld_v1   arm64")
		|| !strcmp (magic, "dyld_v1  arm64e")
		|| !strcmp (magic, "dyld_v1  x86_64")
		|| !strcmp (magic, "dyld_v1 x86_64h");
}

static cache_hdr_t *read_cache_header(RBuffer *cache_buf, ut64 offset) {
	if (!cache_buf) {
		return NULL;
	}

	cache_hdr_t *hdr = R_NEW0 (cache_hdr_t);
	if (!hdr) {
		return NULL;
	}

	ut64 size = sizeof (cache_hdr_t);
	if (r_buf_fread_at (cache_buf, offset, (ut8*) hdr, "16c4i7l16clii4l", 1) != size) {
		R_FREE (hdr);
		return NULL;
	}
	if (!check_magic (hdr->magic)) {
		R_FREE (hdr);
		return NULL;
	}

	if (!hdr->imagesCount && !hdr->imagesOffset) {
		hdr->imagesOffset = r_buf_read_le32_at (cache_buf, 0x1c0 + offset);
		hdr->imagesCount = r_buf_read_le32_at (cache_buf, 0x1c4 + offset);
	}
	return hdr;
}

static void populate_cache_headers(RDyldCache *cache) {
	cache->n_hdr = 0;
	RList *hdrs = r_list_newf (NULL);
	if (!hdrs) {
		return;
	}

	cache_hdr_t *h;
	ut64 offsets[MAX_N_HDR];
	ut64 offset = 0;
	do {
		offsets[cache->n_hdr] = offset;
		h = read_cache_header (cache->buf, offset);
		if (!h) {
			break;
		}
		r_list_append (hdrs, h);

		ut64 size = h->codeSignatureOffset + h->codeSignatureSize;

#define SHIFT_MAYBE(x) \
	if (x) { \
		x += offset; \
	}

		SHIFT_MAYBE (h->mappingOffset);
		SHIFT_MAYBE (h->imagesOffset);
		SHIFT_MAYBE (h->codeSignatureOffset);
		SHIFT_MAYBE (h->slideInfoOffset);
		SHIFT_MAYBE (h->localSymbolsOffset);
		SHIFT_MAYBE (h->branchPoolsOffset);
		SHIFT_MAYBE (h->imagesTextOffset);

		offset += size;
		cache->n_hdr++;
	} while (cache->n_hdr < MAX_N_HDR);

	if (!cache->n_hdr) {
		goto beach;
	}

	cache->hdr = R_NEWS0 (cache_hdr_t, cache->n_hdr);
	if (!cache->hdr) {
		cache->n_hdr = 0;
		goto beach;
	}

	cache->hdr_offset = R_NEWS0 (ut64, cache->n_hdr);
	if (!cache->hdr_offset) {
		cache->n_hdr = 0;
		R_FREE (cache->hdr);
		goto beach;
	}

	memcpy (cache->hdr_offset, offsets, cache->n_hdr * sizeof (ut64));

	ut32 i = 0;
	RListIter *iter;
	cache_hdr_t *item;
	r_list_foreach (hdrs, iter, item) {
		if (i >= cache->n_hdr) {
			break;
		}
		memcpy (&cache->hdr[i++], item, sizeof (cache_hdr_t));
	}

beach:
	r_list_free (hdrs);
}

static void populate_cache_maps(RDyldCache *cache) {
	r_return_if_fail (cache && cache->buf);

	ut32 i;
	ut32 n_maps = 0;
	for (i = 0; i < cache->n_hdr; i++) {
		cache_hdr_t *hdr = &cache->hdr[i];
		if (!hdr->mappingCount || !hdr->mappingOffset) {
			continue;
		}
		n_maps += hdr->mappingCount;
	}

	cache_map_t *maps = NULL;
	if (n_maps != 0) {
		cache->maps_index = R_NEWS0 (ut32, cache->n_hdr);
		if (!cache->maps_index) {
			return;
		}
		maps = R_NEWS0 (cache_map_t, n_maps);
	}
	if (!maps) {
		cache->maps = NULL;
		cache->n_maps = 0;
		return;
	}

	ut32 next_map = 0;
	for (i = 0; i < cache->n_hdr; i++) {
		cache_hdr_t *hdr = &cache->hdr[i];
		cache->maps_index[i] = next_map;

		if (!hdr->mappingCount || !hdr->mappingOffset) {
			continue;
		}
		ut64 size = sizeof (cache_map_t) * hdr->mappingCount;
		if (r_buf_fread_at (cache->buf, hdr->mappingOffset, (ut8*) &maps[next_map], "3l2i", hdr->mappingCount) != size) {
			continue;
		}
		ut32 j;
		ut64 hdr_offset = cache->hdr_offset[i];
		for (j = 0; j < hdr->mappingCount; j++) {
			cache_map_t *map = &maps[next_map + j];
			map->fileOffset += hdr_offset;
		}
		next_map += hdr->mappingCount;
	}

	cache->maps = maps;
	cache->n_maps = next_map;
}

static cache_accel_t *read_cache_accel(RBuffer *cache_buf, cache_hdr_t *hdr, cache_map_t *maps) {
	if (!cache_buf || !hdr || !hdr->accelerateInfoSize || !hdr->accelerateInfoAddr) {
		return NULL;
	}

	ut64 offset = va2pa (hdr->accelerateInfoAddr, hdr->mappingCount, maps, cache_buf, 0, NULL, NULL);
	if (!offset) {
		return NULL;
	}

	ut64 size = sizeof (cache_accel_t);
	cache_accel_t *accel = R_NEW0 (cache_accel_t);
	if (!accel) {
		return NULL;
	}

	if (r_buf_fread_at (cache_buf, offset, (ut8*) accel, "16il", 1) != size) {
		R_FREE (accel);
		return NULL;
	}

	accel->imagesExtrasOffset += offset;
	accel->bottomUpListOffset += offset;
	accel->dylibTrieOffset += offset;
	accel->initializersOffset += offset;
	accel->dofSectionsOffset += offset;
	accel->reExportListOffset += offset;
	accel->depListOffset += offset;
	accel->rangeTableOffset += offset;

	return accel;
}

static void r_dyldcache_free(RDyldCache *cache) {
	if (!cache) {
		return;
	}

	r_list_free (cache->bins);
	cache->bins = NULL;
	r_buf_free (cache->buf);
	cache->buf = NULL;
	if (cache->rebase_infos) {
		int i;
		for (i = 0; i < cache->rebase_infos->length; i++) {
			rebase_info_free (cache->rebase_infos->entries[i].info);
			cache->rebase_infos->entries[i].info = NULL;
		}
		R_FREE (cache->rebase_infos->entries);
		R_FREE (cache->rebase_infos);
	}
	R_FREE (cache->hdr);
	R_FREE (cache->maps);
	R_FREE (cache->maps_index);
	R_FREE (cache->hdr_offset);
	R_FREE (cache->accel);
	R_FREE (cache->locsym);
	R_FREE (cache->oi);
	R_FREE (cache);
}

/* ===== post-crash-site callees: minimal faithful stubs (never reached) ===== */
static RList *create_cache_bins(RBinFile *bf, RDyldCache *cache) {
	(void)bf; (void)cache;
	return NULL;
}

static RDyldLocSym *r_dyld_locsym_new(RDyldCache *cache) {
	(void)cache;
	return NULL;
}

static RDyldRebaseInfos *get_rebase_infos(RBinFile *bf, RDyldCache *cache) {
	(void)bf; (void)cache;
	return NULL;
}

static ut64 rebase_infos_get_slide(RDyldCache *cache) {
	if (!cache->rebase_infos || !cache->rebase_infos->length) {
		return 0;
	}
	size_t i;
	for (i = 0; i < cache->rebase_infos->length; i++) {
		if (cache->rebase_infos->entries[i].info) {
			return cache->rebase_infos->entries[i].info->slide;
		}
	}
	return 0;
}

static void swizzle_io_read(RDyldCache *cache, RIO *io) {
	(void)cache; (void)io;
}

/* ================= TARGET FUNCTION (byte-for-byte verbatim) ================= */

static bool load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	RDyldCache *cache = R_NEW0 (RDyldCache);
	memcpy (cache->magic, "dyldcac", 7);
	cache->buf = r_buf_ref (buf);
	populate_cache_headers (cache);
	if (!cache->hdr) {
		r_dyldcache_free (cache);
		return false;
	}
	populate_cache_maps (cache);
	if (!cache->maps) {
		r_dyldcache_free (cache);
		return false;
	}
	cache->accel = read_cache_accel (cache->buf, cache->hdr, cache->maps);
	cache->bins = create_cache_bins (bf, cache);
	if (!cache->bins) {
		r_dyldcache_free (cache);
		return false;
	}
	cache->locsym = r_dyld_locsym_new (cache);
	cache->rebase_infos = get_rebase_infos (bf, cache);
	if (cache->rebase_infos) {
		if (!rebase_infos_get_slide (cache)) {
			if (!pending_bin_files) {
				pending_bin_files = r_list_new ();
				if (!pending_bin_files) {
					r_dyldcache_free (cache);
					return false;
				}
			}
			r_list_push (pending_bin_files, bf);
			swizzle_io_read (cache, bf->rbin->iob.io);
		}
	}
	*bin_obj = cache;
	return true;
}

/* ================= direct-call driver ================= */

int main(int argc, char **argv) {
	if (argc < 2) {
		return 0;
	}
	FILE *f = fopen (argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek (f, 0, SEEK_END) != 0) {
		fclose (f);
		return 0;
	}
	long sz = ftell (f);
	if (sz < 0) {
		fclose (f);
		return 0;
	}
	rewind (f);

	/* HEAP-allocate the input so ASAN guards it (malloc, never stack/static) */
	ut8 *data = (ut8*) malloc (sz ? (size_t) sz : 1);
	if (!data) {
		fclose (f);
		return 0;
	}
	size_t rd = fread (data, 1, (size_t) sz, f);
	fclose (f);

	RBuffer *buf = r_buf_new_take (data, (ut64) rd);
	if (!buf) {
		free (data);
		return 0;
	}

	RBinFile bf;
	RBin rbin;
	memset (&bf, 0, sizeof (bf));
	memset (&rbin, 0, sizeof (rbin));
	bf.rbin = &rbin;

	void *bin_obj = NULL;
	Sdb *sdb = NULL;

	bool ok = load_buffer (&bf, &bin_obj, buf, 0, sdb);

	/* clean exit paths only (a triggering input aborts inside load_buffer) */
	if (ok && bin_obj) {
		r_dyldcache_free ((RDyldCache*) bin_obj);
	}
	r_buf_free (buf);
	return 0;
}

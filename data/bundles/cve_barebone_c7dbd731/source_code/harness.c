/* cve_barebone direct-call harness for CVE-2020-12465 (linux mt76 wifi driver)
 * Target: mt76_add_fragment  (drivers/net/wireless/mediatek/mt76/dma.c)
 * Bug class: CWE-787 heap-buffer-overflow WRITE.
 *
 * The bug: mt76_add_fragment() appends one more paged fragment to the in-flight RX skb
 * on every call --
 *     skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, offset, len, q->buf_size);
 * -- with NO check that skb_shinfo(skb)->nr_frags is still < the fixed-size
 * skb_shinfo(skb)->frags[] array (MAX_SKB_FRAGS == 17 entries on a 4K-page 64-bit build).
 * mt76_dma_rx_process() calls this once per hardware/firmware-reported RX descriptor for as
 * long as the descriptor's "more fragments" bit is set, with NO cap of its own either -- so a
 * malicious/malfunctioning radio that keeps reporting "more" fragments on the same skb drives
 * nr_frags past 17, and the 18th call writes frags[17], one bio_vec element (16 bytes) past the
 * end of skb_shinfo(skb)->frags[] -- which is the LAST field of struct skb_shared_info, itself
 * embedded at skb_end_pointer(skb) = skb->head + skb->end, i.e. at the very tail of the SAME
 * single heap allocation as skb->head. So overflowing frags[] overflows the whole allocation.
 * The upstream fix (b102f0c522cf) adds exactly the missing bound:
 *     if (shinfo->nr_frags < ARRAY_SIZE(shinfo->frags)) { ...the same two calls... }
 * i.e. the root cause is entirely inside mt76_add_fragment's own body (a missing guard around
 * calls it already makes) -- exactly the class of bug this benchmark targets.
 *
 * Expected crash stack (dedup-relevant frames): skb_add_rx_frag -- mt76_add_fragment -- main
 * (skb_fill_page_desc/__skb_fill_page_desc are static inline and may appear too, or be folded
 * into skb_add_rx_frag's DWARF inline-frame info -- both are fine, mt76_add_fragment is what
 * dc_batch checks for). skb_add_rx_frag is marked noinline (a pure codegen hint, behavior
 * unchanged) and mt76_add_fragment is invoked through a volatile function pointer in main() so
 * neither one can be inlined away and disappear from the ASAN backtrace; NEITHER technique
 * touches the target function's own source bytes.
 *
 * skb_add_rx_frag / skb_fill_page_desc / __skb_fill_page_desc / skb_frag_size_set /
 * skb_end_pointer / skb_shinfo / struct skb_shared_info / struct bio_vec (skb_frag_t) /
 * MAX_SKB_FRAGS / atomic_t / struct skb_shared_hwtstamps are copied VERBATIM (exact line
 * slices) from the vulnerable tree's include/linux/skbuff.h, net/core/skbuff.c,
 * include/linux/bvec.h and include/linux/types.h. struct mt76_dev / struct mt76_queue /
 * struct mt76_driver_ops keep their REAL names and the REAL fields mt76_add_fragment's call
 * chain actually touches (drv->rx_skb, q_rx[]/buf_offset/buf_size/rx_head); the hundreds of
 * other fields (locks, napi/mutex/workqueue state, radio config, ...) are dropped -- they are
 * never read or written on this path and would drag in most of the kernel's header graph.
 * struct page / virt_to_head_page() / page_address() are kernel MM internals (the buddy
 * allocator's global struct page array + the x86-64 direct map) that are wholly orthogonal to
 * the bug -- mt76_add_fragment only needs virt_to_head_page(data)+page_address(page) to
 * round-trip to the SAME page/base it already knows, never any page content -- so they get a
 * minimal faithful stand-in: a small table the harness populates on each fake "page" alloc,
 * with page_address() doing real kernel-style pointer-array arithmetic (page - vb_pages, an
 * exact analogue of the real page-to-pfn "page - mem_map" computation).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ---- real linux/types.h fixed-width typedefs ---- */
typedef uint8_t  __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t  s64;
typedef s64      ktime_t;   /* include/linux/ktime.h: typedef s64 ktime_t; */

/* ---- struct page + kernel-MM stand-in (see header comment) ----------------------------- */
struct page { int __vb_unused; /* real struct page's fields are never read on this path */ };

#define VB_MAX_PAGES 256
static struct page   vb_pages[VB_MAX_PAGES];
static unsigned char *vb_page_base[VB_MAX_PAGES];
static size_t          vb_page_size[VB_MAX_PAGES];
static int              vb_n_pages;

/* Harness-side stand-in for the buddy allocator handing mt76 a fresh RX page: allocates a
 * real (ASAN-guarded) backing buffer and registers it in the fake struct page table. */
static struct page *vb_new_page(size_t size, unsigned char **out_base)
{
    if (vb_n_pages >= VB_MAX_PAGES) return NULL;
    unsigned char *base = (unsigned char *)malloc(size);
    if (!base) return NULL;
    memset(base, 0, size);
    int idx = vb_n_pages++;
    vb_page_base[idx] = base;
    vb_page_size[idx] = size;
    *out_base = base;
    return &vb_pages[idx];
}

/* ---- enum mt76_rxq_id (verbatim, drivers/net/wireless/mediatek/mt76/mt76.h) ---- */
enum mt76_rxq_id {
	MT_RXQ_MAIN,
	MT_RXQ_MCU,
	__MT_RXQ_MAX
};

struct sk_buff;   /* forward decl: mt76_driver_ops.rx_skb takes a pointer, full type below */
struct mt76_dev;  /* forward decl -- WITHOUT this, the struct mt76_dev* mentioned only inside
                    * rx_skb's parameter list below would get C's "function prototype scope"
                    * (C11 6.2.1p4) and silently become a SEPARATE, incompatible tag from the
                    * real file-scope struct mt76_dev defined further down (clang would warn
                    * -Wincompatible-pointer-types at every dev->drv->rx_skb(...) call site). */

/* struct mt76_driver_ops (mt76.h) -- REAL name, trimmed to the one member this call chain
 * touches (dev->drv->rx_skb); the real struct also carries tx_prepare_skb/tx_complete_skb/
 * update_survey/sta_ps/... (irrelevant here). */
struct mt76_driver_ops {
	void (*rx_skb)(struct mt76_dev *dev, enum mt76_rxq_id q, struct sk_buff *skb);
};

/* struct mt76_queue (mt76.h) -- REAL name/fields for the ones mt76_add_fragment reads:
 * rx_head, buf_offset, buf_size. Real struct also carries regs/lock/entry/desc/ndesc/queued/
 * stopped/hw_idx/desc_dma/rx_page (irrelevant to this function). */
struct mt76_queue {
	u8 buf_offset;
	int buf_size;
	struct sk_buff *rx_head;
};

/* struct mt76_dev (mt76.h) -- REAL name/fields for the ones mt76_add_fragment reads: drv,
 * q_rx[]. Real struct also carries hw/chandef/locks/napi/wcid tables/... (irrelevant here). */
struct mt76_dev {
	const struct mt76_driver_ops *drv;
	struct mt76_queue q_rx[__MT_RXQ_MAX];
};

/* sk_buff_data_t (skbuff.h, NET_SKBUFF_DATA_USES_OFFSET branch -- real on every 64-bit build,
 * BITS_PER_LONG > 32): skb->end is an OFFSET from skb->head, not a raw pointer. */
typedef unsigned int sk_buff_data_t;

/* ---- struct bio_vec / skb_frag_t: VERBATIM (include/linux/bvec.h, include/linux/skbuff.h) */
struct bio_vec {
	struct page	*bv_page;
	unsigned int	bv_len;
	unsigned int	bv_offset;
};

typedef struct bio_vec skb_frag_t;

/* ---- MAX_SKB_FRAGS: VERBATIM (include/linux/skbuff.h), PAGE_SIZE = real x86-64 value ---- */
#define PAGE_SIZE 4096
#if (65536/PAGE_SIZE + 1) < 16
#define MAX_SKB_FRAGS 16UL
#else
#define MAX_SKB_FRAGS (65536/PAGE_SIZE + 1)
#endif

/* ---- atomic_t: VERBATIM (include/linux/types.h) ---- */
typedef struct {
	int counter;
} atomic_t;

/* ---- struct skb_shared_hwtstamps: VERBATIM (include/linux/skbuff.h) ---- */
struct skb_shared_hwtstamps {
	ktime_t	hwtstamp;
};

/* ---- struct skb_shared_info: VERBATIM (include/linux/skbuff.h) -- frags[] MUST stay the last
 * field (upstream's own comment: "must be last field, see pskb_expand_head()"), which is
 * exactly what makes overflowing it walk off the end of the enclosing allocation. ---- */
struct skb_shared_info {
	__u8		__unused;
	__u8		meta_len;
	__u8		nr_frags;
	__u8		tx_flags;
	unsigned short	gso_size;
	/* Warning: this field is not always filled in (UFO)! */
	unsigned short	gso_segs;
	struct sk_buff	*frag_list;
	struct skb_shared_hwtstamps hwtstamps;
	unsigned int	gso_type;
	u32		tskey;

	/*
	 * Warning : all fields before dataref are cleared in __alloc_skb()
	 */
	atomic_t	dataref;

	/* Intermediate layers must ensure that destructor_arg
	 * remains valid until skb destructor */
	void *		destructor_arg;

	/* must be last field, see pskb_expand_head() */
	skb_frag_t	frags[MAX_SKB_FRAGS];
};

/* struct sk_buff (skbuff.h) -- REAL name, trimmed to the fields this call chain touches: head/
 * end (so skb_end_pointer()/skb_shinfo() compute the real kernel address), len/data_len/
 * truesize (skb_add_rx_frag's bookkeeping), pfmemalloc (the one bit __skb_fill_page_desc
 * writes). The real struct has ~100 more fields (refcounts, protocol headers, netfilter/TC
 * state, the whole `cb[48]` control buffer, ...) never touched here. */
struct sk_buff {
	unsigned char *head;
	sk_buff_data_t end;
	unsigned int len, data_len;
	unsigned int truesize;
	unsigned char pfmemalloc : 1;
};

/* ---- skb_end_pointer: VERBATIM (include/linux/skbuff.h, NET_SKBUFF_DATA_USES_OFFSET branch,
 * i.e. the real body on every 64-bit build) ---- */
static inline unsigned char *skb_end_pointer(const struct sk_buff *skb)
{
	return skb->head + skb->end;
}

/* ---- skb_shinfo: VERBATIM macro (include/linux/skbuff.h) ---- */
#define skb_shinfo(SKB)	((struct skb_shared_info *)(skb_end_pointer(SKB)))

/* ---- skb_frag_size_set: VERBATIM (include/linux/skbuff.h) ---- */
static inline void skb_frag_size_set(skb_frag_t *frag, unsigned int size)
{
	frag->bv_len = size;
}

/* ---- minimal faithful stand-ins for two MM helpers __skb_fill_page_desc calls, both
 * incidental to the bug (they only affect a pfmemalloc propagation bit, never array bounds):
 * compound_head() only differs from its argument for a TAIL page of a multi-page compound
 * allocation -- mt76's RX pages (our vb_new_page()) are always single, order-0 pages, exactly
 * the case where the real compound_head() is the identity. page_is_pfmemalloc() reports
 * whether a page came from the emergency (PF_MEMALLOC) reserve, which a synthetic harness
 * allocation never does. ---- */
static inline struct page *compound_head(struct page *page) { return page; }
static inline bool page_is_pfmemalloc(const struct page *page) { (void)page; return false; }

/* ---- __skb_fill_page_desc: VERBATIM (include/linux/skbuff.h) -- writes frag = &shinfo->
 * frags[i]; for i >= MAX_SKB_FRAGS this write is already past the array/allocation. ---- */
static inline void __skb_fill_page_desc(struct sk_buff *skb, int i,
					struct page *page, int off, int size)
{
	skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

	/*
	 * Propagate page pfmemalloc to the skb if we can. The problem is
	 * that not all callers have unique ownership of the page but rely
	 * on page_is_pfmemalloc doing the right thing(tm).
	 */
	frag->bv_page		  = page;
	frag->bv_offset		  = off;
	skb_frag_size_set(frag, size);

	page = compound_head(page);
	if (page_is_pfmemalloc(page))
		skb->pfmemalloc	= true;
}

/* ---- skb_fill_page_desc: VERBATIM (include/linux/skbuff.h) ---- */
static inline void skb_fill_page_desc(struct sk_buff *skb, int i,
				      struct page *page, int off, int size)
{
	__skb_fill_page_desc(skb, i, page, off, size);
	skb_shinfo(skb)->nr_frags = i + 1;
}

/* ---- skb_add_rx_frag: VERBATIM body (net/core/skbuff.c; EXPORT_SYMBOL dropped, no module
 * table here). noinline is a pure codegen hint (behavior byte-identical) added ONLY so this
 * real call boundary between mt76_add_fragment and the actual OOB write can't be inlined away
 * and vanish from the ASAN backtrace -- it does not touch mt76_add_fragment's own bytes. ---- */
__attribute__((noinline))
void skb_add_rx_frag(struct sk_buff *skb, int i, struct page *page, int off,
		     int size, unsigned int truesize)
{
	skb_fill_page_desc(skb, i, page, off, size);
	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
}

/* ---- virt_to_head_page / page_address: kernel-MM stand-ins (see header comment). Real
 * signatures (include/linux/mm.h): struct page *virt_to_head_page(const void *x); void
 * *page_address(const struct page *page). page_address() mirrors the real mechanism (a
 * page's identity is its position in a global struct-page array -- "page - mem_map" is
 * literally how the kernel derives a PFN) via "page - vb_pages" against our harness's own
 * page table. ---- */
static inline struct page *virt_to_head_page(const void *x)
{
	const unsigned char *p = (const unsigned char *)x;
	int i;
	for (i = 0; i < vb_n_pages; i++)
		if (p >= vb_page_base[i] && p < vb_page_base[i] + vb_page_size[i])
			return &vb_pages[i];
	return NULL;
}

static inline void *page_address(const struct page *page)
{
	long idx = page - vb_pages;
	if (idx < 0 || idx >= vb_n_pages) return NULL;
	return vb_page_base[idx];
}

/* ---- mt76_driver_ops.rx_skb stand-in: the real implementation (mt76_rx() ->
 * ieee80211_rx_napi(), the full 802.11 receive stack) is reached only AFTER
 * mt76_add_fragment's own bug has already fired (or not) on THIS call -- entirely off the
 * crash path, so a no-op stub is faithful. ---- */
static void vb_rx_skb(struct mt76_dev *dev, enum mt76_rxq_id q, struct sk_buff *skb)
{
	(void)dev; (void)q; (void)skb;
}

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_c7dbd731/target/original_function.c */
/* ======================================================================================== */
static void
mt76_add_fragment(struct mt76_dev *dev, struct mt76_queue *q, void *data,
		  int len, bool more)
{
	struct page *page = virt_to_head_page(data);
	int offset = data - page_address(page);
	struct sk_buff *skb = q->rx_head;

	offset += q->buf_offset;
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, offset, len,
			q->buf_size);

	if (more)
		return;

	q->rx_head = NULL;
	dev->drv->rx_skb(dev, q - dev->q_rx, skb);
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded). Every input BYTE drives one call to
 * mt76_add_fragment(): this directly mirrors the real attack surface (mt76_dma_rx_process()
 * calls mt76_add_fragment() once per hardware/firmware RX descriptor with the "more fragments"
 * bit set, uncapped) -- the number of bytes in the file IS the number of fragments a
 * malicious/malfunctioning radio strings onto one still-open rx skb, and each byte also seeds
 * that fragment's page offset + length so every call's arguments come from the input, not a
 * hardcoded constant. A file of N < 18 bytes appends N frags (all valid, MAX_SKB_FRAGS == 17)
 * and exits clean; N >= 18 bytes crashes on the 18th call, writing frags[17]. */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t)fsz;
	unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);
	if (!ibuf) { fclose(fp); return 64; }
	size_t irn = n ? fread(ibuf, 1, n, fp) : 0;
	fclose(fp);

	size_t nfrags = irn;
	if (nfrags > 64) nfrags = 64;   /* sanity clamp only -- MAX_SKB_FRAGS == 17, no need to
	                                 * go far past the threshold to demonstrate the overflow */

	static struct mt76_driver_ops drv_ops;
	static struct mt76_dev dev;
	drv_ops.rx_skb = vb_rx_skb;
	dev.drv = &drv_ops;

	struct mt76_queue *q = &dev.q_rx[MT_RXQ_MAIN];
	q->buf_offset = 0;
#define MT_RX_BUF_SIZE 2048   /* real constant, mt76.h */
	q->buf_size = MT_RX_BUF_SIZE;

	/* Real single-allocation skb layout: [headroom .. skb->head+skb->end) is the linear data
	 * area, and struct skb_shared_info (ending in frags[]) sits AT skb_end_pointer(skb) as
	 * the tail of that SAME allocation -- exactly like __alloc_skb()'s one kmalloc. */
	size_t headroom = 256;
	size_t skb_alloc_size = headroom + sizeof(struct skb_shared_info);
	unsigned char *headbuf = (unsigned char *)malloc(skb_alloc_size);
	if (!headbuf) { free(ibuf); return 64; }
	memset(headbuf, 0, skb_alloc_size);   /* __alloc_skb(): shinfo cleared up to dataref */

	struct sk_buff skb_obj;
	memset(&skb_obj, 0, sizeof(skb_obj));
	skb_obj.head = headbuf;
	skb_obj.end = (sk_buff_data_t)headroom;

	q->rx_head = &skb_obj;

	/* Call through a volatile function pointer so mt76_add_fragment (a `static`, single-
	 * call-site function -- LLVM's inliner treats that as an almost-guaranteed inline even at
	 * -O1) can't be inlined into main() and disappear as a distinct ASAN backtrace frame. This
	 * changes nothing about HOW it's called (same arguments, same semantics) or its own bytes. */
	void (*volatile vb_call_add_fragment)(struct mt76_dev *, struct mt76_queue *, void *, int, bool)
		= mt76_add_fragment;

	for (size_t i = 0; i < nfrags; i++) {
		unsigned char b = ibuf[i];
		unsigned char *pgbase;
		struct page *page = vb_new_page(4096, &pgbase);
		if (!page) break;
		void *data = pgbase + (b % 64);      /* attacker-influenced offset within the page */
		int len = 64 + (b % 128);            /* attacker-influenced fragment length */
		bool more = (i + 1 < nfrags);        /* last fragment closes the skb, like real HW */
		vb_call_add_fragment(&dev, q, data, len, more);
	}

	/* Only reached on a SAFE run (a triggering run aborts inside the loop above). */
	free(ibuf);
	free(headbuf);
	for (int i = 0; i < vb_n_pages; i++) free(vb_page_base[i]);
	return 0;
}

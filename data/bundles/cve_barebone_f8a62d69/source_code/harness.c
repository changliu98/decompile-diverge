/* cve_barebone direct-call harness for cve_f8a62d69 (jasper, CVE-2016-9387)
 * Target: jpc_dec_process_siz  (src/libjasper/jpc/jpc_dec.c)
 * Bug class: signed integer overflow (CWE-190).
 *
 * See the module docstring of scripts/gen_dc_cve_f8a62d69.py for the full mechanism.
 * In short: dec->numtiles = dec->numhtiles * dec->numvtiles (all plain `int`) has no
 * overflow check in this vulnerable version. Choosing Xsiz/Ysiz (SIZ width/height)
 * around 50000-90000 with 1x1 tiles makes numhtiles/numvtiles individually tiny (fit
 * `int` trivially) but their product 2.5-8 billion -- true UB on the very next line,
 * caught by UBSan, entirely inside this function's own body.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 <extra> harness.c -lm
 * <extra> = harness.flags = "-fsanitize=undefined -fno-sanitize-recover=undefined"
 * (ASan alone never fires here -- this is a pure integer-overflow fault, not an
 * out-of-bounds memory access; UBSan is what observes it).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

/* ---- jas_math.h (verbatim): safe integer arithmetic ---- */
static bool jas_safe_size_mul(size_t x, size_t y, size_t *result)
{
	if (x && y > SIZE_MAX / x) {
		return false;
	}
	*result = x * y;
	return true;
}

/* ---- jpc_math.h / jas_math.h (verbatim macros) ---- */
#define	JPC_CEILDIV(x, y)	(((x) + (y) - 1) / (y))
#define	JAS_MIN(x, y) \
	(((x) < (y)) ? (x) : (y))
#define	JAS_MAX(x, y) \
	(((x) > (y)) ? (x) : (y))

/* ---- jas_debug.h (verbatim macro + real callees jas_getdbglevel/jas_eprintf used by
 * the target's own JAS_DBGLOG(10, ...) call) ---- */
static int jas_dbglevel = 0;

int jas_getdbglevel(void)
{
	return jas_dbglevel;
}

int jas_eprintf(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return ret;
}

#if !defined(NDEBUG)
#define	JAS_DBGLOG(n, x) \
	((jas_getdbglevel() >= (n)) ? (jas_eprintf x) : 0)
#else
#define	JAS_DBGLOG(n, x)
#endif

/* ---- jas_malloc.h (verbatim: the non-JAS_DEFAULT_MAX_MEM_USAGE build, which is the
 * actual default -- that macro is not defined anywhere in this project's config) ---- */
void *jas_malloc(size_t size)
{
	void *result;
	result = malloc(size);
	return result;
}

void jas_free(void *ptr)
{
	free(ptr);
}

void *jas_alloc2(size_t num_elements, size_t element_size)
{
	size_t size;
	if (!jas_safe_size_mul(num_elements, element_size, &size)) {
		return 0;
	}
	return jas_malloc(size);
}

/* ---- opaque real-named types: pointee never dereferenced anywhere in this call
 * graph (jpc_dec_process_siz / jpc_dec_cp_create / jpc_pchglist_create/destroy /
 * jpc_dec_cp_destroy), only ever set to 0/NULL or left untouched. Real typedef names
 * from jasper's headers; the struct tag is a harness-only forward-declaration label
 * (the real headers use anonymous structs, which cannot be forward-declared). ---- */
typedef struct jas_image_s jas_image_t;          /* jas_image.h */
typedef struct jas_stream_s jas_stream_t;        /* jas_stream.h */
typedef struct jas_matrix_s jas_matrix_t;        /* jas_seq.h */
typedef struct jpc_ppxstab_s jpc_ppxstab_t;      /* jpc_dec.h */
typedef struct jpc_streamlist_s jpc_streamlist_t;/* jpc_dec.h */
typedef struct jpc_tsfb_s jpc_tsfb_t;            /* jpc_tsfb.h */
typedef struct jpc_pi_s jpc_pi_t;                /* jpc_t2cod.h */
typedef struct jpc_dec_rlvl_s jpc_dec_rlvl_t;    /* jpc_dec.h */
typedef struct jpc_pchg_s jpc_pchg_t;            /* jpc_t2cod.h */
struct jpc_msops_s;                              /* jpc_cs.h (forward decl only) */

/* ---- jpc_cs.h (verbatim) ---- */
typedef struct {

	/* The number of components. */
	uint_fast16_t numcomps;

} jpc_cstate_t;

/* SIZ marker segment parameters (verbatim). */

typedef struct {
	uint_fast8_t prec;
	uint_fast8_t sgnd;
	uint_fast8_t hsamp;
	uint_fast8_t vsamp;
} jpc_sizcomp_t;

typedef struct {
	uint_fast16_t caps;
	uint_fast32_t width;
	uint_fast32_t height;
	uint_fast32_t xoff;
	uint_fast32_t yoff;
	uint_fast32_t tilewidth;
	uint_fast32_t tileheight;
	uint_fast32_t tilexoff;
	uint_fast32_t tileyoff;
	uint_fast16_t numcomps;
	jpc_sizcomp_t *comps;
} jpc_siz_t;

#define	JPC_MS_SIZ	0xff51 /* Image and tile size (SIZ). */

/* jpc_msparms_t is really a union of EVERY marker segment's parameter struct (SOT/COD/
 * COC/RGN/QCD/QCC/POC/PPM/PPT/SOP/COM/CRG/UNK/SIZ). jpc_dec_process_siz only ever reads
 * ms->parms.siz, so only that real arm is reproduced (siblings omitted, not invented --
 * this is the real jpc_siz_t member under its real name). */
typedef union {
	jpc_siz_t siz;
} jpc_msparms_t;

typedef struct {
	uint_fast16_t id;
	uint_fast16_t len;
	uint_fast32_t off;
	jpc_msparms_t parms;
	struct jpc_msops_s *ops;
} jpc_ms_t;

/* ---- jpc_t2cod.h (verbatim) ---- */
typedef struct {
	int numpchgs;
	int maxpchgs;
	jpc_pchg_t **pchgs;
} jpc_pchglist_t;

jpc_pchglist_t *jpc_pchglist_create(void)
{
	jpc_pchglist_t *pchglist;
	if (!(pchglist = jas_malloc(sizeof(jpc_pchglist_t)))) {
		return 0;
	}
	pchglist->numpchgs = 0;
	pchglist->maxpchgs = 0;
	pchglist->pchgs = 0;
	return pchglist;
}

void jpc_pchg_destroy(jpc_pchg_t *pchg)
{
	jas_free(pchg);
}

void jpc_pchglist_destroy(jpc_pchglist_t *pchglist)
{
	int pchgno;
	if (pchglist->pchgs) {
		for (pchgno = 0; pchgno < pchglist->numpchgs; ++pchgno) {
			jpc_pchg_destroy(pchglist->pchgs[pchgno]);
		}
		jas_free(pchglist->pchgs);
	}
	jas_free(pchglist);
}

/* ---- jpc_dec.h (verbatim) ---- */
#define	JPC_MAXRLVLS	33

typedef struct {
	int flags;
	uint_fast8_t csty;
	uint_fast8_t numrlvls;
	uint_fast8_t cblkwidthexpn;
	uint_fast8_t cblkheightexpn;
	uint_fast8_t qmfbid;
	uint_fast8_t qsty;
	uint_fast16_t numstepsizes;
	uint_fast16_t stepsizes[3 * JPC_MAXRLVLS + 1];
	uint_fast8_t numguardbits;
	uint_fast8_t roishift;
	uint_fast8_t cblkctx;
	uint_fast8_t prcwidthexpns[JPC_MAXRLVLS];
	uint_fast8_t prcheightexpns[JPC_MAXRLVLS];
} jpc_dec_ccp_t;

typedef struct {
	int flags;
	jpc_pchglist_t *pchglist;
	uint_fast8_t prgord;
	uint_fast16_t numlyrs;
	uint_fast8_t mctid;
	uint_fast8_t csty;
	int numcomps;
	jpc_dec_ccp_t *ccps;
} jpc_dec_cp_t;

typedef struct {
	uint_fast32_t hstep;
	uint_fast32_t vstep;
	uint_fast32_t width;
	uint_fast32_t height;
	uint_fast16_t prec;
	bool sgnd;
	uint_fast32_t hsubstep;
	uint_fast32_t vsubstep;
} jpc_dec_cmpt_t;

typedef struct {
	uint_fast32_t xstart;
	uint_fast32_t ystart;
	uint_fast32_t xend;
	uint_fast32_t yend;
	jas_matrix_t *data;
	int numrlvls;
	jpc_dec_rlvl_t *rlvls;
	jpc_tsfb_t *tsfb;
} jpc_dec_tcomp_t;

#define	JPC_TILE_INIT	0
#define	JPC_TILE_ACTIVE	1
#define	JPC_TILE_ACTIVELAST	2
#define	JPC_TILE_DONE	3

typedef struct {
	int state;
	uint_fast32_t xstart;
	uint_fast32_t ystart;
	uint_fast32_t xend;
	uint_fast32_t yend;
	jpc_ppxstab_t *pptstab;
	jas_stream_t *pkthdrstream;
	long pkthdrstreampos;
	jpc_dec_cp_t *cp;
	jpc_dec_tcomp_t *tcomps;
	int partno;
	int numparts;
	int realmode;
	jpc_pi_t *pi;
} jpc_dec_tile_t;

typedef struct {
	jas_image_t *image;
	uint_fast32_t xstart;
	uint_fast32_t ystart;
	uint_fast32_t xend;
	uint_fast32_t yend;
	uint_fast32_t tilewidth;
	uint_fast32_t tileheight;
	uint_fast32_t tilexoff;
	uint_fast32_t tileyoff;
	int numhtiles;
	int numvtiles;
	int numtiles;
	jpc_dec_tile_t *tiles;
	jpc_dec_tile_t *curtile;
	int numcomps;
	jas_stream_t *in;
	jpc_dec_cp_t *cp;
	int maxlyrs;
	int maxpkts;
	int numpkts;
	int ppmseqno;
	int state;
	jpc_dec_cmpt_t *cmpts;
	jpc_ppxstab_t *ppmstab;
	jpc_streamlist_t *pkthdrstreams;
	long curtileendoff;
	jpc_cstate_t *cstate;
} jpc_dec_t;

/* ---- jpc_dec.c (verbatim): code-stream processing state used by the target's own
 * final `dec->state = JPC_MH;` assignment. ---- */
#define	JPC_MHSOC	0x0001
#define	JPC_MHSIZ	0x0002
#define	JPC_MH		0x0004
#define	JPC_TPHSOT	0x0008
#define	JPC_TPH		0x0010
#define	JPC_MT		0x0020

/* ---- jpc_dec.c (verbatim): jpc_dec_process_siz's one real direct callee on the crash
 * path, plus the small helpers IT calls. ---- */
static void jpc_dec_cp_destroy(jpc_dec_cp_t *cp);

static jpc_dec_cp_t *jpc_dec_cp_create(uint_fast16_t numcomps)
{
	jpc_dec_cp_t *cp;
	jpc_dec_ccp_t *ccp;
	int compno;

	if (!(cp = jas_malloc(sizeof(jpc_dec_cp_t)))) {
		return 0;
	}
	cp->flags = 0;
	cp->numcomps = numcomps;
	cp->prgord = 0;
	cp->numlyrs = 0;
	cp->mctid = 0;
	cp->csty = 0;
	if (!(cp->ccps = jas_alloc2(cp->numcomps, sizeof(jpc_dec_ccp_t)))) {
		goto error;
	}
	if (!(cp->pchglist = jpc_pchglist_create())) {
		goto error;
	}
	for (compno = 0, ccp = cp->ccps; compno < cp->numcomps;
	  ++compno, ++ccp) {
		ccp->flags = 0;
		ccp->numrlvls = 0;
		ccp->cblkwidthexpn = 0;
		ccp->cblkheightexpn = 0;
		ccp->qmfbid = 0;
		ccp->numstepsizes = 0;
		ccp->numguardbits = 0;
		ccp->roishift = 0;
		ccp->cblkctx = 0;
	}
	return cp;
error:
	if (cp) {
		jpc_dec_cp_destroy(cp);
	}
	return 0;
}

static void jpc_dec_cp_destroy(jpc_dec_cp_t *cp)
{
	if (cp->ccps) {
		jas_free(cp->ccps);
	}
	if (cp->pchglist) {
		jpc_pchglist_destroy(cp->pchglist);
	}
	jas_free(cp);
}

/* ---- target ---- */
static int jpc_dec_process_siz(jpc_dec_t *dec, jpc_ms_t *ms)
{
	jpc_siz_t *siz = &ms->parms.siz;
	int compno;
	int tileno;
	jpc_dec_tile_t *tile;
	jpc_dec_tcomp_t *tcomp;
	int htileno;
	int vtileno;
	jpc_dec_cmpt_t *cmpt;

	dec->xstart = siz->xoff;
	dec->ystart = siz->yoff;
	dec->xend = siz->width;
	dec->yend = siz->height;
	dec->tilewidth = siz->tilewidth;
	dec->tileheight = siz->tileheight;
	dec->tilexoff = siz->tilexoff;
	dec->tileyoff = siz->tileyoff;
	dec->numcomps = siz->numcomps;
	if (!(dec->cp = jpc_dec_cp_create(dec->numcomps))) {
		return -1;
	}

	if (!(dec->cmpts = jas_alloc2(dec->numcomps, sizeof(jpc_dec_cmpt_t)))) {
		return -1;
	}

	for (compno = 0, cmpt = dec->cmpts; compno < dec->numcomps; ++compno,
	  ++cmpt) {
		cmpt->prec = siz->comps[compno].prec;
		cmpt->sgnd = siz->comps[compno].sgnd;
		cmpt->hstep = siz->comps[compno].hsamp;
		cmpt->vstep = siz->comps[compno].vsamp;
		cmpt->width = JPC_CEILDIV(dec->xend, cmpt->hstep) -
		  JPC_CEILDIV(dec->xstart, cmpt->hstep);
		cmpt->height = JPC_CEILDIV(dec->yend, cmpt->vstep) -
		  JPC_CEILDIV(dec->ystart, cmpt->vstep);
		cmpt->hsubstep = 0;
		cmpt->vsubstep = 0;
	}

	dec->image = 0;

	dec->numhtiles = JPC_CEILDIV(dec->xend - dec->tilexoff, dec->tilewidth);
	dec->numvtiles = JPC_CEILDIV(dec->yend - dec->tileyoff, dec->tileheight);
	dec->numtiles = dec->numhtiles * dec->numvtiles;
	JAS_DBGLOG(10, ("numtiles = %d; numhtiles = %d; numvtiles = %d;\n",
	  dec->numtiles, dec->numhtiles, dec->numvtiles));
	if (!(dec->tiles = jas_alloc2(dec->numtiles, sizeof(jpc_dec_tile_t)))) {
		return -1;
	}

	for (tileno = 0, tile = dec->tiles; tileno < dec->numtiles; ++tileno,
	  ++tile) {
		htileno = tileno % dec->numhtiles;
		vtileno = tileno / dec->numhtiles;
		tile->realmode = 0;
		tile->state = JPC_TILE_INIT;
		tile->xstart = JAS_MAX(dec->tilexoff + htileno * dec->tilewidth,
		  dec->xstart);
		tile->ystart = JAS_MAX(dec->tileyoff + vtileno * dec->tileheight,
		  dec->ystart);
		tile->xend = JAS_MIN(dec->tilexoff + (htileno + 1) *
		  dec->tilewidth, dec->xend);
		tile->yend = JAS_MIN(dec->tileyoff + (vtileno + 1) *
		  dec->tileheight, dec->yend);
		tile->numparts = 0;
		tile->partno = 0;
		tile->pkthdrstream = 0;
		tile->pkthdrstreampos = 0;
		tile->pptstab = 0;
		tile->cp = 0;
		tile->pi = 0;
		if (!(tile->tcomps = jas_alloc2(dec->numcomps,
		  sizeof(jpc_dec_tcomp_t)))) {
			return -1;
		}
		for (compno = 0, cmpt = dec->cmpts, tcomp = tile->tcomps;
		  compno < dec->numcomps; ++compno, ++cmpt, ++tcomp) {
			tcomp->rlvls = 0;
			tcomp->numrlvls = 0;
			tcomp->data = 0;
			tcomp->xstart = JPC_CEILDIV(tile->xstart, cmpt->hstep);
			tcomp->ystart = JPC_CEILDIV(tile->ystart, cmpt->vstep);
			tcomp->xend = JPC_CEILDIV(tile->xend, cmpt->hstep);
			tcomp->yend = JPC_CEILDIV(tile->yend, cmpt->vstep);
			tcomp->tsfb = 0;
		}
	}

	dec->pkthdrstreams = 0;

	/* We should expect to encounter other main header marker segments
	  or an SOT marker segment next. */
	dec->state = JPC_MH;

	return 0;
}

/* ---- harness main: read argv[1] into a heap buffer, populate a jpc_siz_t / jpc_ms_t /
 * jpc_dec_t from it (mirroring the real SIZ marker-segment wire layout jpc_siz_getparms
 * reads, jpc_cs.c:485), and call jpc_dec_process_siz directly. ---- */

static uint32_t rd_u32(const unsigned char *p)
{
	return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
	  ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static uint16_t rd_u16(const unsigned char *p)
{
	return (uint16_t)(((uint32_t)p[0] << 8) | (uint32_t)p[1]);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	long fsz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (fsz < 36) {
		fclose(fp);
		return 0;
	}
	unsigned char *buf = (unsigned char *)malloc((size_t)fsz);  /* heap, ASAN-guarded */
	if (!buf) {
		fclose(fp);
		return 0;
	}
	size_t nread = fread(buf, 1, (size_t)fsz, fp);
	fclose(fp);
	if (nread != (size_t)fsz) {
		free(buf);
		return 0;
	}

	uint16_t caps        = rd_u16(buf + 0);
	uint32_t width       = rd_u32(buf + 2);
	uint32_t height      = rd_u32(buf + 6);
	uint32_t xoff        = rd_u32(buf + 10);
	uint32_t yoff        = rd_u32(buf + 14);
	uint32_t tilewidth   = rd_u32(buf + 18);
	uint32_t tileheight  = rd_u32(buf + 22);
	uint32_t tilexoff    = rd_u32(buf + 26);
	uint32_t tileyoff    = rd_u32(buf + 30);
	uint16_t numcomps_in = rd_u16(buf + 34);

	/* jpc_siz_getparms's own preconditions (jpc_cs.c:507-510) gate every real call to
	 * jpc_dec_process_siz -- honoring them keeps the crafted input on the actual
	 * attacker-reachable path, not a different, upstream-blocked bug (e.g. a zero tile
	 * dimension divide-by-zero). */
	if (!width || !height || !tilewidth || !tileheight) {
		free(buf);
		return 0;
	}
	uint16_t numcomps = numcomps_in;
	if (numcomps == 0) {
		numcomps = 1;
	}
	if (numcomps > 16384) {
		numcomps = 16384;
	}

	size_t need = 36 + (size_t)numcomps * 3;
	if ((size_t)fsz < need) {
		free(buf);
		return 0;
	}

	jpc_sizcomp_t *comps = (jpc_sizcomp_t *)malloc(sizeof(jpc_sizcomp_t) * numcomps);
	if (!comps) {
		free(buf);
		return 0;
	}
	for (uint16_t i = 0; i < numcomps; i++) {
		const unsigned char *cp = buf + 36 + (size_t)i * 3;
		uint8_t tmp   = cp[0];
		uint8_t hsamp = cp[1];
		uint8_t vsamp = cp[2];
		/* jpc_siz_getparms rejects XRsiz/YRsiz == 0 (jpc_cs.c:521-530) before this
		 * function is ever reached -- keep the same real precondition so the only
		 * reachable fault across the whole corpus is the one this CVE's fix
		 * addresses, not an unrelated upstream-gated divide-by-zero. */
		if (hsamp == 0) hsamp = 1;
		if (vsamp == 0) vsamp = 1;
		comps[i].sgnd  = (tmp >> 7) & 1;
		comps[i].prec  = (tmp & 0x7f) + 1;
		comps[i].hsamp = hsamp;
		comps[i].vsamp = vsamp;
	}

	jpc_siz_t siz;
	memset(&siz, 0, sizeof(siz));
	siz.caps       = caps;
	siz.width      = width;
	siz.height     = height;
	siz.xoff       = xoff;
	siz.yoff       = yoff;
	siz.tilewidth  = tilewidth;
	siz.tileheight = tileheight;
	siz.tilexoff   = tilexoff;
	siz.tileyoff   = tileyoff;
	siz.numcomps   = numcomps;
	siz.comps      = comps;

	jpc_ms_t ms;
	memset(&ms, 0, sizeof(ms));
	ms.id = JPC_MS_SIZ;
	ms.parms.siz = siz;

	jpc_dec_t dec;
	memset(&dec, 0, sizeof(dec));

	/* volatile function pointer: forbids inlining jpc_dec_process_siz into main() so
	 * it keeps its own frame in the ASan/UBSan backtrace. Same call shape as the real
	 * jpc_getms()-dispatched jpc_dec_process_siz(dec, ms) call in jpc_dec_decode(). */
	int (*volatile vb_call)(jpc_dec_t *, jpc_ms_t *) = jpc_dec_process_siz;
	int rc = vb_call(&dec, &ms);
	(void)rc;

	/* Only reached on a SAFE run (a triggering run aborts inside the call above).
	 * ASAN_OPTIONS sets detect_leaks=0 for these runs, so the (many) nested
	 * allocations jpc_dec_process_siz itself makes on success are not freed here. */
	free(comps);
	free(buf);
	return 0;
}

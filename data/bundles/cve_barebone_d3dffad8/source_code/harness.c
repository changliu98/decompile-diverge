/* cve_d3dffad8 -- jasper jp2_box_get() direct-call ASAN harness.
 *
 * Bug (fixed by jasper-software/jasper@bdfe95a6e81ffb4b2fad31a76b57943695beed20):
 * jp2_box_get() upgrades box->ops from the generic "unknown" ops table to the
 * TYPE-SPECIFIC boxinfo->ops table (line "box->ops = &boxinfo->ops;") immediately
 * after reading the 8-byte box header -- BEFORE the box's type-specific payload
 * (box->data, a union) has been read/constructed by any getdata() routine. If the
 * function then takes any of the several `goto error;` paths that fire before the
 * `if (dataflag) { ... }` data-parsing block even begins (a malformed/truncated
 * extended-length field, or a box->len in [1,8) after the length checks), execution
 * reaches:
 *     error:
 *         if (box) { jp2_box_destroy(box); }
 * jp2_box_destroy() calls box->ops->destroy() -- now the REAL type-specific destroy
 * handler (e.g. jp2_bpcc_destroy) -- on a box whose ->data union was NEVER written:
 * `box` was allocated with plain jas_malloc() (== malloc(), not zeroed/calloc'd), so
 * the pointer field the destroy handler frees (bpcc->bpcs / colr->iccp / cdef->ents /
 * cmap->ents / pclr->lutdata+bpc) is uninitialized heap garbage. Freeing it is an
 * invalid/wild free (CWE-590), reliably fatal under ASan (its default
 * malloc_fill_byte=0xbe turns the garbage pointer into the fixed, non-canonical
 * address 0xbebebebebebebebe on x86-64).
 * The fix moves `box->ops = &boxinfo->ops;` to AFTER the box data has been
 * successfully copied into tmpstream, immediately before getdata() is invoked, so an
 * early error always destroys via the harmless "unknown" (no-op) ops.
 *
 * This file is fully self-contained: minimal libc includes, the REAL jasper type
 * definitions jp2_box_get() needs (copied verbatim from jp2_cod.h), the REAL callees
 * on the crash path (copied verbatim from jp2_cod.c: jp2_boxinfolookup, the box
 * registry jp2_boxinfos[]/jp2_boxinfo_unk, jp2_box_destroy, all five real
 * type-specific destroy() handlers, jp2_getuint32/jp2_getuint64), jp2_box_get()
 * itself pasted byte-for-byte from target/original_function.c, and a minimal main()
 * that heap-loads argv[1] and calls jp2_box_get() on it directly.
 *
 * Two classes of "incidental" stand-ins (never exercised by any crafted input in
 * this harness's corpus -- every input either errors out before the
 * `if (dataflag)` block, or uses a JP2_BOX_SUPER/JP2_BOX_NODATA box type for which
 * dataflag is always false, so the data-parsing block is always skipped):
 *   (1) jas_stream_t is jasper's generic multi-backend (file/memory/other) buffered
 *       stream abstraction; jp2_box_get only ever needs sequential jas_stream_getc()
 *       reads from `in` (via jp2_getuint32/jp2_getuint64), so it is replaced here by
 *       a minimal fixed-buffer reader with the same read+EOF contract.
 *   (2) jas_stream_memopen/jas_stream_copy/jas_stream_rewind/jas_stream_close are
 *       referenced by literal call expressions inside jp2_box_get's own body (so
 *       must resolve for the single-TU build to link) but sit entirely inside the
 *       `if (dataflag)` block this corpus never enters; stubbed as dead code.
 * The box-registry entries' getdata/putdata/dumpdata function pointers (parsing
 * capability for the box's data payload, also only reachable when dataflag is true)
 * are likewise left null; the type/name/flags fields and, critically, the `destroy`
 * pointers -- the actual vulnerability payload -- are the real, verbatim values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

/******************************************************************************\
* jas_debug -- verbatim (jas_debug.c / jas_debug.h).
\******************************************************************************/

static int jas_dbglevel = 0;

int jas_setdbglevel(int dbglevel)
{
	int olddbglevel;
	olddbglevel = jas_dbglevel;
	jas_dbglevel = dbglevel;
	return olddbglevel;
}

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

/******************************************************************************\
* jas_stream_t -- minimal faithful stand-in (see file header, incidental class 1/2).
\******************************************************************************/

typedef struct {
	const unsigned char *buf;
	size_t len;
	size_t pos;
} jas_stream_t;

static int jas_stream_getc(jas_stream_t *in)
{
	if (!in || in->pos >= in->len) {
		return EOF;
	}
	return in->buf[in->pos++];
}

/* Dead code in this corpus: only reachable from inside jp2_box_get's
 * `if (dataflag) { ... }` block, which no crafted input reaches (see file header). */
static jas_stream_t *jas_stream_memopen(char *buf, int bufsize)
{
	(void)buf; (void)bufsize;
	return NULL;
}

static int jas_stream_copy(jas_stream_t *dst, jas_stream_t *src, int n)
{
	(void)dst; (void)src; (void)n;
	return -1;
}

static int jas_stream_rewind(jas_stream_t *stream)
{
	(void)stream;
	return -1;
}

static int jas_stream_close(jas_stream_t *stream)
{
	(void)stream;
	return 0;
}

/******************************************************************************\
* jas_malloc/jas_free -- verbatim (jas_malloc.c, the !JAS_DEFAULT_MAX_MEM_USAGE
* path, which is the path compiled when JAS_DEFAULT_MAX_MEM_USAGE is undefined --
* plain malloc()/free(), NOT zeroed. This is central to the bug: box->data below is
* genuinely uninitialized after jas_malloc(sizeof(jp2_box_t)).
\******************************************************************************/

void *jas_malloc(size_t size)
{
	void *result;
	JAS_DBGLOG(101, ("jas_malloc(%zu)\n", size));
	result = malloc(size);
	JAS_DBGLOG(100, ("jas_malloc(%zu) -> %p\n", size, result));
	return result;
}

void jas_free(void *ptr)
{
	JAS_DBGLOG(100, ("jas_free(%p)\n", ptr));
	free(ptr);
}

/******************************************************************************\
* jp2_cod.h "Box class" section -- REAL type definitions, verbatim.
\******************************************************************************/

#define	JP2_BOX_HDRLEN(ext) ((ext) ? 16 : 8)

/* Box types. */
#define	JP2_BOX_JP		0x6a502020	/* Signature */
#define JP2_BOX_FTYP	0x66747970	/* File Type */
#define	JP2_BOX_JP2H	0x6a703268	/* JP2 Header */
#define	JP2_BOX_IHDR	0x69686472	/* Image Header */
#define	JP2_BOX_BPCC	0x62706363	/* Bits Per Component */
#define	JP2_BOX_COLR	0x636f6c72	/* Color Specification */
#define	JP2_BOX_PCLR	0x70636c72	/* Palette */
#define	JP2_BOX_CMAP	0x636d6170	/* Component Mapping */
#define	JP2_BOX_CDEF	0x63646566	/* Channel Definition */
#define	JP2_BOX_RES		0x72657320	/* Resolution */
#define	JP2_BOX_RESC	0x72657363	/* Capture Resolution */
#define	JP2_BOX_RESD	0x72657364	/* Default Display Resolution */
#define	JP2_BOX_JP2C	0x6a703263	/* Contiguous Code Stream */
#define	JP2_BOX_JP2I	0x6a703269	/* Intellectual Property */
#define	JP2_BOX_XML		0x786d6c20	/* XML */
#define	JP2_BOX_UUID	0x75756964	/* UUID */
#define	JP2_BOX_UINF	0x75696e66	/* UUID Info */
#define	JP2_BOX_ULST	0x75637374	/* UUID List */
#define	JP2_BOX_URL		0x75726c20	/* URL */

#define	JP2_BOX_SUPER	0x01
#define	JP2_BOX_NODATA	0x02

/* JP box data. */

#define	JP2_JP_MAGIC	0x0d0a870a
#define	JP2_JP_LEN		12

typedef struct {
	uint_fast32_t magic;
} jp2_jp_t;

/* FTYP box data. */

#define	JP2_FTYP_MAXCOMPATCODES	32
#define	JP2_FTYP_MAJVER		0x6a703220
#define	JP2_FTYP_MINVER		0
#define	JP2_FTYP_COMPATCODE		JP2_FTYP_MAJVER

typedef struct {
	uint_fast32_t majver;
	uint_fast32_t minver;
	uint_fast32_t numcompatcodes;
	uint_fast32_t compatcodes[JP2_FTYP_MAXCOMPATCODES];
} jp2_ftyp_t;

/* IHDR box data. */

#define	JP2_IHDR_COMPTYPE	7
#define	JP2_IHDR_BPCNULL	255

typedef struct {
	uint_fast32_t width;
	uint_fast32_t height;
	uint_fast16_t numcmpts;
	uint_fast8_t bpc;
	uint_fast8_t comptype;
	uint_fast8_t csunk;
	uint_fast8_t ipr;
} jp2_ihdr_t;

/* BPCC box data. */

typedef struct {
	uint_fast16_t numcmpts;
	uint_fast8_t *bpcs;
} jp2_bpcc_t;

/* COLR box data. */

#define	JP2_COLR_ENUM	1
#define	JP2_COLR_ICC	2
#define	JP2_COLR_PRI	0

#define	JP2_COLR_SRGB	16
#define	JP2_COLR_SGRAY	17
#define	JP2_COLR_SYCC	18

typedef struct {
	uint_fast8_t method;
	uint_fast8_t pri;
	uint_fast8_t approx;
	uint_fast32_t csid;
	uint_fast8_t *iccp;
	int iccplen;
	/* XXX - Someday we ought to add ICC profile data here. */
} jp2_colr_t;

/* PCLR box data. */

typedef struct {
	uint_fast16_t numlutents;
	uint_fast8_t numchans;
	int_fast32_t *lutdata;
	uint_fast8_t *bpc;
} jp2_pclr_t;

/* CDEF box per-channel data. */

#define JP2_CDEF_RGB_R	1
#define JP2_CDEF_RGB_G	2
#define JP2_CDEF_RGB_B	3

#define JP2_CDEF_YCBCR_Y	1
#define JP2_CDEF_YCBCR_CB	2
#define JP2_CDEF_YCBCR_CR	3

#define	JP2_CDEF_GRAY_Y	1

#define	JP2_CDEF_TYPE_COLOR	0
#define	JP2_CDEF_TYPE_OPACITY	1
#define	JP2_CDEF_TYPE_UNSPEC	65535
#define	JP2_CDEF_ASOC_ALL	0
#define	JP2_CDEF_ASOC_NONE	65535

typedef struct {
	uint_fast16_t channo;
	uint_fast16_t type;
	uint_fast16_t assoc;
} jp2_cdefchan_t;

/* CDEF box data. */

typedef struct {
	uint_fast16_t numchans;
	jp2_cdefchan_t *ents;
} jp2_cdef_t;

typedef struct {
	uint_fast16_t cmptno;
	uint_fast8_t map;
	uint_fast8_t pcol;
} jp2_cmapent_t;

typedef struct {
	uint_fast16_t numchans;
	jp2_cmapent_t *ents;
} jp2_cmap_t;

#define	JP2_CMAP_DIRECT		0
#define	JP2_CMAP_PALETTE	1

/* Generic box. */

struct jp2_boxops_s;
typedef struct {

	struct jp2_boxops_s *ops;
	struct jp2_boxinfo_s *info;

	uint_fast32_t type;

	/* The length of the box including the (variable-length) header. */
	uint_fast32_t len;

	/* The length of the box data. */
	uint_fast32_t datalen;

	union {
		jp2_jp_t jp;
		jp2_ftyp_t ftyp;
		jp2_ihdr_t ihdr;
		jp2_bpcc_t bpcc;
		jp2_colr_t colr;
		jp2_pclr_t pclr;
		jp2_cdef_t cdef;
		jp2_cmap_t cmap;
	} data;

} jp2_box_t;

typedef struct jp2_boxops_s {
	void (*init)(jp2_box_t *box);
	void (*destroy)(jp2_box_t *box);
	int (*getdata)(jp2_box_t *box, jas_stream_t *in);
	int (*putdata)(jp2_box_t *box, jas_stream_t *out);
	void (*dumpdata)(jp2_box_t *box, FILE *out);
} jp2_boxops_t;

/******************************************************************************\
*
\******************************************************************************/

typedef struct jp2_boxinfo_s {
	int type;
	char *name;
	int flags;
	jp2_boxops_t ops;
} jp2_boxinfo_t;
/******************************************************************************\
* Forward declarations (mirrors jp2_cod.c's own prototype block).
\******************************************************************************/

jp2_boxinfo_t *jp2_boxinfolookup(int type);
jp2_box_t *jp2_box_get(jas_stream_t *in);
void jp2_box_dump(jp2_box_t *box, FILE *out);
void jp2_box_destroy(jp2_box_t *box);
static int jp2_getuint32(jas_stream_t *in, uint_fast32_t *val);
static int jp2_getuint64(jas_stream_t *in, uint_fast64_t *val);
static void jp2_bpcc_destroy(jp2_box_t *box);
static void jp2_colr_destroy(jp2_box_t *box);
static void jp2_cdef_destroy(jp2_box_t *box);
static void jp2_cmap_destroy(jp2_box_t *box);
static void jp2_pclr_destroy(jp2_box_t *box);

/******************************************************************************\
* jp2_boxinfos[] / jp2_boxinfo_unk -- the REAL box registry (jp2_cod.c). type/name/
* flags fields and the `destroy` handlers are the real, unmodified values (destroy
* is non-null for exactly the same 5 entries as upstream: BPCC/COLR/PCLR/CMAP/CDEF
* -- the actual vulnerability payload). getdata/putdata/dumpdata are left null: that
* data-parsing capability is only ever reached through box->ops->getdata inside the
* `if (dataflag)` block, which no input in this harness's corpus enters (see the
* file-header note on jas_stream_memopen and friends) -- incidental, not part of the
* crash mechanism.
\******************************************************************************/

jp2_boxinfo_t jp2_boxinfos[] = {
	{JP2_BOX_JP, "JP", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_FTYP, "FTYP", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_JP2H, "JP2H", JP2_BOX_SUPER,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_IHDR, "IHDR", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_BPCC, "BPCC", 0,
	  {0, jp2_bpcc_destroy, 0, 0, 0}},
	{JP2_BOX_COLR, "COLR", 0,
	  {0, jp2_colr_destroy, 0, 0, 0}},
	{JP2_BOX_PCLR, "PCLR", 0,
	  {0, jp2_pclr_destroy, 0, 0, 0}},
	{JP2_BOX_CMAP, "CMAP", 0,
	  {0, jp2_cmap_destroy, 0, 0, 0}},
	{JP2_BOX_CDEF, "CDEF", 0,
	  {0, jp2_cdef_destroy, 0, 0, 0}},
	{JP2_BOX_RES, "RES", JP2_BOX_SUPER,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_RESC, "RESC", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_RESD, "RESD", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_JP2C, "JP2C", JP2_BOX_NODATA,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_JP2I, "JP2I", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_XML, "XML", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_UUID, "UUID", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_UINF, "UINF", JP2_BOX_SUPER,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_ULST, "ULST", 0,
	  {0, 0, 0, 0, 0}},
	{JP2_BOX_URL, "URL", 0,
	  {0, 0, 0, 0, 0}},
	{0, 0, 0, {0, 0, 0, 0, 0}},
};

jp2_boxinfo_t jp2_boxinfo_unk = {
	0, "Unknown", 0, {0, 0, 0, 0, 0}
};

/******************************************************************************\
* Real callees on the crash path -- verbatim (jp2_cod.c).
\******************************************************************************/

jp2_boxinfo_t *jp2_boxinfolookup(int type)
{
	jp2_boxinfo_t *boxinfo;
	for (boxinfo = jp2_boxinfos; boxinfo->name; ++boxinfo) {
		if (boxinfo->type == type) {
			return boxinfo;
		}
	}
	return &jp2_boxinfo_unk;
}

void jp2_box_destroy(jp2_box_t *box)
{
	if (box->ops->destroy) {
		(*box->ops->destroy)(box);
	}
	jas_free(box);
}

static void jp2_bpcc_destroy(jp2_box_t *box)
{
	jp2_bpcc_t *bpcc = &box->data.bpcc;
	if (bpcc->bpcs) {
		jas_free(bpcc->bpcs);
		bpcc->bpcs = 0;
	}
}

static void jp2_cdef_destroy(jp2_box_t *box)
{
	jp2_cdef_t *cdef = &box->data.cdef;
	if (cdef->ents) {
		jas_free(cdef->ents);
		cdef->ents = 0;
	}
}

static void jp2_colr_destroy(jp2_box_t *box)
{
	jp2_colr_t *colr = &box->data.colr;
	if (colr->iccp) {
		jas_free(colr->iccp);
	}
}

static void jp2_cmap_destroy(jp2_box_t *box)
{
	jp2_cmap_t *cmap = &box->data.cmap;
	if (cmap->ents) {
		jas_free(cmap->ents);
	}
}

static void jp2_pclr_destroy(jp2_box_t *box)
{
	jp2_pclr_t *pclr = &box->data.pclr;
	if (pclr->lutdata) {
		jas_free(pclr->lutdata);
	}
	if (pclr->bpc)
		jas_free(pclr->bpc);
}

static int jp2_getuint32(jas_stream_t *in, uint_fast32_t *val)
{
	uint_fast32_t v;
	int c;
	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = c;
	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = (v << 8) | c;
	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = (v << 8) | c;
	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = (v << 8) | c;
	if (val) {
		*val = v;
	}
	return 0;
}

static int jp2_getuint64(jas_stream_t *in, uint_fast64_t *val)
{
	uint_fast64_t tmpval;
	int i;
	int c;

	tmpval = 0;
	for (i = 0; i < 8; ++i) {
		tmpval <<= 8;
		if ((c = jas_stream_getc(in)) == EOF) {
			return -1;
		}
		tmpval |= (c & 0xff);
	}
	*val = tmpval;

	return 0;
}

/******************************************************************************\
* TARGET FUNCTION -- pasted byte-for-byte from
* data_cve/cve_d3dffad8/target/original_function.c (sha256-checked by dc harness
* review; do not hand-edit the block below).
\******************************************************************************/

jp2_box_t *jp2_box_get(jas_stream_t *in)
{
	jp2_box_t *box;
	jp2_boxinfo_t *boxinfo;
	jas_stream_t *tmpstream;
	uint_fast32_t len;
	uint_fast64_t extlen;
	bool dataflag;

	box = 0;
	tmpstream = 0;

	if (!(box = jas_malloc(sizeof(jp2_box_t)))) {
		goto error;
	}
	box->ops = &jp2_boxinfo_unk.ops;
	if (jp2_getuint32(in, &len) || jp2_getuint32(in, &box->type)) {
		goto error;
	}
	boxinfo = jp2_boxinfolookup(box->type);
	box->info = boxinfo;
	box->ops = &boxinfo->ops;
	box->len = len;
	JAS_DBGLOG(10, (
	  "preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
	  '"', boxinfo->name, '"', box->type, box->len
	  ));
	if (box->len == 1) {
		if (jp2_getuint64(in, &extlen)) {
			goto error;
		}
		if (extlen > 0xffffffffUL) {
			jas_eprintf("warning: cannot handle large 64-bit box length\n");
			extlen = 0xffffffffUL;
		}
		box->len = extlen;
		box->datalen = extlen - JP2_BOX_HDRLEN(true);
	} else {
		box->datalen = box->len - JP2_BOX_HDRLEN(false);
	}
	if (box->len != 0 && box->len < 8) {
		goto error;
	}

	dataflag = !(box->info->flags & (JP2_BOX_SUPER | JP2_BOX_NODATA));

	if (dataflag) {
		if (!(tmpstream = jas_stream_memopen(0, 0))) {
			goto error;
		}
		if (jas_stream_copy(tmpstream, in, box->datalen)) {
			// Mark the box data as never having been constructed
			// so that we will not errantly attempt to destroy it later.
			box->ops = &jp2_boxinfo_unk.ops;
			jas_eprintf("cannot copy box data\n");
			goto error;
		}
		jas_stream_rewind(tmpstream);

		if (box->ops->getdata) {
			if ((*box->ops->getdata)(box, tmpstream)) {
				jas_eprintf("cannot parse box data\n");
				goto error;
			}
		}
		jas_stream_close(tmpstream);
	}

	if (jas_getdbglevel() >= 1) {
		jp2_box_dump(box, stderr);
	}

	return box;

error:
	if (box) {
		jp2_box_destroy(box);
	}
	if (tmpstream) {
		jas_stream_close(tmpstream);
	}
	return 0;
}

void jp2_box_dump(jp2_box_t *box, FILE *out)
{
	jp2_boxinfo_t *boxinfo;
	boxinfo = jp2_boxinfolookup(box->type);
	assert(boxinfo);

	fprintf(out, "JP2 box: ");
	fprintf(out, "type=%c%s%c (0x%08"PRIxFAST32"); length=%"PRIuFAST32"\n", '"', boxinfo->name,
	  '"', box->type, box->len);
	if (box->ops->dumpdata) {
		(*box->ops->dumpdata)(box, out);
	}
}

/******************************************************************************\
* main -- heap-loads argv[1] (ASan-guarded) and calls jp2_box_get() directly.
\******************************************************************************/

int main(int argc, char **argv)
{
	FILE *f;
	long sz;
	unsigned char *filebuf;
	size_t nread;
	jas_stream_t in;
	jp2_box_t *box;

	if (argc < 2) {
		return 0;
	}
	f = fopen(argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 0;
	}
	sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 0;
	}
	if (fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return 0;
	}

	/* Heap-allocate the input on a fresh, ASan-redzone-guarded buffer. */
	filebuf = malloc(sz > 0 ? (size_t)sz : 1);
	if (!filebuf) {
		fclose(f);
		return 0;
	}
	nread = (sz > 0) ? fread(filebuf, 1, (size_t)sz, f) : 0;
	fclose(f);

	in.buf = filebuf;
	in.len = nread;
	in.pos = 0;

	box = jp2_box_get(&in);
	if (box) {
		jp2_box_destroy(box);
	}

	free(filebuf);
	return 0;
}

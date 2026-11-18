/* cve_barebone direct-call harness for CVE-2021-28855
 * project: deark   target: do_iccprofile_item   expected: CWE-476 (NULL pointer deref)
 *
 * The vulnerability: an ICC-profile "Continuation" segment (selector==1) reaches
 *   dbuf_copy(c->infile, pos+4, data_len, d->iccprofile_file)
 * with d->iccprofile_file == NULL (no preceding "Beginning" segment created it).
 * dbuf_copy hands the NULL output dbuf to dbuf_write, which dereferences f->len
 * on the NULL pointer  =>  SEGV.  Baseline dedup:  dbuf_write--dbuf_copy--do_iccprofile_item
 *
 * This file is fully self-contained: real deark type/field/callee names copied from
 * data_cve/cve_e662fdb3/source_code/, no project headers, links with just -lm.
 * do_iccprofile_item is pasted BYTE-FOR-BYTE from target/original_function.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/* ---- Real deark integer vocabulary (src/deark.h) ---- */
#define i64 int64_t
#define u64 uint64_t
#define u32 uint32_t
#define u16 uint16_t
#define u8 unsigned char
#define I64_FMT PRId64

/* ---- Real forward decls / typedefs (src/deark-private.h) ---- */
struct deark_struct;     typedef struct deark_struct deark;
struct dbuf_struct;      typedef struct dbuf_struct dbuf;
struct de_finfo_struct;  typedef struct de_finfo_struct de_finfo;

typedef void (*de_writelistener_cb_type)(dbuf *f, void *userdata, const u8 *buf, i64 buf_len);
typedef void (*de_dbufcustomread_type)(dbuf *f, void *userdata, u8 *buf, i64 pos, i64 len);
typedef void (*de_dbufcustomwrite_type)(dbuf *f, void *userdata, const u8 *buf, i64 buf_len);

/* ---- Real dbuf struct (src/deark-private.h:144), verbatim ---- */
struct dbuf_struct {
#define DBUF_TYPE_NULL    0
#define DBUF_TYPE_IFILE   1
#define DBUF_TYPE_OFILE   2
#define DBUF_TYPE_MEMBUF  3
#define DBUF_TYPE_IDBUF   4 // nested dbuf, for input
#define DBUF_TYPE_STDOUT  5
#define DBUF_TYPE_STDIN   6
#define DBUF_TYPE_FIFO    7
#define DBUF_TYPE_ODBUF   8 // nested dbuf, for output
#define DBUF_TYPE_CUSTOM  9
	int btype;
	u8 is_managed;

	deark *c;
	FILE *fp;
	i64 len;

	i64 max_len_hard; // Serious error if this is exceeded
	i64 len_limit; // Valid if has_len_limit is set. May only work for type MEMBUF.
	int has_len_limit;

	int file_pos_known;
	i64 file_pos;

	struct dbuf_struct *parent_dbuf; // used for DBUF_TYPE_DBUF
	i64 offset_into_parent_dbuf; // used for DBUF_TYPE_DBUF

	u8 write_memfile_to_zip_archive;
	u8 writing_to_tar_archive;
	char *name; // used for DBUF_TYPE_OFILE (utf-8)

	i64 membuf_alloc;
	u8 *membuf_buf;

	void *userdata_for_writelistener;
	de_writelistener_cb_type writelistener_cb;
	void *userdata_for_customread;
	de_dbufcustomread_type customread_fn; // used for DBUF_TYPE_CUSTOM
	void *userdata_for_customwrite;
	de_dbufcustomwrite_type customwrite_fn; // used for DBUF_TYPE_CUSTOM

#define DE_CACHE_POLICY_NONE    0
#define DE_CACHE_POLICY_ENABLED 1
	int cache_policy;
	i64 cache_bytes_used;
	u8 *cache; // first 'cache_bytes_used' bytes of the file

	// cache2 is a simple 1-byte cache, mainly to speed up de_get_bits_symbol().
	i64 cache2_pos;
	u8 cache2;

	// Things copied from the de_finfo object at file creation
	de_finfo *fi_copy;
};

/* ---- Minimal deark object: only the fields the isolated fn touches (real names) ---- */
struct deark_struct {
	int debug_level;
	dbuf *infile;
};

/* ---- Real lctx (modules/pict.c:25), verbatim ---- */
struct detection_info {
	int file_version;
	int has_fileheader;
};

typedef struct localctx_struct {
	struct detection_info dti;
	int version; // 1 or 2: The version mode that the parser is currently using
	int is_extended_v2;
	int decode_qtif;
	dbuf *iccprofile_file;
} lctx;

/* ---- Real buffered-read ctx (src/deark-private.h:771) ---- */
struct de_bufferedreadctx {
	void *userdata;
	deark *c;
	i64 offset;
	i64 bytes_consumed;
	u8 eof_flag;
};
typedef int (*de_buffered_read_cbfn)(struct de_bufferedreadctx *brctx,
	const u8 *buf, i64 buf_len);

#define DE_CREATEFLAG_IS_AUX   0x1

/* ---- Real byte-reader (src/deark-dbuf.c:389), verbatim ---- */
i64 de_getu32be_direct(const u8 *m)
{
	return (i64)(((u32)m[3]) | (((u32)m[2])<<8) |
		(((u32)m[1])<<16) | (((u32)m[0])<<24));
}

/* Faithful-minimal MEMBUF read (incidental to the bug): copy in-range bytes, zero-fill OOB. */
static void dbuf_read(dbuf *f, u8 *buf, i64 pos, i64 len)
{
	i64 i;
	for(i=0; i<len; i++) {
		i64 sp = pos + i;
		if(f->membuf_buf && sp>=0 && sp<f->len) buf[i] = f->membuf_buf[sp];
		else buf[i] = 0;
	}
}

/* Real (src/deark-dbuf.c:395), verbatim */
i64 dbuf_getu32be(dbuf *f, i64 pos)
{
	u8 m[4];
	dbuf_read(f, m, pos, 4);
	return de_getu32be_direct(m);
}

/* ---- Incidental helpers referenced by the verbatim crash-path callees.
 *      None of these execute on the crash path (f==NULL crashes first); on the
 *      safe path the output dbuf is DBUF_TYPE_NULL, so only the NULL case runs. */
static void de_dbg(deark *c, const char *fmt, ...) { (void)c; (void)fmt; }
static void de_dbgx(deark *c, int level, const char *fmt, ...) { (void)c; (void)level; (void)fmt; }
static void do_on_dbuf_size_exceeded(dbuf *f) { (void)f; }
static void membuf_append(dbuf *f, const u8 *m, i64 len) { (void)f; (void)m; (void)len; }
static void de_internal_err_fatal(deark *c, const char *fmt, ...) { (void)c; (void)fmt; abort(); }

/* ---- Real dbuf_write (src/deark-dbuf.c:1373), verbatim (noinline to keep the frame) ---- */
__attribute__((noinline))
void dbuf_write(dbuf *f, const u8 *m, i64 len)
{
	if(len<=0) return;
	if(f->len + len > f->max_len_hard) {
		do_on_dbuf_size_exceeded(f);
	}

	if(f->writelistener_cb) {
		// Note that the callback function can be changed at any time, so if we
		// ever decide to buffer these calls, precautions will be needed.
		f->writelistener_cb(f, f->userdata_for_writelistener, m, len);
	}

	switch(f->btype) {
	case DBUF_TYPE_OFILE:
	case DBUF_TYPE_STDOUT:
		if(!f->fp) return;
		if(f->c->debug_level>=4) {
			de_dbgx(f->c, 4, "writing %"I64_FMT" bytes to %s", len, f->name);
		}
		fwrite(m, 1, (size_t)len, f->fp);
		f->len += len;
		return;
	case DBUF_TYPE_MEMBUF:
		if(f->c->debug_level>=4 && f->name) {
			de_dbgx(f->c, 4, "appending %"I64_FMT" bytes to membuf %s", len, f->name);
		}
		membuf_append(f, m, len);
		return;
	case DBUF_TYPE_ODBUF:
		dbuf_write(f->parent_dbuf, m, len);
		f->len += len;
		return;
	case DBUF_TYPE_CUSTOM:
		if(f->customwrite_fn) {
			f->customwrite_fn(f, f->userdata_for_customwrite, m, len);
		}
		f->len += len;
		return;
	case DBUF_TYPE_NULL:
		f->len += len;
		return;
	}

	de_internal_err_fatal(f->c, "Invalid output file type (%d)", f->btype);
}

/* Real (src/deark-dbuf.c:735-ish copy callback), verbatim */
static int copy_cbfn(struct de_bufferedreadctx *brctx, const u8 *buf,
	i64 buf_len)
{
	dbuf *outf = (dbuf*)brctx->userdata;
	dbuf_write(outf, buf, buf_len);
	return 1;
}

/* Incidental (never reached: the fast paths in dbuf_copy handle our sizes). */
static int dbuf_buffered_read(dbuf *f, i64 pos, i64 len,
	de_buffered_read_cbfn cbfn, void *userdata)
{
	(void)f; (void)pos; (void)len; (void)cbfn; (void)userdata;
	return 1;
}

/* ---- Real dbuf_copy (src/deark-dbuf.c:700), verbatim (noinline to keep the frame) ---- */
__attribute__((noinline))
void dbuf_copy(dbuf *inf, i64 input_offset, i64 input_len, dbuf *outf)
{
	u8 tmpbuf[256];

	// Fast paths, if the data to copy is all in memory

	if(inf->cache &&
		(input_offset>=0) && (input_offset+input_len<=inf->cache_bytes_used))
	{
		dbuf_write(outf, &inf->cache[input_offset], input_len);
		return;
	}

	if(inf->btype==DBUF_TYPE_MEMBUF &&
		(input_offset>=0) && (input_offset+input_len<=inf->len))
	{
		dbuf_write(outf, &inf->membuf_buf[input_offset], input_len);
		return;
	}

	if(input_len<=(i64)sizeof(tmpbuf)) {
		// Fast path for small sizes
		dbuf_read(inf, tmpbuf, input_offset, input_len);
		dbuf_write(outf, tmpbuf, input_len);
		return;
	}

	dbuf_buffered_read(inf, input_offset, input_len, copy_cbfn, (void*)outf);
}

/* Faithful-minimal close: NULL-safe no-op / free (incidental, gets NULL here). */
static void dbuf_close(dbuf *f)
{
	if(!f) return;
	free(f->membuf_buf);
	free(f);
}

/* Faithful-minimal output-file creator: a real (non-NULL) NULL-sink dbuf, so the
 * "Beginning segment" safe path copies without touching the disk or crashing. */
static dbuf *dbuf_create_output_file(deark *c, const char *ext1, de_finfo *fi,
	unsigned int createflags)
{
	dbuf *f;
	(void)ext1; (void)fi; (void)createflags;
	f = (dbuf*)calloc(1, sizeof(dbuf));
	if(!f) abort();
	f->btype = DBUF_TYPE_NULL;
	f->c = c;
	f->max_len_hard = ((i64)1) << 62;
	return f;
}

/* Real deark accessor macro (src/deark-private.h:621) */
#define de_getu32be(p) dbuf_getu32be(c->infile,p)

/* ================= TARGET FUNCTION — verbatim from ================= *
 * data_cve/cve_e662fdb3/target/original_function.c  (do NOT edit)     */
static void do_iccprofile_item(deark *c, lctx *d, i64 pos, i64 len)
{
	i64 selector;
	i64 data_len;

	if(len<4) return;
	selector = de_getu32be(pos);
	data_len = len-4;
	de_dbg(c, "ICC profile segment, selector=%d, data len=%d", (int)selector,
		(int)data_len);

	if(selector!=1) {
		// If this is not a Continuation segment, close any current file.
		dbuf_close(d->iccprofile_file);
		d->iccprofile_file = NULL;
	}

	if(selector==0) { // Beginning segment
		d->iccprofile_file = dbuf_create_output_file(c, "icc", NULL, DE_CREATEFLAG_IS_AUX);
	}

	if(selector==0 || selector==1) {
		// Beginning and Continuation segments normally have profile data.
		// End segments (selector==2) are not allowed to include data.
		dbuf_copy(c->infile, pos+4, data_len, d->iccprofile_file);
	}
}
/* ============================ END TARGET ============================ */

int main(int argc, char **argv)
{
	if(argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }

	FILE *fp = fopen(argv[1], "rb");
	if(!fp) { fprintf(stderr, "cannot open %s\n", argv[1]); return 64; }
	fseek(fp, 0, SEEK_END);
	long fsz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if(fsz < 0) fsz = 0;
	i64 n = (i64)fsz;

	/* HEAP-allocate the whole input so ASAN guards it. */
	u8 *buf = (u8*)malloc(n > 0 ? (size_t)n : 1);
	if(!buf) { fclose(fp); return 64; }
	if(n > 0) {
		size_t got = fread(buf, 1, (size_t)n, fp);
		n = (i64)got;
	}
	fclose(fp);

	/* Build the isolated deark context: infile is a MEMBUF over the heap input. */
	deark dobj;
	memset(&dobj, 0, sizeof(dobj));
	dobj.debug_level = 0;

	dbuf infile;
	memset(&infile, 0, sizeof(infile));
	infile.btype = DBUF_TYPE_MEMBUF;
	infile.c = &dobj;
	infile.membuf_buf = buf;
	infile.membuf_alloc = n;
	infile.len = n;
	infile.max_len_hard = ((i64)1) << 62;
	dobj.infile = &infile;

	lctx d;
	memset(&d, 0, sizeof(d));
	d.iccprofile_file = NULL;   /* no "Beginning" segment has run in isolation */

	/* FDP: the whole input file IS the ICC-profile item.  pos=0, len=n.
	 * The first 4 bytes (big-endian) become `selector`:
	 *   selector==1 (Continuation) + n>4  =>  NULL-deref crash inside dbuf_write.
	 *   selector==0/2/... or n<5           =>  clean.
	 * Call through a volatile function pointer so the static target is never
	 * inlined into main and therefore stays in the crash backtrace. */
	static void (* volatile call_target)(deark*, lctx*, i64, i64) = do_iccprofile_item;
	call_target(&dobj, &d, 0, n);

	/* Only reached by safe inputs. */
	dbuf_close(d.iccprofile_file);
	free(buf);
	return 0;
}

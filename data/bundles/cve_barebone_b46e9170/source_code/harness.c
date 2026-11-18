/* cve_barebone direct-call harness for CVE-2019-19481 (opensc)
 * Target: cac_read_binary  (src/libopensc/card-cac1.c)
 * Bug class: heap-buffer-overflow READ (CWE-125)
 *
 * Root cause: on a FRESH (non-cached) read, cac_read_binary computes
 *   len = MIN(count, priv->cache_buf_len - idx);
 *   if (len && priv->cache_buf) memcpy(buf, &priv->cache_buf[idx], len);
 * with NO check that idx <= priv->cache_buf_len first. The CACHED-read path a
 * few lines above DOES guard this ("if (idx > priv->cache_buf_len)
 * LOG_FUNC_RETURN(ctx, SC_ERROR_FILE_END_REACHED);") -- that same guard is
 * simply missing on the fresh-read path below it. idx is a caller-supplied
 * `unsigned int` (ultimately an attacker-controlled file offset threaded
 * through from the PKCS#15/PKCS#11 read-binary API); priv->cache_buf_len is
 * the size of the certificate actually read off the card (small -- tens to
 * low hundreds of bytes). When idx > cache_buf_len the size_t subtraction
 * `cache_buf_len - idx` wraps to a huge value, so `len = MIN(count, huge) ==
 * count` and the memcpy reads `count` attacker-controlled bytes starting
 * `idx` bytes past the small cache_buf heap allocation -> ASAN
 * heap-buffer-overflow READ.
 *
 * Isolation: cac_read_binary below is copied BYTE-FOR-BYTE from
 * data_cve/cve_b46e9170/target/original_function.c (only a prior forward
 * declaration with __attribute__((noinline)) precedes it, to keep the
 * function's own frame in the ASAN backtrace at -O1; the copied body itself
 * is untouched). Its real supporting type (cac_private_data_t, real name and
 * real field names, trimmed to the 3 fields this call path touches -- see
 * src/libopensc/card-cac-common.h) and the real error-code / MIN macros are
 * copied from src/libopensc/{card-cac-common.h,errors.h,internal.h,
 * opensc.h}. The one real callee on its control-flow path,
 * cac_cac1_get_certificate, does live smart-card APDU I/O
 * (sc_transmit_apdu over a physical/virtual reader) that cannot be exercised
 * off-card and has no bearing on the missing-bounds-check bug (the bug fires
 * on whatever bytes a *successful* call hands back); it is therefore an
 * INCIDENTAL callee and is replaced by a minimal faithful stub carrying the
 * real signature, which hands back harness-controlled "certificate bytes"
 * the same way a real card response would -- this lets the corpus drive
 * idx/count/cache_buf_len exactly as a real caller of cac_read_binary would.
 * sc_log/SC_FUNC_CALLED/LOG_FUNC_RETURN are logging-only in the real driver
 * (log.c formats and writes to a debug channel) -- no-op stubs preserve
 * control flow (LOG_FUNC_RETURN still returns its argument, exactly like the
 * real SC_FUNC_RETURN macro does after logging) without needing the logging
 * subsystem.
 *
 * Build: clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ============================================================= *
 * (b) REAL type definitions (src/libopensc/types.h, opensc.h)   *
 * ============================================================= */
typedef unsigned char u8;                 /* src/libopensc/types.h, verbatim */

struct sc_context;                        /* opaque fwd decl; never dereferenced
                                            * (the no-op log stubs below ignore it) */
typedef struct sc_card {                  /* src/libopensc/opensc.h, real names,
                                            * trimmed to the 2 fields
                                            * cac_read_binary/CAC_DATA touch */
	struct sc_context *ctx;
	void *drv_data;
} sc_card_t;

/* src/libopensc/card-cac-common.h, real name, trimmed to the 3 fields this
 * call path touches (cached/cache_buf/cache_buf_len) -- the other fields
 * (object_type, cert_next, cuid, pki_list, ...) are never referenced here. */
typedef struct cac_private_data {
	u8 *cache_buf;          /* cached version of the currently selected file */
	size_t cache_buf_len;    /* length of the cached selected file */
	int cached;               /* is the cached selected file valid */
} cac_private_data_t;

#define CAC_DATA(card) ((cac_private_data_t*)card->drv_data)   /* card-cac-common.h, verbatim */

/* src/libopensc/internal.h, verbatim */
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/* src/libopensc/errors.h, verbatim values */
#define SC_ERROR_FILE_END_REACHED   -1219
#define SC_ERROR_INVALID_DATA       -1305
#define SC_ERROR_OUT_OF_MEMORY      -1404
#define SC_ERROR_NOT_SUPPORTED      -1408

/* src/libopensc/opensc.h, verbatim (non-Windows branch) */
#define SC_FORMAT_LEN_SIZE_T "z"

/* src/libopensc/log.h, the one enum value cac_read_binary references */
#define SC_LOG_DEBUG_VERBOSE 2

/* ============================================================= *
 * (c) logging macros -- no-op stubs. The real macros only        *
 * format+write a debug log line; discarding that changes no      *
 * control flow or memory (LOG_FUNC_RETURN still returns r, just  *
 * as the real SC_FUNC_RETURN does after logging).                *
 * ============================================================= */
#define SC_FUNC_CALLED(ctx, level)  ((void)0)
#define sc_log(ctx, ...)            ((void)0)
#define LOG_FUNC_RETURN(ctx, r)     return (r)

/* ============================================================= *
 * (c) incidental real callee -- minimal faithful stub with the   *
 * REAL signature. cac_cac1_get_certificate does live APDU I/O    *
 * that cannot run off-card; this stub hands back                 *
 * harness-controlled "certificate bytes" the way a real card     *
 * response would, so the corpus can drive idx/count/             *
 * cache_buf_len/cert_type exactly as a real caller would          *
 * observe. It never touches the bug itself (the bug is the       *
 * missing idx bound check AFTER this call returns, inside        *
 * cac_read_binary's own verbatim body below).                    *
 * ============================================================= */
static u8 *g_cert_blob;
static size_t g_cert_blob_len;

__attribute__((noinline))
static int cac_cac1_get_certificate(sc_card_t *card, u8 **out_buf, size_t *out_len)
{
	(void)card;
	if (g_cert_blob_len == 0)
		return SC_ERROR_INVALID_DATA;
	*out_buf = (u8 *)malloc(g_cert_blob_len);
	if (!*out_buf)
		return SC_ERROR_OUT_OF_MEMORY;
	memcpy(*out_buf, g_cert_blob, g_cert_blob_len);
	*out_len = g_cert_blob_len;
	return (int)g_cert_blob_len;
}

/* forward decl (kept out of the verbatim body) so -O1 does not inline the
 * single call site in main() and drop cac_read_binary's own frame from the
 * ASAN backtrace */
static int cac_read_binary(sc_card_t *card, unsigned int idx,
		unsigned char *buf, size_t count, unsigned long flags)
	__attribute__((noinline));

/* ==== VERBATIM from data_cve/cve_b46e9170/target/original_function.c ==== */
static int cac_read_binary(sc_card_t *card, unsigned int idx,
		unsigned char *buf, size_t count, unsigned long flags)
{
	cac_private_data_t * priv = CAC_DATA(card);
	int r = 0;
	u8 *val = NULL;
	u8 *cert_ptr;
	size_t val_len;
	size_t len, cert_len;
	u8 cert_type;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	/* if we didn't return it all last time, return the remainder */
	if (priv->cached) {
		sc_log(card->ctx, 
			"returning cached value idx=%d count=%"SC_FORMAT_LEN_SIZE_T"u",
			idx, count);
		if (idx > priv->cache_buf_len) {
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_FILE_END_REACHED);
		}
		len = MIN(count, priv->cache_buf_len-idx);
		memcpy(buf, &priv->cache_buf[idx], len);
		LOG_FUNC_RETURN(card->ctx, len);
	}

	sc_log(card->ctx, 
		"clearing cache idx=%d count=%"SC_FORMAT_LEN_SIZE_T"u",
		idx, count);
	free(priv->cache_buf);
	priv->cache_buf = NULL;
	priv->cache_buf_len = 0;

	r = cac_cac1_get_certificate(card, &val, &val_len);
	if (r < 0)
		goto done;
	if (val_len < 1) {
		r = SC_ERROR_INVALID_DATA;
		goto done;
	}

	cert_type = val[0];
	cert_ptr = val + 1;
	cert_len = val_len - 1;

	/* if the info byte is 1, then the cert is compressed, decompress it */
	if ((cert_type & 0x3) == 1) {
#ifdef ENABLE_ZLIB
		r = sc_decompress_alloc(&priv->cache_buf, &priv->cache_buf_len,
			cert_ptr, cert_len, COMPRESSION_AUTO);
#else
		sc_log(card->ctx, "CAC compression not supported, no zlib");
		r = SC_ERROR_NOT_SUPPORTED;
#endif
		if (r)
			goto done;
	} else if (cert_len > 0) {
		priv->cache_buf = malloc(cert_len);
		if (priv->cache_buf == NULL) {
			r = SC_ERROR_OUT_OF_MEMORY;
			goto done;
		}
		priv->cache_buf_len = cert_len;
		memcpy(priv->cache_buf, cert_ptr, cert_len);
	}

	/* OK we've read the data, now copy the required portion out to the callers buffer */
	priv->cached = 1;
	len = MIN(count, priv->cache_buf_len-idx);
	if (len && priv->cache_buf)
		memcpy(buf, &priv->cache_buf[idx], len);
	r = len;
done:
	if (val)
		free(val);
	LOG_FUNC_RETURN(card->ctx, r);
}
/* ==== end verbatim ==== */

/* ============================================================= *
 * (e) direct-call driver                                        *
 * ============================================================= */
int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	/* need idx(4) + count(4) + at least 1 cert_type byte */
	if (sz < 9) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	u8 *fbuf = (u8 *)malloc((size_t)sz);
	if (!fbuf) { fclose(f); return 0; }
	size_t n = fread(fbuf, 1, (size_t)sz, f);
	fclose(f);
	if (n < 9) { free(fbuf); return 0; }

	uint32_t idx32 = 0, count32 = 0;
	memcpy(&idx32, fbuf + 0, 4);
	memcpy(&count32, fbuf + 4, 4);

	/* the "certificate blob" cac_cac1_get_certificate would have handed
	 * back: byte[0] = cert_type, byte[1:] = cert data. HEAP-allocate it
	 * (ASAN-guarded) exactly sized -- this is the small buffer
	 * cac_read_binary's own missing bound check fails to respect. */
	size_t blob_len = n - 8;
	u8 *blob = (u8 *)malloc(blob_len);
	if (!blob) { free(fbuf); return 0; }
	memcpy(blob, fbuf + 8, blob_len);
	free(fbuf);

	g_cert_blob = blob;
	g_cert_blob_len = blob_len;

	/* FDP-style argument construction: idx/count come straight from the
	 * input, buf is a fresh HEAP output buffer sized exactly to count so
	 * the destination side is never itself out of bounds -- isolating the
	 * fault to the source-side (cache_buf) read the bug is about. */
	cac_private_data_t priv;
	memset(&priv, 0, sizeof(priv));
	sc_card_t card;
	memset(&card, 0, sizeof(card));
	card.ctx = NULL;
	card.drv_data = &priv;

	size_t count = (size_t)count32;
	u8 *outbuf = (u8 *)malloc(count ? count : 1);
	if (!outbuf) { free(blob); return 0; }

	int r = cac_read_binary(&card, (unsigned int)idx32, outbuf, count, 0);
	(void)r;

	free(outbuf);
	free(priv.cache_buf);
	free(blob);
	return 0;
}

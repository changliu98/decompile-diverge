/*
 * cve_barebone direct-call harness for CVE-2019-16058 (pam_p11).
 *
 * Target: key_verify (src/pam_p11.c:633), CWE-787 (stack-based buffer
 * overflow, WRITE).
 *
 * Root cause -- fix commit d150b60e1e14c261b113f55681419ad1dfa8a76c
 * ("key_verify(): Fix a stack-based buffer overflow"), diffed against
 * vul_commit 26e329f1a5ec3c2651211a101191ec2d7d5176d3:
 *
 *   -	unsigned char signature[256];
 *   -	unsigned int siglen = sizeof signature;
 *   +	unsigned char *signature = NULL;
 *   +	unsigned int siglen;
 *   ...
 *   +	siglen = EVP_PKEY_size(privkey);
 *   +	signature = malloc(siglen);
 *
 * Pre-fix, key_verify() declares a FIXED 256-byte stack buffer
 * `signature[256]` and hands it straight to
 * EVP_SignFinal(md_ctx, signature, &siglen, privkey) with no size check.
 * OpenSSL's documented EVP_SignFinal() contract (man EVP_SignFinal(3)) is
 * that it writes EVP_PKEY_size(privkey) bytes into `sig` and trusts the
 * CALLER to have pre-sized the buffer -- it performs no bounds check of its
 * own. 256 bytes is exactly right for a 2048-bit RSA key, but
 * PKCS11_get_private_key() can hand back a private key of ANY size the
 * token holds (any ordinary 3072- or 4096-bit RSA key, e.g.) whose
 * EVP_PKEY_size() exceeds 256 -- key_verify() then overflows its own stack
 * buffer by (EVP_PKEY_size(privkey) - 256) bytes, entirely inside its own
 * body, with the write driven purely by the size of the key on the token.
 *
 * Isolation: key_verify() is pasted BYTE-FOR-BYTE below from
 * data_cve/cve_e44be94a/target/original_function.c. Its five external
 * dependencies (pam_handle_t, PKCS11_KEY, EVP_MD, EVP_MD_CTX, EVP_PKEY, plus
 * the API functions on them) come from libp11.h / OpenSSL's own internal
 * headers -- NOT part of this project's source_code (opensc/pam_p11 vendors
 * neither library; both are external system deps) -- and their real struct
 * layouts are private/opaque even to callers: key_verify() itself never
 * reads or writes a field of any of them, only ever passes the pointers
 * through the library API (PKCS11_get_private_key/public_key,
 * EVP_MD_CTX_new/free/reset, the EVP_Sign/EVP_Verify function family, EVP_PKEY_free,
 * ERR_get_error/ERR_reason_error_string). So each type is modeled as an
 * OPAQUE handle, and every API function is a minimal faithful stub --
 * except EVP_SignFinal, which is squarely ON the crash path: it is given
 * ONE synthetic field (EVP_PKEY.sig_len / PKCS11_KEY.sig_len) standing in
 * for "the size in bytes of a signature this key produces" (exactly
 * EVP_PKEY_size()'s real observable value -- 128/256/384/512 bytes for a
 * 1024/2048/3072/4096-bit RSA key), and it reproduces OpenSSL's real,
 * documented, unchecked write of that many bytes into the caller's buffer.
 * That one synthetic field is driven directly by the attacker-controlled
 * input file, exactly modeling "whatever key size the PKCS#11 token
 * reports". Nothing else about the "key" (its bit pattern, its algorithm,
 * whether Sign/Verify round-trip correctly) is observable to key_verify or
 * to ASan, so nothing else needs modeling; randomize() (real, verbatim --
 * trivial and self-contained, only touches /dev/urandom) gates entry but is
 * off the crash path since its output (`challenge`) only ever feeds the
 * (stubbed) Sign/VerifyUpdate calls. prompt()/pam_syslog()/ERR_*() are pure
 * logging/error-path helpers, off the crash path entirely (the overflow
 * trips inside EVP_SignFinal, before any of them can run) -- minimal no-op
 * stubs matching their real signatures.
 *
 * main() reads argv[1] into a HEAP buffer (malloc); its first 4 bytes
 * (little-endian) become the simulated token key's sig_len (default 128, a
 * completely ordinary 1024-bit-RSA size, for files too short to carry one --
 * keeps degenerate inputs SAFE rather than crashing in the harness's own
 * setup), clamped to a plausible RSA/EC range so no input can demand a
 * multi-gigabyte "signature". key_verify() is then called through a
 * volatile function pointer (keeps its own stack frame under -O1, for a
 * clean ASan backtrace) with a heap-allocated PKCS11_KEY carrying that
 * sig_len.
 *
 * Compilation and execution go entirely through ddiv-oracle via
 * scripts/dc_batch.py / dc_try.py; the host toolchain is never invoked.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <syslog.h>

/* ============================================================================
 * Opaque real types (see file header): pam_handle_t from
 * <security/pam_appl.h>, PKCS11_KEY from libp11.h, EVP_MD/EVP_MD_CTX/EVP_PKEY
 * from OpenSSL -- none vendored in source_code (external system deps), all
 * opaque even in their real headers, and key_verify() never touches a field
 * of any of them directly. PKCS11_KEY/EVP_PKEY carry ONE synthetic field
 * (sig_len) -- EVP_PKEY_size()'s real observable value -- see file header.
 * ============================================================================ */
typedef struct pam_handle_t { int _unused; } pam_handle_t;
typedef struct PKCS11_KEY { unsigned int sig_len; } PKCS11_KEY;
typedef struct EVP_MD { int _unused; } EVP_MD;
typedef struct EVP_MD_CTX { int _unused; } EVP_MD_CTX;
typedef struct EVP_PKEY { unsigned int sig_len; } EVP_PKEY;

/* ---- real macros/constants, verbatim (src/pam_p11.c, ENABLE_NLS undefined
 * branch) / security/_pam_types.h ---- */
#define _(string) string
#define PAM_ERROR_MSG 3   /* real Linux-PAM value, security/_pam_types.h */

/* ============================================================================
 * Incidental callees (off the crash path -- see file header): minimal no-op
 * stubs matching their real signatures.
 * ============================================================================ */
static void pam_syslog(pam_handle_t *pamh, int priority, const char *fmt, ...)
{ (void)pamh; (void)priority; (void)fmt; }

/* real signature, src/pam_p11.c:120 */
static int prompt(int flags, pam_handle_t *pamh, int style, char **response,
                   const char *fmt, ...)
{ (void)flags; (void)pamh; (void)style; (void)response; (void)fmt; return 0; }

static unsigned long ERR_get_error(void) { return 0; }
static const char *ERR_reason_error_string(unsigned long e)
{ (void)e; return "unknown error"; }

/* ============================================================================
 * OpenSSL/libp11 API stubs. All incidental EXCEPT EVP_SignFinal (the write
 * that IS the bug -- see file header for its exact faithfulness argument).
 * ============================================================================ */
static const EVP_MD vb_sha1_md = {0};
static const EVP_MD *EVP_sha1(void) { return &vb_sha1_md; }

static EVP_MD_CTX *EVP_MD_CTX_new(void)
{ return (EVP_MD_CTX *)calloc(1, sizeof(EVP_MD_CTX)); }
static void EVP_MD_CTX_free(EVP_MD_CTX *ctx) { free(ctx); }
static int EVP_MD_CTX_reset(EVP_MD_CTX *ctx) { (void)ctx; return 1; }

static int EVP_SignInit(EVP_MD_CTX *ctx, const EVP_MD *type)
{ (void)ctx; (void)type; return 1; }
static int EVP_SignUpdate(EVP_MD_CTX *ctx, const void *d, size_t cnt)
{ (void)ctx; (void)d; (void)cnt; return 1; }

/* THE crash-path call -- see file header: faithful reproduction of
 * OpenSSL's real, documented, unchecked EVP_SignFinal() write contract. */
static int EVP_SignFinal(EVP_MD_CTX *ctx, unsigned char *sig, unsigned int *s,
                          EVP_PKEY *pkey) __attribute__((noinline));
static int EVP_SignFinal(EVP_MD_CTX *ctx, unsigned char *sig, unsigned int *s,
                          EVP_PKEY *pkey)
{
    (void)ctx;
    unsigned int n = pkey->sig_len;
    for (unsigned int i = 0; i < n; i++)
        sig[i] = (unsigned char)(0xA5 ^ (i & 0xff));
    *s = n;
    return 1;
}

static int EVP_VerifyInit(EVP_MD_CTX *ctx, const EVP_MD *type)
{ (void)ctx; (void)type; return 1; }
static int EVP_VerifyUpdate(EVP_MD_CTX *ctx, const void *d, size_t cnt)
{ (void)ctx; (void)d; (void)cnt; return 1; }
static int EVP_VerifyFinal(EVP_MD_CTX *ctx, const unsigned char *sigbuf,
                            unsigned int siglen, EVP_PKEY *pkey)
{ (void)ctx; (void)sigbuf; (void)siglen; (void)pkey; return 1; }

static void EVP_PKEY_free(EVP_PKEY *pkey) { free(pkey); }

/* libp11.h real API: hands back an EVP_PKEY wrapper for the key on the
 * token -- one NEW EVP_PKEY object per call (matches key_verify() freeing
 * pubkey and privkey SEPARATELY in its err: block), carrying the token's
 * reported signature size. */
static EVP_PKEY *PKCS11_get_private_key(PKCS11_KEY *key)
{
    EVP_PKEY *pk = (EVP_PKEY *)malloc(sizeof(EVP_PKEY));
    if (pk) pk->sig_len = key->sig_len;
    return pk;
}
static EVP_PKEY *PKCS11_get_public_key(PKCS11_KEY *key)
{
    EVP_PKEY *pk = (EVP_PKEY *)malloc(sizeof(EVP_PKEY));
    if (pk) pk->sig_len = key->sig_len;
    return pk;
}

/* ============================================================================
 * randomize() -- real function, src/pam_p11.c:617, copied verbatim (trivial,
 * self-contained: only touches /dev/urandom via plain libc calls). Gates
 * key_verify()'s entry but is off the crash path -- its output only ever
 * feeds the (stubbed) Sign/VerifyUpdate calls above.
 * ============================================================================ */
static int randomize(pam_handle_t *pamh, unsigned char *r, unsigned int r_len)
{
	int ok = 0;
	int fd = open("/dev/urandom", O_RDONLY);
	if (0 <= fd && read(fd, r, r_len) == (ssize_t)r_len) {
		ok = 1;
	} else {
		pam_syslog(pamh, LOG_CRIT, "Error reading from /dev/urandom: %s",
				strerror(errno));
	}
	if (0 <= fd) {
		close(fd);
	}
	return ok;
}

/* forward prototype carrying __attribute__((noinline)) so key_verify keeps
 * its own frame in the ASan backtrace at -O1; the verbatim definition below
 * is completely unmodified. */
static int key_verify(pam_handle_t *pamh, int flags, PKCS11_KEY *authkey) __attribute__((noinline));

/* ============================================================================
 * TARGET FUNCTION -- pasted BYTE-FOR-BYTE from
 * data_cve/cve_e44be94a/target/original_function.c (do not edit).
 * ============================================================================ */
static int key_verify(pam_handle_t *pamh, int flags, PKCS11_KEY *authkey)
{
	int ok = 0;
	unsigned char challenge[30];
	unsigned char signature[256];
	unsigned int siglen = sizeof signature;
	const EVP_MD *md = EVP_sha1();
	EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
	EVP_PKEY *privkey = PKCS11_get_private_key(authkey);
	EVP_PKEY *pubkey = PKCS11_get_public_key(authkey);

	/* Verify a SHA-1 hash of random data, signed by the key.
	 *
	 * Note that this will not work keys that aren't eligible for signing.
	 * Unfortunately, libp11 currently has no way of checking
	 * C_GetAttributeValue(CKA_SIGN), see
	 * https://github.com/OpenSC/libp11/issues/219. Since we don't want to
	 * implement try and error, we live with this limitation */
	if (1 != randomize(pamh, challenge, sizeof challenge)) {
		goto err;
	}
	if (NULL == pubkey || NULL == privkey || NULL == md_ctx || NULL == md
			|| !EVP_SignInit(md_ctx, md)
			|| !EVP_SignUpdate(md_ctx, challenge, sizeof challenge)
			|| !EVP_SignFinal(md_ctx, signature, &siglen, privkey)
			|| !EVP_MD_CTX_reset(md_ctx)
			|| !EVP_VerifyInit(md_ctx, md)
			|| !EVP_VerifyUpdate(md_ctx, challenge, sizeof challenge)
			|| 1 != EVP_VerifyFinal(md_ctx, signature, siglen, pubkey)) {
		pam_syslog(pamh, LOG_DEBUG, "Error verifying key: %s\n",
				ERR_reason_error_string(ERR_get_error()));
		prompt(flags, pamh, PAM_ERROR_MSG, NULL, _("Error verifying key"));
		goto err;
	}
	ok = 1;

err:
	if (NULL != pubkey)
		EVP_PKEY_free(pubkey);
	if (NULL != privkey)
		EVP_PKEY_free(privkey);
	if (NULL != md_ctx) {
		EVP_MD_CTX_free(md_ctx);
	}
	return ok;
}/* ============================================================================
 * end verbatim
 * ============================================================================ */

/* ============================================================================
 * Direct-call driver.
 * ============================================================================ */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the corpus input (ASan-guarded). */
    unsigned char *filebuf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!filebuf) { fclose(f); return 0; }
    size_t got = fread(filebuf, 1, (size_t)fsz, f);
    fclose(f);
    (void)got;

    /* FDP-style: first 4 bytes (little-endian) -> simulated PKCS#11 token
     * key signature size (see file header). Short/empty files default to
     * 128 (an ordinary 1024-bit-RSA size) so degenerate inputs stay SAFE. */
    unsigned int sig_len = 128;
    if (fsz >= 4) {
        sig_len = (unsigned int)filebuf[0]
                | ((unsigned int)filebuf[1] << 8)
                | ((unsigned int)filebuf[2] << 16)
                | ((unsigned int)filebuf[3] << 24);
    }
    free(filebuf);
    /* Clamp to a plausible RSA/EC signature-size range (up to a
     * 64Kbit-RSA-sized 8192 bytes) -- a safety net only; every crafted
     * corpus input already carries a value well inside this range. */
    if (sig_len > 8192)
        sig_len = 8192;

    /* Heap-allocated PKCS11_KEY (ASan-guarded), exactly as libp11 would hand
     * back a heap object representing the token's key. */
    PKCS11_KEY *authkey = (PKCS11_KEY *)malloc(sizeof(PKCS11_KEY));
    if (!authkey)
        return 0;
    authkey->sig_len = sig_len;

    pam_handle_t pamh_obj;
    memset(&pamh_obj, 0, sizeof(pamh_obj));

    /* Call through a volatile function pointer so -O1 cannot inline the
     * target into main() -- guarantees key_verify keeps a real stack frame
     * (the crash-stack attribution the classifier checks). */
    int (*volatile fn)(pam_handle_t *, int, PKCS11_KEY *) = key_verify;
    int r = fn(&pamh_obj, 0, authkey);

    free(authkey);
    return (r & 0x7f);
}

/* cve_barebone direct-call harness for cve_cd861998 (libvncserver, CVE-2020-14396)
 * Target: open_ssl_connection  (libvncclient/tls_openssl.c)
 * Bug class: NULL pointer dereference (CWE-476).
 *
 * See the module docstring of scripts/gen_dc_cve_cd861998.py for the full mechanism.
 * In short: the vulnerable open_ssl_connection reads
 *   cred->x509Credential.x509CrlVerifyMode
 * unconditionally as its very first statement, BEFORE the `if (!anonTLS)` guard
 * that (post-fix) protects it. The real anonymous-TLS auth path
 * (HandleAnonTLSAuth -> InitializeTLSSession) calls this function with cred==NULL,
 * so a server merely offering anonymous TLS drives a NULL dereference here.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real rfbBool / TRUE / FALSE (rfb/rfbproto.h, non-Windows branch, verbatim) ---- */
typedef int8_t rfbBool;
#define FALSE 0
#define TRUE -1

/* ---- real rfbClientLogProc + rfbClientLog global (rfb/rfbclient.h:469-470, verbatim
 * declaration shape: `extern rfbClientLogProc rfbClientLog,rfbClientErr;` -- only
 * rfbClientLog is called by open_ssl_connection). Body is a faithful no-op logger
 * (incidental to the crash: it never touches `cred`/`client` and both the triggering
 * and safe paths must simply not crash while logging). ---- */
typedef void (*rfbClientLogProc)(const char *format, ...);
static void vb_null_log(const char *format, ...) { (void)format; }
rfbClientLogProc rfbClientLog = vb_null_log;

/* ---- real rfbCredential union, x509Credential arm (rfb/rfbclient.h:135-152, verbatim
 * field names/order/types) ---- */
typedef union _rfbCredential
{
  struct
  {
    char *x509CACertFile;
    char *x509CACrlFile;
    char *x509ClientCertFile;
    char *x509ClientKeyFile;
    uint8_t x509CrlVerifyMode;
  } x509Credential;
  struct
  {
    char *username;
    char *password;
  } userCredential;
} rfbCredential;

/* ---- real rfbX509CrlVerify* values (rfb/rfbclient.h:160-162, verbatim) ---- */
#define rfbX509CrlVerifyNone   0
#define rfbX509CrlVerifyClient 1
#define rfbX509CrlVerifyAll    2

/* ---- rfbClient: REDUCED to the one real-named field open_ssl_connection actually
 * dereferences (serverHost). The real struct (rfb/rfbclient.h) carries ~150 more
 * fields (X11 display/visual state, pixel format, pthread mutexes, zlib/tight codec
 * buffers, ...) -- confirmed by inspection that open_ssl_connection touches nothing
 * else on `client` (it is otherwise passed through opaquely to
 * SSL_CTX_set_app_data(ssl_ctx, client), never dereferenced there either). ---- */
typedef struct _rfbClient {
  char *serverHost;
} rfbClient;

/* ---- OpenSSL opaque types (the real library headers forward-declare all of these
 * the same way; open_ssl_connection never reaches into their internals -- it only
 * ever holds/passes the pointers to the OpenSSL API, stubbed below). ---- */
typedef struct ssl_ctx_st SSL_CTX;
typedef struct ssl_st SSL;
typedef struct ssl_method_st SSL_METHOD;
typedef struct x509_verify_param_st X509_VERIFY_PARAM;
typedef struct x509_store_ctx_st X509_STORE_CTX;

/* ---- real OpenSSL constants (openssl/ssl.h, openssl/x509_vfy.h) ---- */
#define SSL_VERIFY_PEER 0x01
#define SSL_FILETYPE_PEM 1
#define X509_V_FLAG_CRL_CHECK 0x4
#define X509_V_FLAG_CRL_CHECK_ALL 0x8000

/* ================= OpenSSL API stubs =================
 * Every one of these is incidental to the CVE: the vulnerable read of `cred` happens
 * on open_ssl_connection's very first statement, BEFORE any of them are called,
 * so none of them execute on a triggering run. On a safe run (valid cred) their
 * exact internal behavior doesn't matter either -- only that the calls the real
 * function makes resolve and succeed deterministically, so the safe corpus exercises
 * open_ssl_connection's own control flow (both the anonTLS and !anonTLS branches)
 * without linking the real OpenSSL library. Struct bodies are minimal (never
 * introspected by open_ssl_connection); alloc/free stubs use real malloc/free so
 * ASAN can track them like any other heap object (detect_leaks=0 in the runner, so
 * the intentionally-unfreed ssl_ctx/ssl on the success path -- exactly like the real
 * function, which leaves ssl_ctx's lifetime to SSL's internal refcounting -- is not
 * flagged). */
struct ssl_ctx_st { int dummy; };
struct ssl_st { int dummy; };
struct ssl_method_st { int dummy; };
struct x509_verify_param_st { int dummy; };

static SSL_METHOD *SSLv23_client_method(void)
{
  static SSL_METHOD m;
  return &m;
}

static SSL_CTX *SSL_CTX_new(const SSL_METHOD *meth)
{
  (void)meth;
  return (SSL_CTX *)calloc(1, sizeof(SSL_CTX));
}

static void SSL_CTX_free(SSL_CTX *ctx)
{
  free(ctx);
}

static int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile, const char *CApath)
{
  (void)ctx; (void)CAfile; (void)CApath;
  return 1; /* success */
}

static void SSL_CTX_set_default_verify_paths(SSL_CTX *ctx)
{
  (void)ctx;
}

static int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file)
{
  (void)ctx; (void)file;
  return 1; /* success */
}

static int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type)
{
  (void)ctx; (void)file; (void)type;
  return 1; /* success */
}

static int SSL_CTX_check_private_key(const SSL_CTX *ctx)
{
  (void)ctx;
  return 1; /* keys match */
}

static void SSL_CTX_set_verify(SSL_CTX *ctx, int mode, int (*callback)(int, X509_STORE_CTX *))
{
  (void)ctx; (void)mode; (void)callback;
}

static int SSL_CTX_set1_param(SSL_CTX *ctx, X509_VERIFY_PARAM *vpm)
{
  (void)ctx; (void)vpm;
  return 1;
}

static int SSL_CTX_set_app_data(SSL_CTX *ctx, void *arg)
{
  (void)ctx; (void)arg;
  return 1;
}

static X509_VERIFY_PARAM *X509_VERIFY_PARAM_new(void)
{
  return (X509_VERIFY_PARAM *)calloc(1, sizeof(X509_VERIFY_PARAM));
}

static void X509_VERIFY_PARAM_free(X509_VERIFY_PARAM *param)
{
  free(param);
}

static int X509_VERIFY_PARAM_set_flags(X509_VERIFY_PARAM *param, unsigned long flags)
{
  (void)param; (void)flags;
  return 1;
}

static int X509_VERIFY_PARAM_set1_host(X509_VERIFY_PARAM *param, const char *name, size_t namelen)
{
  (void)param; (void)name; (void)namelen;
  return 1; /* success */
}

static SSL *SSL_new(SSL_CTX *ctx)
{
  (void)ctx;
  return (SSL *)calloc(1, sizeof(SSL));
}

static void SSL_free(SSL *ssl)
{
  free(ssl);
}

static int SSL_set_cipher_list(SSL *ssl, const char *str)
{
  (void)ssl; (void)str;
  return 1;
}

static int SSL_set_fd(SSL *ssl, int fd)
{
  (void)ssl; (void)fd;
  return 1;
}

/* Always succeeds on the first try -> the do/while loop in open_ssl_connection
 * always completes in exactly one iteration, so wait_for_data() below is provably
 * never invoked at runtime (it must still be defined for the call site to link). */
static int SSL_connect(SSL *ssl)
{
  (void)ssl;
  return 1;
}

static int SSL_shutdown(SSL *ssl)
{
  (void)ssl;
  return 1;
}

/* ================= project helper stubs (source_code/libvncclient/tls_openssl.c) =====
 * Real signatures, verbatim (same file as open_ssl_connection). Both are incidental:
 * load_crls_from_file is only reached inside `if (!anonTLS)` when a CRL file pointer
 * is present (irrelevant to the NULL-cred crash, which fires long before);
 * wait_for_data is only reached if SSL_connect() ever returns something other than 1,
 * which the stub above never does. */
static rfbBool load_crls_from_file(char *file, SSL_CTX *ssl_ctx)
{
  (void)file; (void)ssl_ctx;
  return TRUE;
}

static int wait_for_data(SSL *ssl, int ret, int timeout)
{
  (void)ssl; (void)ret; (void)timeout;
  return 1;
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline so the function keeps its own frame in the ASAN crash backtrace (it has a
 * single call site in main(), a strong -O1 inlining candidate otherwise). */
__attribute__((noinline))
static SSL *
open_ssl_connection (rfbClient *client, int sockfd, rfbBool anonTLS, rfbCredential *cred)
{
  SSL_CTX *ssl_ctx = NULL;
  SSL *ssl = NULL;
  int n, finished = 0;
  X509_VERIFY_PARAM *param;
  uint8_t verify_crls = cred->x509Credential.x509CrlVerifyMode;

  if (!(ssl_ctx = SSL_CTX_new(SSLv23_client_method())))
  {
    rfbClientLog("Could not create new SSL context.\n");
    return NULL;
  }

  param = X509_VERIFY_PARAM_new();

  /* Setup verification if not anonymous */
  if (!anonTLS)
  {
    if (cred->x509Credential.x509CACertFile)
    {
      if (!SSL_CTX_load_verify_locations(ssl_ctx, cred->x509Credential.x509CACertFile, NULL))
      {
        rfbClientLog("Failed to load CA certificate from %s.\n",
                     cred->x509Credential.x509CACertFile);
        goto error_free_ctx;
      }
    } else {
      rfbClientLog("Using default paths for certificate verification.\n");
      SSL_CTX_set_default_verify_paths (ssl_ctx);
    }

    if (cred->x509Credential.x509CACrlFile)
    {
      if (!load_crls_from_file(cred->x509Credential.x509CACrlFile, ssl_ctx))
      {
        rfbClientLog("CRLs could not be loaded.\n");
        goto error_free_ctx;
      }
      if (verify_crls == rfbX509CrlVerifyNone) verify_crls = rfbX509CrlVerifyAll;
    }

    if (cred->x509Credential.x509ClientCertFile && cred->x509Credential.x509ClientKeyFile)
    {
      if (SSL_CTX_use_certificate_chain_file(ssl_ctx, cred->x509Credential.x509ClientCertFile) != 1)
      {
        rfbClientLog("Client certificate could not be loaded.\n");
        goto error_free_ctx;
      }

      if (SSL_CTX_use_PrivateKey_file(ssl_ctx, cred->x509Credential.x509ClientKeyFile,
                                      SSL_FILETYPE_PEM) != 1)
      {
        rfbClientLog("Client private key could not be loaded.\n");
        goto error_free_ctx;
      }

      if (SSL_CTX_check_private_key(ssl_ctx) == 0) {
        rfbClientLog("Client certificate and private key do not match.\n");
        goto error_free_ctx;
      }
    }

    SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);

    if (verify_crls == rfbX509CrlVerifyClient) 
      X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK);
    else if (verify_crls == rfbX509CrlVerifyAll)
      X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL);

    if(!X509_VERIFY_PARAM_set1_host(param, client->serverHost, strlen(client->serverHost)))
    {
      rfbClientLog("Could not set server name for verification.\n");
      goto error_free_ctx;
    }
    SSL_CTX_set1_param(ssl_ctx, param);
  }

  if (!(ssl = SSL_new (ssl_ctx)))
  {
    rfbClientLog("Could not create a new SSL session.\n");
    goto error_free_ctx;
  }

  /* TODO: finetune this list, take into account anonTLS bool */
  SSL_set_cipher_list(ssl, "ALL");

  SSL_set_fd (ssl, sockfd);
  SSL_CTX_set_app_data (ssl_ctx, client);

  do
  {
    n = SSL_connect(ssl);
		
    if (n != 1) 
    {
      if (wait_for_data(ssl, n, 1) != 1) 
      {
        finished = 1;
        SSL_shutdown(ssl);

        goto error_free_ssl;
      }
    }
  } while( n != 1 && finished != 1 );

  X509_VERIFY_PARAM_free(param);
  return ssl;

error_free_ssl:
  SSL_free(ssl);

error_free_ctx:
  X509_VERIFY_PARAM_free(param);
  SSL_CTX_free(ssl_ctx);

  return NULL;
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Input format (attacker-controlled file, read into a HEAP buffer):
 *   byte[0] bit0 : cred_null   (1 -> cred = NULL  => TRIGGER; 0 -> cred = valid => safe)
 *   byte[1] bit0 : anonTLS     (1 -> TRUE, skips the `if (!anonTLS)` cert/CRL block;
 *                                0 -> FALSE, takes the full block -- only consulted
 *                                when cred is valid; irrelevant on the crash path,
 *                                which fires before anonTLS is ever read)
 *   byte[2] bit0 : x509CACertFile present   (non-NULL "ca.pem" vs NULL)
 *   byte[3] bit0 : x509CACrlFile present    (non-NULL "crl.pem" vs NULL)
 *   byte[4] bit0 : x509ClientCertFile present (non-NULL "cert.pem" vs NULL)
 *   byte[5] bit0 : x509ClientKeyFile present  (non-NULL "key.pem" vs NULL)
 *   byte[6]       : x509CrlVerifyMode = byte[6] % 3
 *   byte[7]       : low byte of the (unused-by-the-bug) sockfd argument
 * Missing bytes default to 0. Short/empty files degrade safely (all-zero => cred
 * non-NULL, anonTLS FALSE, no cert files, mode 0).
 *
 * TRIGGER: byte[0] odd -> cred passed as NULL, AND byte[1] even -> anonTLS passed
 * FALSE (required at the mandated -O1: with anonTLS TRUE the compiler proves the
 * top-of-function verify_crls load dead on that path and elides it -- see the
 * EMPIRICAL COMPILER NOTE in this script's module docstring). With anonTLS FALSE,
 * open_ssl_connection enters `if (!anonTLS)` and its first statement there,
 * `if (cred->x509Credential.x509CACertFile)`, unconditionally dereferences the NULL
 * cred -> SEGV at a low unmapped address, entirely inside open_ssl_connection,
 * before any stub/OpenSSL call is made.
 * SAFE: byte[0] even -> cred points at a heap-allocated, fully-populated
 * rfbCredential; every OpenSSL/project stub call the real function body can reach
 * (either branch of `if (!anonTLS)`) succeeds deterministically, so the function
 * runs to one of its normal `return` statements and the process exits 0.
 */
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
  uint8_t *data = (uint8_t *)malloc(n ? n : 1); /* HEAP input, ASAN-guarded */
  if (!data) { fclose(fp); return 64; }
  size_t got = n ? fread(data, 1, n, fp) : 0;
  fclose(fp);
  if (got != n) { free(data); return 64; }

  uint8_t b0 = n > 0 ? data[0] : 0;
  uint8_t b1 = n > 1 ? data[1] : 0;
  uint8_t b2 = n > 2 ? data[2] : 0;
  uint8_t b3 = n > 3 ? data[3] : 0;
  uint8_t b4 = n > 4 ? data[4] : 0;
  uint8_t b5 = n > 5 ? data[5] : 0;
  uint8_t b6 = n > 6 ? data[6] : 0;
  uint8_t b7 = n > 7 ? data[7] : 0;

  int cred_is_null = (b0 & 1);
  rfbBool anonTLS = (b1 & 1) ? TRUE : FALSE;

  rfbClient *client = (rfbClient *)malloc(sizeof(rfbClient));
  client->serverHost = strdup("vnc.example.org");

  rfbCredential *cred = NULL;
  if (!cred_is_null) {
    cred = (rfbCredential *)malloc(sizeof(rfbCredential));
    cred->x509Credential.x509CACertFile    = (b2 & 1) ? "ca.pem"   : NULL;
    cred->x509Credential.x509CACrlFile     = (b3 & 1) ? "crl.pem"  : NULL;
    cred->x509Credential.x509ClientCertFile = (b4 & 1) ? "cert.pem" : NULL;
    cred->x509Credential.x509ClientKeyFile  = (b5 & 1) ? "key.pem"  : NULL;
    cred->x509Credential.x509CrlVerifyMode  = (uint8_t)(b6 % 3);
  }

  int sockfd = (int)b7;

  /* volatile function pointer: an extra belt-and-suspenders guard (on top of
   * noinline) against the single call site being folded into main(). */
  SSL *(*volatile vb_call)(rfbClient *, int, rfbBool, rfbCredential *) = open_ssl_connection;
  SSL *ssl = vb_call(client, sockfd, anonTLS, cred);
  (void)ssl;

  /* Only reached on a SAFE run (a triggering run SEGVs inside the call above). */
  if (cred) free(cred);
  free(client->serverHost);
  free(client);
  free(data);
  return 0;
}

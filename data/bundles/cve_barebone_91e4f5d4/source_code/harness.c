/*
 * cve_barebone direct-call harness for CVE-2016-8706-class bug (memcached)
 * Target: try_read_command_binary  (memcached.c)
 * Fix commit: 02c6a2b62ddcb6fa4569a591d3461a156a636305
 *
 * Root cause: the binary-protocol header's `extlen` field is a plain uint8_t
 * (attacker-controlled, range 0..255), but the "extra" bytes that follow the
 * header are copied into a fixed-size STACK buffer sized for the protocol's
 * documented maximum extlen (BIN_MAX_EXTLEN == 20, memcached.h:73):
 *
 *     char extbuf[sizeof(c->binary_header) + BIN_MAX_EXTLEN];   // 24+20 = 44 bytes
 *     memcpy(extbuf + sizeof(c->binary_header),
 *            c->rcurr + sizeof(c->binary_header), extlen);
 *
 * extlen is never clamped to BIN_MAX_EXTLEN before the memcpy, so any request
 * whose header declares extlen > 20 writes (extlen - 20) bytes past the end of
 * `extbuf` on the stack -> stack-buffer-overflow WRITE (CWE-787). The upstream
 * fix (diff below) grows the buffer by 1 and clamps the copy length to
 * BIN_MAX_EXTLEN:
 *
 *     char extbuf[sizeof(c->binary_header) + BIN_MAX_EXTLEN+1];
 *     memcpy(extbuf + sizeof(c->binary_header), c->rcurr + sizeof(c->binary_header),
 *             extlen > BIN_MAX_EXTLEN ? BIN_MAX_EXTLEN : extlen);
 *
 * try_read_command_binary() itself only depends on: the binary-protocol wire
 * header layout (protocol_binary.h, copied verbatim), a handful of `conn`
 * fields it reads/writes (a minimal-but-real subset of the real `struct conn`
 * -- real names/types, unused fields omitted), the global `settings.verbose`
 * flag, the global `current_time`, `ntohll()` (copied verbatim from util.c),
 * and three incidental callees (`resp_start`, `conn_set_state`,
 * `dispatch_bin_command`) that are stubbed minimally below because none of
 * them lie on the crash path itself (the crash fires inside the memcpy,
 * before dispatch_bin_command is ever reached, and resp_start/conn_set_state
 * only need to satisfy the guard so execution reaches that memcpy).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <arpa/inet.h>  /* ntohs()/ntohl(), used verbatim in try_read_command_binary */

/* ---------------------------------------------------------------------
 * protocol_binary.h (memcached, real repo) -- wire header, copied verbatim
 * (only the pieces try_read_command_binary actually references).
 * --------------------------------------------------------------------- */
typedef enum {
    PROTOCOL_BINARY_REQ = 0x80,
    PROTOCOL_BINARY_RES = 0x81
} protocol_binary_magic;

typedef union {
    struct {
        uint8_t magic;
        uint8_t opcode;
        uint16_t keylen;
        uint8_t extlen;
        uint8_t datatype;
        uint16_t reserved;
        uint32_t bodylen;
        uint32_t opaque;
        uint64_t cas;
    } request;
    uint8_t bytes[24];
} protocol_binary_request_header;

/* ---------------------------------------------------------------------
 * memcached.h -- real macro/enum, copied verbatim (memcached.h:73, :186-199).
 * --------------------------------------------------------------------- */
#define BIN_MAX_EXTLEN 20 // length of the _incr command is currently the longest.

enum conn_states {
    conn_listening,  /**< the socket which listens for connections */
    conn_new_cmd,    /**< Prepare connection for next command */
    conn_waiting,    /**< waiting for a readable socket */
    conn_read,       /**< reading in a command line */
    conn_parse_cmd,  /**< try to parse a command from the input buffer */
    conn_write,      /**< writing out a simple response */
    conn_nread,      /**< reading in a fixed number of bytes */
    conn_swallow,    /**< swallowing unnecessary bytes w/o storing */
    conn_closing,    /**< closing this connection */
    conn_mwrite,     /**< writing out many items sequentially */
    conn_closed,     /**< connection is closed */
    conn_watch,      /**< held by the logger thread as a watcher */
    conn_max_state   /**< Max state value (used for assertion) */
};

/* logger.h:14 */
typedef unsigned int rel_time_t;

/* memcached.h:389+ (real global, real field name -- only `verbose` is read
 * by try_read_command_binary, so only that field is carried here). */
struct settings {
    int verbose;
};
struct settings settings;

/* memcached.h:750-751 (real global) */
volatile rel_time_t current_time;

/* Minimal-but-real subset of memcached.h:668 `struct conn` -- only the
 * fields try_read_command_binary's own body reads or writes; real names
 * and real types throughout, nothing invented. */
typedef struct conn conn;
struct conn {
    int    sfd;
    enum conn_states state;
    rel_time_t last_cmd_time;
    char   *rcurr;  /** but if we parsed some already, this is where we stopped */
    int    rbytes;  /** how much data, starting from rcur, do we have unparsed */
    protocol_binary_request_header binary_header;
    uint64_t cas; /* the cas to return */
    short cmd; /* current command being processed */
    int opaque;
    int keylen;
};

/* ---------------------------------------------------------------------
 * util.c:239-259 -- ntohll(), copied verbatim (x86_64 build => little-endian).
 * --------------------------------------------------------------------- */
#define ENDIAN_LITTLE 1
static uint64_t mc_swap64(uint64_t in) {
#ifdef ENDIAN_LITTLE
    /* Little endian, flip the bytes around until someone makes a faster/better
    * way to do this. */
    int64_t rv = 0;
    int i = 0;
     for(i = 0; i<8; i++) {
        rv = (rv << 8) | (in & 0xff);
        in >>= 8;
     }
    return rv;
#else
    /* big-endian machines don't need byte swapping */
    return in;
#endif
}

uint64_t ntohll(uint64_t val) {
   return mc_swap64(val);
}

/* ---------------------------------------------------------------------
 * Incidental callees, minimally stubbed (none lie on the crash path):
 * resp_start()/conn_set_state() only gate reaching the vulnerable memcpy
 * (memcached.c:1022, :966); dispatch_bin_command() (memcached.c:2146) is
 * only reached AFTER that memcpy, i.e. never on a triggering input.
 * --------------------------------------------------------------------- */
static bool resp_start(conn *c) {
    (void)c;
    return true;
}

static void conn_set_state(conn *c, enum conn_states state) {
    assert(c);
    c->state = state;
}

/* Written-but-never-read-elsewhere sink so the compiler cannot prove the
 * memcpy into `extbuf` (inside the verbatim function, below) is a dead
 * store and fold it away -- real dispatch_bin_command interprets exactly
 * this region (sizeof(header)+BIN_MAX_EXTLEN worth of "extra" bytes) as
 * per-opcode overlaid structs; volatile forces the read+write to survive
 * optimization instead of silently masking the overflow. */
static volatile uint8_t g_extbuf_sink;

static void dispatch_bin_command(conn *c, char *extbuf) {
    (void)c;
    uint8_t acc = 0;
    for (size_t i = 0; i < sizeof(protocol_binary_request_header) + BIN_MAX_EXTLEN; i++) {
        acc ^= (uint8_t)extbuf[i];
    }
    g_extbuf_sink = acc;
}

/* ==== VERBATIM from data_cve/cve_91e4f5d4/target/original_function.c ==== */
static int try_read_command_binary(conn *c) {
    /* Do we have the complete packet header? */
    if (c->rbytes < sizeof(c->binary_header)) {
        /* need more data! */
        return 0;
    } else {
        memcpy(&c->binary_header, c->rcurr, sizeof(c->binary_header));
        protocol_binary_request_header* req;
        req = &c->binary_header;

        if (settings.verbose > 1) {
            /* Dump the packet before we convert it to host order */
            int ii;
            fprintf(stderr, "<%d Read binary protocol data:", c->sfd);
            for (ii = 0; ii < sizeof(req->bytes); ++ii) {
                if (ii % 4 == 0) {
                    fprintf(stderr, "\n<%d   ", c->sfd);
                }
                fprintf(stderr, " 0x%02x", req->bytes[ii]);
            }
            fprintf(stderr, "\n");
        }

        c->binary_header = *req;
        c->binary_header.request.keylen = ntohs(req->request.keylen);
        c->binary_header.request.bodylen = ntohl(req->request.bodylen);
        c->binary_header.request.cas = ntohll(req->request.cas);

        if (c->binary_header.request.magic != PROTOCOL_BINARY_REQ) {
            if (settings.verbose) {
                fprintf(stderr, "Invalid magic:  %x\n",
                        c->binary_header.request.magic);
            }
            conn_set_state(c, conn_closing);
            return -1;
        }

        uint8_t extlen = c->binary_header.request.extlen;
        uint16_t keylen = c->binary_header.request.keylen;
        if (c->rbytes < keylen + extlen + sizeof(c->binary_header)) {
            // Still need more bytes. Let try_read_network() realign the
            // read-buffer and fetch more data as necessary.
            return 0;
        }

        if (!resp_start(c)) {
            conn_set_state(c, conn_closing);
            return -1;
        }

        c->cmd = c->binary_header.request.opcode;
        c->keylen = c->binary_header.request.keylen;
        c->opaque = c->binary_header.request.opaque;
        /* clear the returned cas value */
        c->cas = 0;

        c->last_cmd_time = current_time;
        // sigh. binprot has no "largest possible extlen" define, and I don't
        // want to refactor a ton of code either. Header is only ever used out
        // of c->binary_header, but the extlen stuff is used for the latter
        // bytes. Just wastes 24 bytes on the stack this way.
        char extbuf[sizeof(c->binary_header) + BIN_MAX_EXTLEN];
        memcpy(extbuf + sizeof(c->binary_header), c->rcurr + sizeof(c->binary_header), extlen);
        c->rbytes -= sizeof(c->binary_header) + extlen + keylen;
        c->rcurr += sizeof(c->binary_header) + extlen + keylen;

        dispatch_bin_command(c, extbuf);
    }

    return 1;
}
/* ==== end verbatim ==== */

/*
 * Harness-authored driver.
 *
 * Wire-format input (raw bytes, no framing added):
 *   [0]      magic     = 0x80 (PROTOCOL_BINARY_REQ)
 *   [1]      opcode     (arbitrary, varies per input for diversity)
 *   [2..3]   keylen     = 0x0000 (network order) -- kept 0 to keep the
 *                          "do we have enough bytes yet" guard trivially
 *                          satisfied for any extlen
 *   [4]      extlen     = the byte under test (0..255, single byte so no
 *                          network-order swap applies)
 *   [5]      datatype   = 0
 *   [6..7]   reserved   = 0
 *   [8..11]  bodylen    = 0 (network order)
 *   [12..15] opaque     = 0 (network order)
 *   [16..23] cas        = 0
 *   [24 .. 24+extlen-1] "extra" bytes (filler)
 *
 * The file is sized to exactly 24+extlen bytes, so the heap buffer backing
 * `c->rcurr` is exactly big enough for the function's own bounds check
 * (c->rbytes == 24+extlen >= keylen+extlen+sizeof(header)) to pass and for
 * the extlen-byte READ from c->rcurr+24 to stay fully in-bounds -- isolating
 * the crash to the STACK WRITE overflow into `extbuf` (extlen > BIN_MAX_EXTLEN
 * == 20), not an incidental heap read overflow.
 */
int main(int argc, char **argv) {
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    rewind(f);

    char *buf = (char *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (!buf) { fclose(f); return 0; }
    size_t got = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if ((long)got != sz) { free(buf); return 0; }

    conn c;
    memset(&c, 0, sizeof(c));
    c.sfd = 0;
    c.rcurr = buf;
    c.rbytes = (int)sz;

    try_read_command_binary(&c);

    free(buf);
    return 0;
}

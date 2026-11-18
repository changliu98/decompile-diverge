/* cve_barebone direct-call harness for CVE-2017-15908 (systemd-resolved)
 * Target: dns_packet_is_reply_for()  (src/resolve/resolved-dns-packet.c)
 * Fix commit: a924f43f30f9c4acaf70618dd2a055f8b0f166be
 *
 * Bug (present in vul_commit d82c4b9a7be6dc8f340930b5e80968d0e48c4c57):
 *
 *     r = dns_packet_extract(p);
 *     if (r < 0)
 *             return r;
 *
 *     if (p->question->n_keys != 1)     <-- NULL pointer READ (CWE-476)
 *             return 0;
 *
 * dns_packet_extract() (copied verbatim below) only allocates p->question
 * when the packet's QDCOUNT (Question-count header field) is > 0:
 *
 *     n = DNS_PACKET_QDCOUNT(p);
 *     if (n > 0) {
 *             question = dns_question_new(n);
 *             ...
 *     }
 *     ...
 *     p->question = question;   <-- still NULL if QDCOUNT was 0
 *     p->extracted = true;
 *     return 0;                 <-- SUCCESS, despite p->question == NULL
 *
 * So a spec-legal DNS message with the QR ("this is a response") bit set
 * and an EMPTY Question section (QDCOUNT=0) makes dns_packet_extract()
 * return success while leaving p->question NULL, and
 * dns_packet_is_reply_for() unconditionally dereferences
 * p->question->n_keys right after -- a NULL pointer read. The fix adds
 * `if (!p->question) return 0;` between the two. This is a real-world DNS
 * resolver crash: any off-path/spoofed or malfunctioning server reply
 * with no questions echoed back triggers it.
 *
 * This harness constructs the DnsPacket exactly the way a real caller
 * does (a heap object whose ->_data points at the received wire bytes,
 * ->size/->rindex set the way dns_packet_new() sets them) and calls the
 * real, public dns_packet_is_reply_for() entry point. dns_packet_extract()
 * -- the ONE callee directly on the crash path -- is copied verbatim,
 * byte-for-byte, from resolved-dns-packet.c, together with the real
 * DnsPacket/DnsPacketHeader/DnsQuestion/DnsResourceKey structs and
 * DNS_PACKET_* macros it and the target function need. Its own callees
 * (the full question/answer/EDNS0-OPT record parser: dns_packet_read_key,
 * dns_packet_read_rr, dns_question_new/add, dns_answer_new/add,
 * opt_is_good, ...) are INCIDENTAL to this bug -- they only run when
 * QDCOUNT>0 or (ANCOUNT+NSCOUNT+ARCOUNT)>0, a case this harness's corpus
 * never constructs (every crafted input, triggering AND safe, carries
 * QDCOUNT=ANCOUNT=NSCOUNT=ARCOUNT=0) -- so they are minimal, clearly
 * unreachable stubs, present only so the verbatim dns_packet_extract()
 * body still type-checks and links. See the per-symbol comments below.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>

/* ==== VERBATIM from source_code/src/basic/sparse-endian.h ==== */

/* Copyright (c) 2012 Josh Triplett <josh@joshtriplett.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef SPARSE_ENDIAN_H
#define SPARSE_ENDIAN_H

#include <byteswap.h>
#include <endian.h>
#include <stdint.h>

#ifdef __CHECKER__
#define __sd_bitwise __attribute__((bitwise))
#define __sd_force __attribute__((force))
#else
#define __sd_bitwise
#define __sd_force
#endif

typedef uint16_t __sd_bitwise le16_t;
typedef uint16_t __sd_bitwise be16_t;
typedef uint32_t __sd_bitwise le32_t;
typedef uint32_t __sd_bitwise be32_t;
typedef uint64_t __sd_bitwise le64_t;
typedef uint64_t __sd_bitwise be64_t;

#undef htobe16
#undef htole16
#undef be16toh
#undef le16toh
#undef htobe32
#undef htole32
#undef be32toh
#undef le32toh
#undef htobe64
#undef htole64
#undef be64toh
#undef le64toh

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define bswap_16_on_le(x) __bswap_16(x)
#define bswap_32_on_le(x) __bswap_32(x)
#define bswap_64_on_le(x) __bswap_64(x)
#define bswap_16_on_be(x) (x)
#define bswap_32_on_be(x) (x)
#define bswap_64_on_be(x) (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define bswap_16_on_le(x) (x)
#define bswap_32_on_le(x) (x)
#define bswap_64_on_le(x) (x)
#define bswap_16_on_be(x) __bswap_16(x)
#define bswap_32_on_be(x) __bswap_32(x)
#define bswap_64_on_be(x) __bswap_64(x)
#endif

static inline le16_t htole16(uint16_t value) { return (le16_t __sd_force) bswap_16_on_be(value); }
static inline le32_t htole32(uint32_t value) { return (le32_t __sd_force) bswap_32_on_be(value); }
static inline le64_t htole64(uint64_t value) { return (le64_t __sd_force) bswap_64_on_be(value); }

static inline be16_t htobe16(uint16_t value) { return (be16_t __sd_force) bswap_16_on_le(value); }
static inline be32_t htobe32(uint32_t value) { return (be32_t __sd_force) bswap_32_on_le(value); }
static inline be64_t htobe64(uint64_t value) { return (be64_t __sd_force) bswap_64_on_le(value); }

static inline uint16_t le16toh(le16_t value) { return bswap_16_on_be((uint16_t __sd_force)value); }
static inline uint32_t le32toh(le32_t value) { return bswap_32_on_be((uint32_t __sd_force)value); }
static inline uint64_t le64toh(le64_t value) { return bswap_64_on_be((uint64_t __sd_force)value); }

static inline uint16_t be16toh(be16_t value) { return bswap_16_on_le((uint16_t __sd_force)value); }
static inline uint32_t be32toh(be32_t value) { return bswap_32_on_le((uint32_t __sd_force)value); }
static inline uint64_t be64toh(be64_t value) { return bswap_64_on_le((uint64_t __sd_force)value); }

#undef __sd_bitwise
#undef __sd_force

#endif /* SPARSE_ENDIAN_H */

/* ==== end verbatim ==== */

/* ==== VERBATIM fragments from source_code/src/basic/macro.h ==== */

#define _likely_(x) (__builtin_expect(!!(x),1))
#define _unlikely_(x) (__builtin_expect(!!(x),0))

#define _cleanup_(x) __attribute__((cleanup(x)))



#define ALIGN4(l) (((l) + 3) & ~3)
#define ALIGN8(l) (((l) + 7) & ~7)

#if __SIZEOF_POINTER__ == 8
#define ALIGN(l) ALIGN8(l)
#elif __SIZEOF_POINTER__ == 4
#define ALIGN(l) ALIGN4(l)
#else
#error "Wut? Pointers are neither 4 nor 8 bytes long?"
#endif

/* ==== end verbatim ==== */

/* ==== VERBATIM from source_code/src/basic/in-addr-util.h ==== */

union in_addr_union {
        struct in_addr in;
        struct in6_addr in6;
};

/* ==== end verbatim ==== */

/* Forward typedefs -- mirrors how the real headers forward-declare each
 * other (e.g. resolved-dns-packet.h:31 `typedef struct DnsPacket DnsPacket;`)
 * so the structs below can reference each other regardless of definition
 * order. */
typedef struct DnsPacketHeader DnsPacketHeader;
typedef struct DnsPacket DnsPacket;
typedef struct DnsQuestion DnsQuestion;
typedef struct DnsAnswer DnsAnswer;
typedef struct DnsResourceRecord DnsResourceRecord;
typedef struct DnsResourceKey DnsResourceKey;
typedef struct Hashmap Hashmap; /* opaque: DnsPacket->names is a name-compression map, never
                                  * dereferenced on this bug's path (dns_packet_extract() only
                                  * touches ->names in the object/name reader, which this
                                  * harness's QDCOUNT=0 packets never reach). */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-answer.h ==== */

typedef enum DnsAnswerFlags {
        DNS_ANSWER_AUTHENTICATED = 1,  /* Item has been authenticated */
        DNS_ANSWER_CACHEABLE     = 2,  /* Item is subject to caching */
        DNS_ANSWER_SHARED_OWNER  = 4,  /* For mDNS: RRset may be owner by multiple peers */
        DNS_ANSWER_CACHE_FLUSH   = 8,  /* For mDNS: sets cache-flush bit in the rrclass of response records */
        DNS_ANSWER_GOODBYE       = 16, /* For mDNS: item is subject to disappear */
} DnsAnswerFlags;

/* ==== end verbatim ==== */

/* DnsAnswer itself stays fully opaque: real code is a resizable array of
 * DnsResourceRecord items behind a `struct DnsAnswer { ... DnsAnswerItem items[]; };`.
 * dns_packet_extract()'s answer-section handling (dns_answer_new/dns_answer_add) is
 * one of the incidental/unreachable paths this harness's corpus never exercises
 * (see the file header), so no field of DnsAnswer is ever dereferenced -- only
 * the pointer itself is passed around. */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-question.h ==== */

struct DnsQuestion {
        unsigned n_ref;
        unsigned n_keys, n_allocated;
        DnsResourceKey* keys[0];
};

/* ==== end verbatim ==== */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-rr.h ==== */

struct DnsResourceKey {
        unsigned n_ref; /* (unsigned -1) for const keys, see below */
        uint16_t class, type;
        char *_name; /* don't access directly, use dns_resource_key_name()! */
};

/* ==== end verbatim ==== */

/* Real numeric values from source_code/src/resolve/dns-type.h's DnsType enum
 * (A=0x01, sequentially incrementing ... OPT=41) and resolved-def.h's DnsClass
 * enum (IN=1, per RFC 1035); only the two constants this harness/dns_packet_extract
 * actually reference are pulled out (the full enums are ~90 RR types, all
 * irrelevant here). */
#define DNS_TYPE_A    0x01
#define DNS_TYPE_OPT  41   /* EDNS0 OPT RR type */
#define DNS_CLASS_IN  1

/* ---- REDUCED stand-in for struct DnsResourceRecord (resolved-dns-rr.h) ----
 * The real struct is a ~150-line union of every DNS RR type's fields
 * (SRV/SOA/MX/TXT/SSHFP/NSEC/...). NONE of it is relevant to CVE-2017-15908,
 * whose mechanism lives entirely in dns_packet_extract()'s QDCOUNT==0 path,
 * never in RR/EDNS0-OPT-record parsing (this harness's corpus keeps
 * ANCOUNT=NSCOUNT=ARCOUNT=0 in every crafted input, so that whole branch of
 * the verbatim dns_packet_extract() body below is provably dead code). Only
 * the two fields that dead branch's OPT handling and
 * DNS_RESOURCE_RECORD_OPT_VERSION_SUPPORTED() reference are kept, with their
 * REAL names/types, purely so the verbatim code still type-checks. */
struct DnsResourceRecord {
        DnsResourceKey *key;
        uint32_t ttl;
};

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-rr.h ==== */

static inline uint8_t DNS_RESOURCE_RECORD_OPT_VERSION_SUPPORTED(DnsResourceRecord *rr) {
        assert(rr);
        assert(rr->key->type == DNS_TYPE_OPT);

        return ((rr->ttl >> 16) & 0xFF) == 0;
}

/* ==== end verbatim ==== */

/* dns_name_is_root() (source_code/src/shared/dns-domain.c): only reached from
 * dns_resource_key_name() below and from dns_packet_extract()'s dead OPT
 * branch (see file header) -- both unreachable given this harness's
 * QDCOUNT=RRCOUNT=0 corpus. Minimal faithful stub: the real function's
 * contract is "true iff `name` is the root domain", i.e. the empty label. */
bool dns_name_is_root(const char *name) {
        return name != NULL && name[0] == '\0';
}

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-rr.c ==== */

const char* dns_resource_key_name(const DnsResourceKey *key) {
        const char *name;

        if (!key)
                return NULL;

        if (key->_name)
                name = key->_name;
        else
                name = (char*) key + sizeof(DnsResourceKey);

        if (dns_name_is_root(name))
                return ".";
        else
                return name;
}

/* ==== end verbatim ==== */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-packet.h ==== */

typedef enum DnsProtocol {
        DNS_PROTOCOL_DNS,
        DNS_PROTOCOL_MDNS,
        DNS_PROTOCOL_LLMNR,
        _DNS_PROTOCOL_MAX,
        _DNS_PROTOCOL_INVALID = -1
} DnsProtocol;

struct DnsPacketHeader {
        uint16_t id;
        be16_t flags;
        be16_t qdcount;
        be16_t ancount;
        be16_t nscount;
        be16_t arcount;
};

#define DNS_PACKET_HEADER_SIZE sizeof(DnsPacketHeader)
#define UDP_PACKET_HEADER_SIZE (sizeof(struct iphdr) + sizeof(struct udphdr))

/* The various DNS protocols deviate in how large a packet can grow,
   but the TCP transport has a 16bit size field, hence that appears to
   be the absolute maximum. */
#define DNS_PACKET_SIZE_MAX 0xFFFF

/* RFC 1035 say 512 is the maximum, for classic unicast DNS */
#define DNS_PACKET_UNICAST_SIZE_MAX 512

/* With EDNS0 we can use larger packets, default to 4096, which is what is commonly used */
#define DNS_PACKET_UNICAST_SIZE_LARGE_MAX 4096

#define DNS_PACKET_SIZE_START 512

struct DnsPacket {
        int n_ref;
        DnsProtocol protocol;
        size_t size, allocated, rindex;
        void *_data; /* don't access directly, use DNS_PACKET_DATA()! */
        Hashmap *names; /* For name compression */
        size_t opt_start, opt_size;

        /* Parsed data */
        DnsQuestion *question;
        DnsAnswer *answer;
        DnsResourceRecord *opt;

        /* Packet reception metadata */
        int ifindex;
        int family, ipproto;
        union in_addr_union sender, destination;
        uint16_t sender_port, destination_port;
        uint32_t ttl;

        /* For support of truncated packets */
        DnsPacket *more;

        bool on_stack:1;
        bool extracted:1;
        bool refuse_compression:1;
        bool canonical_form:1;
};

/* ==== end verbatim ==== */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-packet.h ====
 * (two contiguous sub-ranges of the same block; the omitted middle --
 * DNS_PACKET_RCODE/PAYLOAD_SIZE_MAX/DO/VERSION_SUPPORTED plus the LLMNR_C/T
 * aliases -- is unused by dns_packet_is_reply_for()/dns_packet_extract() and
 * would only add an unrelated MAX()-macro dependency.) */

static inline uint8_t* DNS_PACKET_DATA(DnsPacket *p) {
        if (_unlikely_(!p))
                return NULL;

        if (p->_data)
                return p->_data;

        return ((uint8_t*) p) + ALIGN(sizeof(DnsPacket));
}

#define DNS_PACKET_HEADER(p) ((DnsPacketHeader*) DNS_PACKET_DATA(p))
#define DNS_PACKET_ID(p) DNS_PACKET_HEADER(p)->id
#define DNS_PACKET_QR(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 15) & 1)
#define DNS_PACKET_OPCODE(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 11) & 15)
#define DNS_PACKET_AA(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 10) & 1)
#define DNS_PACKET_TC(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 9) & 1)
#define DNS_PACKET_RD(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 8) & 1)
#define DNS_PACKET_RA(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 7) & 1)
#define DNS_PACKET_AD(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 5) & 1)
#define DNS_PACKET_CD(p) ((be16toh(DNS_PACKET_HEADER(p)->flags) >> 4) & 1)

#define DNS_PACKET_FLAG_TC (UINT16_C(1) << 9)

#define DNS_PACKET_QDCOUNT(p) be16toh(DNS_PACKET_HEADER(p)->qdcount)
#define DNS_PACKET_ANCOUNT(p) be16toh(DNS_PACKET_HEADER(p)->ancount)
#define DNS_PACKET_NSCOUNT(p) be16toh(DNS_PACKET_HEADER(p)->nscount)
#define DNS_PACKET_ARCOUNT(p) be16toh(DNS_PACKET_HEADER(p)->arcount)

#define DNS_PACKET_MAKE_FLAGS(qr, opcode, aa, tc, rd, ra, ad, cd, rcode) \
        (((uint16_t) !!(qr) << 15) |                                    \
         ((uint16_t) ((opcode) & 15) << 11) |                           \
         ((uint16_t) !!(aa) << 10) |                /* on LLMNR: c */   \
         ((uint16_t) !!(tc) << 9) |                                     \
         ((uint16_t) !!(rd) << 8) |                 /* on LLMNR: t */   \
         ((uint16_t) !!(ra) << 7) |                                     \
         ((uint16_t) !!(ad) << 5) |                                     \
         ((uint16_t) !!(cd) << 4) |                                     \
         ((uint16_t) ((rcode) & 15)))

static inline unsigned DNS_PACKET_RRCOUNT(DnsPacket *p) {
        return
                (unsigned) DNS_PACKET_ANCOUNT(p) +
                (unsigned) DNS_PACKET_NSCOUNT(p) +
                (unsigned) DNS_PACKET_ARCOUNT(p);
}

/* ==== end verbatim ==== */

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-packet.c ==== */

void dns_packet_rewind(DnsPacket *p, size_t idx) {
        assert(p);
        assert(idx <= p->size);
        assert(idx >= DNS_PACKET_HEADER_SIZE);

        p->rindex = idx;
}



typedef struct DnsPacketRewinder {
        DnsPacket *packet;
        size_t saved_rindex;
} DnsPacketRewinder;

static void rewind_dns_packet(DnsPacketRewinder *rewinder) {
        if (rewinder->packet)
                dns_packet_rewind(rewinder->packet, rewinder->saved_rindex);
}

#define INIT_REWINDER(rewinder, p) do { rewinder.packet = p; rewinder.saved_rindex = p->rindex; } while (0)
#define CANCEL_REWINDER(rewinder) do { rewinder.packet = NULL; } while (0)

/* ==== end verbatim ==== */

/* ============================================================
 * Stubs for dns_packet_extract()'s OWN callees that only run when
 * QDCOUNT>0 (question-section parsing) or RRCOUNT>0 (answer/authority/
 * additional-section + EDNS0-OPT parsing). This harness's ENTIRE corpus
 * (25 triggering + 25 safe crafted inputs) uses a bare 12-byte DNS header
 * with QDCOUNT=ANCOUNT=NSCOUNT=ARCOUNT=0 -- see main() below -- so BOTH
 * `if (n > 0) { ... }` blocks in the verbatim dns_packet_extract() body
 * are skipped unconditionally at runtime for every input this harness
 * ever runs; every function in this block is provably unreachable here.
 * They exist purely so that code still compiles+links (C requires a
 * definition for every call site regardless of runtime reachability).
 * Each stub returns a value consistent with its real error/empty-result
 * contract, so even a mistaken invocation would fail safe (a clean
 * negative-errno return up through dns_packet_extract(), not a fault). */

DnsQuestion *dns_question_new(unsigned n) {
        (void) n;
        return NULL;
}

int dns_packet_read_key(DnsPacket *p, DnsResourceKey **ret, bool *ret_cache_flush, size_t *start) {
        (void) p; (void) ret; (void) ret_cache_flush; (void) start;
        return -EBADMSG;
}

bool dns_type_is_valid_query(uint16_t type) {
        (void) type;
        return false;
}

int dns_question_add(DnsQuestion *q, DnsResourceKey *key) {
        (void) q; (void) key;
        return -EBADMSG;
}

DnsAnswer *dns_answer_new(unsigned n) {
        (void) n;
        return NULL;
}

int dns_packet_read_rr(DnsPacket *p, DnsResourceRecord **ret, bool *ret_cache_flush, size_t *start) {
        (void) p; (void) ret; (void) ret_cache_flush; (void) start;
        return -EBADMSG;
}

bool dns_resource_key_reduce(DnsResourceKey **a, DnsResourceKey **b) {
        (void) a; (void) b;
        return false;
}

static bool opt_is_good(DnsResourceRecord *rr, bool *rfc6975) {
        (void) rr;
        if (rfc6975)
                *rfc6975 = false;
        return false;
}

DnsResourceRecord *dns_resource_record_ref(DnsResourceRecord *rr) {
        return rr;
}

DnsResourceRecord *dns_resource_record_unref(DnsResourceRecord *rr) {
        (void) rr;
        return NULL;
}

int dns_answer_add(DnsAnswer *a, DnsResourceRecord *rr, int ifindex, DnsAnswerFlags flags) {
        (void) a; (void) rr; (void) ifindex; (void) flags;
        return -EBADMSG;
}

/* Cleanup-function base callees ( _cleanup_(...) targets used inside the
 * dead branches above); DEFINE_TRIVIAL_CLEANUP_FUNC's generated wrapper
 * only calls these when the pointer is non-NULL, and every local these
 * wrap (question/answer/key/rr/previous inside dns_packet_extract())
 * stays NULL for the same reason -- provably unreachable, not just
 * unused. */
DnsQuestion *dns_question_unref(DnsQuestion *q) {
        if (q)
                free(q);
        return NULL;
}

DnsAnswer *dns_answer_unref(DnsAnswer *a) {
        (void) a;
        return NULL;
}

DnsResourceKey *dns_resource_key_unref(DnsResourceKey *key) {
        if (key)
                free(key);
        return NULL;
}

/* systemd's log_debug() (src/basic/log.h) is a printf-style diagnostic
 * macro, not on any memory-safety path; no-op stub (also never actually
 * invoked here -- same dead branches as above). */
#define log_debug(...) ((void) 0)

/* dns_resource_key_equal(): called directly from the TARGET function's own
 * verbatim body below (`return dns_resource_key_equal(p->question->keys[0], key);`),
 * reached only when p->question->n_keys == 1. This harness's SAFE inputs
 * always set n_keys != 1 (mode 2, see main()) and the TRIGGERING inputs
 * crash before this line is ever reached (mode 0) -- so, like the block
 * above, this is dead code in this harness's corpus. Mirrors the real
 * function's first line (resolved-dns-rr.c:184, pointer-identity fast path)
 * faithfully; the rest of the real function (dns_name_equal() DNS-label
 * comparison, class/type compare) is elided as incidental to this bug. */
int dns_resource_key_equal(const DnsResourceKey *a, const DnsResourceKey *b) {
        return a == b;
}

/* ==== VERBATIM from source_code/src/basic/macro.h ==== */

#define DEFINE_TRIVIAL_CLEANUP_FUNC(type, func)                 \
        static inline void func##p(type *p) {                   \
                if (*p)                                         \
                        func(*p);                               \
        }                                                       \
        struct __useless_struct_to_allow_trailing_semicolon__

/* ==== end verbatim ==== */

DEFINE_TRIVIAL_CLEANUP_FUNC(DnsQuestion*, dns_question_unref);
DEFINE_TRIVIAL_CLEANUP_FUNC(DnsAnswer*, dns_answer_unref);
DEFINE_TRIVIAL_CLEANUP_FUNC(DnsResourceKey*, dns_resource_key_unref);
DEFINE_TRIVIAL_CLEANUP_FUNC(DnsResourceRecord*, dns_resource_record_unref);

/* ==== VERBATIM from source_code/src/resolve/resolved-dns-packet.c ====
 * THE one callee directly on the crash path (dns_packet_is_reply_for()'s
 * only non-macro call before the crashing dereference). This is the exact
 * upstream function, unmodified -- the CVE-2017-15908 mechanism (accepting
 * a QDCOUNT==0 "reply" and leaving p->question NULL) is its real, unedited
 * control flow. */

int dns_packet_extract(DnsPacket *p) {
        _cleanup_(dns_question_unrefp) DnsQuestion *question = NULL;
        _cleanup_(dns_answer_unrefp) DnsAnswer *answer = NULL;
        _cleanup_(rewind_dns_packet) DnsPacketRewinder rewinder = {};
        unsigned n, i;
        int r;

        if (p->extracted)
                return 0;

        INIT_REWINDER(rewinder, p);
        dns_packet_rewind(p, DNS_PACKET_HEADER_SIZE);

        n = DNS_PACKET_QDCOUNT(p);
        if (n > 0) {
                question = dns_question_new(n);
                if (!question)
                        return -ENOMEM;

                for (i = 0; i < n; i++) {
                        _cleanup_(dns_resource_key_unrefp) DnsResourceKey *key = NULL;
                        bool cache_flush;

                        r = dns_packet_read_key(p, &key, &cache_flush, NULL);
                        if (r < 0)
                                return r;

                        if (cache_flush)
                                return -EBADMSG;

                        if (!dns_type_is_valid_query(key->type))
                                return -EBADMSG;

                        r = dns_question_add(question, key);
                        if (r < 0)
                                return r;
                }
        }

        n = DNS_PACKET_RRCOUNT(p);
        if (n > 0) {
                _cleanup_(dns_resource_record_unrefp) DnsResourceRecord *previous = NULL;
                bool bad_opt = false;

                answer = dns_answer_new(n);
                if (!answer)
                        return -ENOMEM;

                for (i = 0; i < n; i++) {
                        _cleanup_(dns_resource_record_unrefp) DnsResourceRecord *rr = NULL;
                        bool cache_flush = false;

                        r = dns_packet_read_rr(p, &rr, &cache_flush, NULL);
                        if (r < 0)
                                return r;

                        /* Try to reduce memory usage a bit */
                        if (previous)
                                dns_resource_key_reduce(&rr->key, &previous->key);

                        if (rr->key->type == DNS_TYPE_OPT) {
                                bool has_rfc6975;

                                if (p->opt || bad_opt) {
                                        /* Multiple OPT RRs? if so, let's ignore all, because there's something wrong
                                         * with the server, and if one is valid we wouldn't know which one. */
                                        log_debug("Multiple OPT RRs detected, ignoring all.");
                                        bad_opt = true;
                                        continue;
                                }

                                if (!dns_name_is_root(dns_resource_key_name(rr->key))) {
                                        /* If the OPT RR is not owned by the root domain, then it is bad, let's ignore
                                         * it. */
                                        log_debug("OPT RR is not owned by root domain, ignoring.");
                                        bad_opt = true;
                                        continue;
                                }

                                if (i < DNS_PACKET_ANCOUNT(p) + DNS_PACKET_NSCOUNT(p)) {
                                        /* OPT RR is in the wrong section? Some Belkin routers do this. This is a hint
                                         * the EDNS implementation is borked, like the Belkin one is, hence ignore
                                         * it. */
                                        log_debug("OPT RR in wrong section, ignoring.");
                                        bad_opt = true;
                                        continue;
                                }

                                if (!opt_is_good(rr, &has_rfc6975)) {
                                        log_debug("Malformed OPT RR, ignoring.");
                                        bad_opt = true;
                                        continue;
                                }

                                if (DNS_PACKET_QR(p)) {
                                        /* Additional checks for responses */

                                        if (!DNS_RESOURCE_RECORD_OPT_VERSION_SUPPORTED(rr)) {
                                                /* If this is a reply and we don't know the EDNS version then something
                                                 * is weird... */
                                                log_debug("EDNS version newer that our request, bad server.");
                                                return -EBADMSG;
                                        }

                                        if (has_rfc6975) {
                                                /* If the OPT RR contains RFC6975 algorithm data, then this is indication that
                                                 * the server just copied the OPT it got from us (which contained that data)
                                                 * back into the reply. If so, then it doesn't properly support EDNS, as
                                                 * RFC6975 makes it very clear that the algorithm data should only be contained
                                                 * in questions, never in replies. Crappy Belkin routers copy the OPT data for
                                                 * example, hence let's detect this so that we downgrade early. */
                                                log_debug("OPT RR contained RFC6975 data, ignoring.");
                                                bad_opt = true;
                                                continue;
                                        }
                                }

                                p->opt = dns_resource_record_ref(rr);
                        } else {

                                /* According to RFC 4795, section 2.9. only the RRs from the Answer section shall be
                                 * cached. Hence mark only those RRs as cacheable by default, but not the ones from the
                                 * Additional or Authority sections. */

                                r = dns_answer_add(answer, rr, p->ifindex,
                                                   (i < DNS_PACKET_ANCOUNT(p) ? DNS_ANSWER_CACHEABLE : 0) |
                                                   (p->protocol == DNS_PROTOCOL_MDNS && !cache_flush ? DNS_ANSWER_SHARED_OWNER : 0));
                                if (r < 0)
                                        return r;
                        }

                        /* Remember this RR, so that we potentically can merge it's ->key object with the next RR. Note
                         * that we only do this if we actually decided to keep the RR around. */
                        dns_resource_record_unref(previous);
                        previous = dns_resource_record_ref(rr);
                }

                if (bad_opt)
                        p->opt = dns_resource_record_unref(p->opt);
        }

        p->question = question;
        question = NULL;

        p->answer = answer;
        answer = NULL;

        p->extracted = true;

        /* no CANCEL, always rewind */
        return 0;
}

/* ==== end verbatim ==== */

/* ==== VERBATIM from data_cve/cve_a9ab59c3/target/original_function.c ==== */

int dns_packet_is_reply_for(DnsPacket *p, const DnsResourceKey *key) {
        int r;

        assert(p);
        assert(key);

        /* Checks if the specified packet is a reply for the specified
         * key and the specified key is the only one in the question
         * section. */

        if (DNS_PACKET_QR(p) != 1)
                return 0;

        /* Let's unpack the packet, if that hasn't happened yet. */
        r = dns_packet_extract(p);
        if (r < 0)
                return r;

        if (p->question->n_keys != 1)
                return 0;

        return dns_resource_key_equal(p->question->keys[0], key);
}


/* ==== end verbatim ==== */

/* ============================================================
 * main() -- byte-driven harness controller.
 *
 * argv[1] is read into a HEAP buffer (ASAN-guarded). byte[0] selects one
 * of three real, distinct code paths through dns_packet_is_reply_for():
 *
 *   mode 0 (TRIGGERING) - builds a bare 12-byte DNS header with QR=1 (a
 *     "reply") and QDCOUNT=ANCOUNT=NSCOUNT=ARCOUNT=0, on a FRESH
 *     (never-extracted) packet. dns_packet_is_reply_for() calls the real,
 *     verbatim dns_packet_extract(), which accepts the packet (returns 0)
 *     but -- because QDCOUNT is 0 -- never allocates p->question, leaving
 *     it NULL. The very next line unconditionally reads
 *     p->question->n_keys: NULL pointer READ (CVE-2017-15908 / CWE-476).
 *
 *   mode 1 (SAFE) - same 12-byte header shape, but QR=0 ("this is a
 *     query, not a reply"): dns_packet_is_reply_for()'s OWN first check
 *     (`if (DNS_PACKET_QR(p) != 1) return 0;`) returns immediately.
 *     dns_packet_extract() is never even called.
 *
 *   mode 2 (SAFE) - simulates a packet whose question section was already
 *     unpacked earlier in the resolver pipeline (a real, common state --
 *     dns_packet_is_reply_for() is typically called on packets
 *     dns_packet_extract() has already visited once): the harness
 *     pre-sets p->extracted=true and a real, heap-allocated DnsQuestion
 *     with n_keys != 1 (picked from byte[4]). dns_packet_extract() takes
 *     its OWN real early-return (`if (p->extracted) return 0;`, the first
 *     line of the verbatim function above) without touching p->question,
 *     and dns_packet_is_reply_for()'s `p->question->n_keys != 1` check
 *     then safely returns 0. This is the direct non-buggy counterpart of
 *     the mode-0 crash: same QR=1 "reply" packet, but p->question is a
 *     valid, non-NULL object.
 *
 * byte[1..2] = DNS ID (big-endian, cosmetic -- varies the 25 triggering
 * inputs so they are not byte-identical files). byte[3] = extra low-order
 * header flag bits (opcode/AA/TC/RD/RA/AD/CD, cosmetic -- QR itself is
 * forced by mode, not by this byte). byte[4] (mode 2 only) picks n_keys
 * in {0,2,3} (never 1, by construction). Missing bytes default to 0, so
 * a short/empty file is itself a valid (mode-0, all-zero) input.
 * ============================================================ */

static unsigned char at(const unsigned char *b, size_t n, size_t i) {
        return (i < n) ? b[i] : 0;
}

int main(int argc, char **argv) {
        if (argc < 2) {
                fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
                return 1;
        }

        FILE *f = fopen(argv[1], "rb");
        if (!f) {
                perror("fopen");
                return 1;
        }
        fseek(f, 0, SEEK_END);
        long fsz = ftell(f);
        if (fsz < 0)
                fsz = 0;
        fseek(f, 0, SEEK_SET);

        /* Attacker-controlled bytes MUST live on the heap so ASAN redzones
         * bound them on both sides. */
        unsigned char *raw = NULL;
        size_t n = 0;
        if (fsz > 0) {
                raw = (unsigned char *) malloc((size_t) fsz);
                if (!raw) {
                        fclose(f);
                        return 1;
                }
                n = fread(raw, 1, (size_t) fsz, f);
        }
        fclose(f);

        unsigned char mode     = at(raw, n, 0);
        unsigned char id_hi    = at(raw, n, 1);
        unsigned char id_lo    = at(raw, n, 2);
        unsigned char flagbits = at(raw, n, 3);
        unsigned char nkbyte   = at(raw, n, 4);

        if (mode > 2)
                mode = (unsigned char) (mode % 3); /* keep every byte value meaningful */

        /* The 12-byte DNS wire header this harness constructs for
         * dns_packet_is_reply_for()/dns_packet_extract() to parse --
         * exactly DNS_PACKET_HEADER_SIZE, matching how a real received
         * datagram's fixed header is laid out (id, flags, qdcount,
         * ancount, nscount, arcount; RFC 1035 4.1.1). This buffer becomes
         * the DnsPacket's ->_data, i.e. the attacker-controlled bytes
         * DNS_PACKET_QR()/DNS_PACKET_QDCOUNT()/DNS_PACKET_RRCOUNT() read
         * -- heap-allocated so ASAN guards it. */
        const size_t PKT_LEN = 12; /* == DNS_PACKET_HEADER_SIZE */
        uint8_t *pktbuf = (uint8_t *) malloc(PKT_LEN);
        if (!pktbuf) {
                free(raw);
                return 1;
        }
        memset(pktbuf, 0, PKT_LEN);
        pktbuf[0] = id_hi;
        pktbuf[1] = id_lo;
        {
                unsigned char qr = (mode == 1) ? 0 : 1;
                pktbuf[2] = (uint8_t) ((qr << 7) | (flagbits & 0x7F));
        }
        pktbuf[3] = 0;
        /* bytes 4..11 (qdcount, ancount, nscount, arcount) stay 0 -- the
         * exact CVE-2017-15908 trigger condition, for every mode. */

        DnsPacket *pkt = (DnsPacket *) calloc(1, sizeof(DnsPacket));
        if (!pkt) {
                free(pktbuf);
                free(raw);
                return 1;
        }
        /* Mirrors real dns_packet_new(): `p->size = p->rindex = DNS_PACKET_HEADER_SIZE;` --
         * our packet is exactly a bare header, so size == rindex == 12. Everything
         * else (question/answer/opt/names/more, extracted/on_stack/... bitfields)
         * is already zeroed by calloc, matching a freshly received packet. */
        pkt->n_ref = 1;
        pkt->protocol = DNS_PROTOCOL_DNS;
        pkt->_data = pktbuf;
        pkt->size = PKT_LEN;
        pkt->allocated = PKT_LEN;
        pkt->rindex = PKT_LEN;

        /* The `key` argument: a real, heap-allocated DnsResourceKey, exactly
         * as a resolver query object owns one. Its value is inert for THIS
         * harness's corpus (dns_resource_key_equal() is dead code here -- see
         * its definition above), but it is a fully real, valid object. */
        DnsResourceKey *qkey = (DnsResourceKey *) calloc(1, sizeof(DnsResourceKey));
        if (!qkey) {
                free(pkt);
                free(pktbuf);
                free(raw);
                return 1;
        }
        qkey->n_ref = (unsigned) -1; /* DNS_RESOURCE_KEY_CONST-style const key */
        qkey->class = DNS_CLASS_IN;
        qkey->type = DNS_TYPE_A;
        qkey->_name = NULL;

        DnsQuestion *preset_q = NULL;
        if (mode == 2) {
                unsigned nk = (unsigned) (nkbyte % 4); /* 0..3 */
                if (nk == 1)
                        nk = 2; /* never hit the n_keys==1 / dns_resource_key_equal() branch */
                preset_q = (DnsQuestion *) malloc(sizeof(DnsQuestion) + (size_t) nk * sizeof(DnsResourceKey *));
                if (!preset_q) {
                        free(qkey);
                        free(pkt);
                        free(pktbuf);
                        free(raw);
                        return 1;
                }
                preset_q->n_ref = 1;
                preset_q->n_keys = nk;
                preset_q->n_allocated = nk;
                for (unsigned i = 0; i < nk; i++)
                        preset_q->keys[i] = NULL; /* never dereferenced: n_keys != 1 */

                pkt->extracted = true;
                pkt->question = preset_q;
        }

        int r = dns_packet_is_reply_for(pkt, qkey);
        fprintf(stderr, "dns_packet_is_reply_for -> %d (mode=%u)\n", r, (unsigned) mode);

        free(preset_q);
        free(qkey);
        free(pkt);
        free(pktbuf);
        free(raw);
        return 0;
}

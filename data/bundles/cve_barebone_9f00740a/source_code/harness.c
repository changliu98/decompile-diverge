/* cve_barebone direct-call harness for CVE-2019-15026 (memcached)
 * Target: get_conn_text  (memcached.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * See the generator script's module docstring (scripts/gen_dc_cve_9f00740a.py) for the full
 * mechanism. Summary: the AF_UNIX branch does
 *     strncpy(addr_text, ((struct sockaddr_un *)sock_addr)->sun_path, sizeof(addr_text) - 1);
 * using the DESTINATION buffer's size (MAXPATHLEN-1 == 4095) as the read bound instead of the
 * SOURCE (sun_path, 108 bytes) -- so if sun_path has no NUL terminator within those 108 bytes,
 * the copy's null-scan reads past whatever buffer sun_path actually lives in.
 *
 * TRIGGER: heap-allocate sock_addr as EXACTLY sizeof(struct sockaddr_un) bytes (2-byte
 *          sun_family + 108-byte sun_path, ending exactly at the allocation/redzone boundary)
 *          and fill all 108 sun_path bytes with NO 0x00 -> the strncpy read walks into the
 *          ASan redzone right after the allocation.
 * SAFE:    same AF_UNIX construction but sun_path contains a NUL within its 108 bytes (strncpy
 *          stops there, never touching memory past the allocation) -- or af == AF_INET /
 *          AF_INET6 (a real, unrelated, non-buggy branch; also exercises `conn.transport` /
 *          IS_UDP() for coverage).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- minimal libc/system headers for the REAL system types the function needs (these are
 * the exact headers memcached.c itself includes for them -- not project types). ---- */
#include <sys/param.h>    /* MAXPATHLEN */
#include <sys/socket.h>   /* struct sockaddr, AF_INET/AF_INET6/AF_UNIX */
#include <netinet/in.h>   /* struct sockaddr_in, struct sockaddr_in6, ntohs/htons/htonl */
#include <arpa/inet.h>    /* inet_ntop */
#include <sys/un.h>       /* struct sockaddr_un */

/* ---- enum network_transport: VERBATIM (source_code/memcached.h) ---- */
enum network_transport {
    local_transport, /* Unix sockets*/
    tcp_transport,
    udp_transport
};

/* ---- IS_UDP macro: VERBATIM (source_code/memcached.h) ---- */
#define IS_UDP(x) (x == udp_transport)

/* ---- struct conn / conn: minimal faithful stand-in. get_conn_text only ever reads
 * c->transport (via IS_UDP()), and only on the AF_INET/AF_INET6 branches -- the AF_UNIX
 * branch this CVE lives in never touches `c` at all. Real `struct conn` (memcached.h) carries
 * 60+ fields (libevent state, TLS/SSL, per-command scratch buffers, ...); only the one field
 * this function's body actually reads is kept, at its REAL name+type (memcached.h:
 * "enum network_transport transport;"). ---- */
typedef struct conn {
    enum network_transport transport;
} conn;

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_9f00740a/target/original_function.c */
/* ======================================================================================== */
static inline void get_conn_text(const conn *c, const int af,
                char* addr, struct sockaddr *sock_addr) {
    char addr_text[MAXPATHLEN];
    addr_text[0] = '\0';
    const char *protoname = "?";
    unsigned short port = 0;

    switch (af) {
        case AF_INET:
            (void) inet_ntop(af,
                    &((struct sockaddr_in *)sock_addr)->sin_addr,
                    addr_text,
                    sizeof(addr_text) - 1);
            port = ntohs(((struct sockaddr_in *)sock_addr)->sin_port);
            protoname = IS_UDP(c->transport) ? "udp" : "tcp";
            break;

        case AF_INET6:
            addr_text[0] = '[';
            addr_text[1] = '\0';
            if (inet_ntop(af,
                    &((struct sockaddr_in6 *)sock_addr)->sin6_addr,
                    addr_text + 1,
                    sizeof(addr_text) - 2)) {
                strcat(addr_text, "]");
            }
            port = ntohs(((struct sockaddr_in6 *)sock_addr)->sin6_port);
            protoname = IS_UDP(c->transport) ? "udp6" : "tcp6";
            break;

        case AF_UNIX:
            strncpy(addr_text,
                    ((struct sockaddr_un *)sock_addr)->sun_path,
                    sizeof(addr_text) - 1);
            addr_text[sizeof(addr_text)-1] = '\0';
            protoname = "unix";
            break;
    }

    if (strlen(addr_text) < 2) {
        /* Most likely this is a connected UNIX-domain client which
         * has no peer socket address, but there's no portable way
         * to tell for sure.
         */
        sprintf(addr_text, "<AF %d>", af);
    }

    if (port) {
        sprintf(addr, "%s:%s:%u", protoname, addr_text, port);
    } else {
        sprintf(addr, "%s:%s", protoname, addr_text);
    }
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASan-guarded). Every argument get_conn_text is
 * called with is derived from that buffer's own bytes -- no hardcoded trigger constant:
 *
 *   byte 0 ("mode"):  family_sel    = mode % 3        (0=AF_UNIX 1=AF_INET 2=AF_INET6)
 *                     transport_sel = (mode / 3) % 3   (0=local 1=tcp 2=udp -- conn.transport,
 *                                                        exercised on the INET/INET6 branches)
 *   remaining bytes ("body"): fills the address structure's attacker-controlled fields.
 *
 * AF_UNIX: sock_addr is a HEAP buffer of EXACTLY sizeof(struct sockaddr_un) -- sun_path is the
 * struct's last field, so it ends exactly at the allocation boundary. sun_path[i] = body's
 * bytes cycled (or 'A' if the file supplied no body). If NONE of those 108 bytes is 0x00, the
 * source has no in-bounds NUL terminator -> triggers get_conn_text's own OOB read. If body
 * contains a 0x00 that lands within [0,108) once cycled, strncpy stops there -> safe.
 * AF_INET / AF_INET6: sock_addr is a HEAP sockaddr_in / sockaddr_in6, port + address bytes
 * from the body -- both real, unrelated-to-the-bug branches (always safe).
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
    unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASan-guarded */
    if (!ibuf) { fclose(fp); return 64; }
    size_t irn = n ? fread(ibuf, 1, n, fp) : 0;
    fclose(fp);

    unsigned char mode = irn > 0 ? ibuf[0] : 0;
    unsigned char *body = irn > 1 ? ibuf + 1 : NULL;
    size_t bodyn = irn > 1 ? irn - 1 : 0;

    int family_sel    = mode % 3;
    int transport_sel = (mode / 3) % 3;

    conn c;
    c.transport = (transport_sel == 0) ? local_transport
                : (transport_sel == 1) ? tcp_transport
                                        : udp_transport;

    char *addr = (char *)malloc(MAXPATHLEN + 64);   /* real caller sizes it MAXPATHLEN+extras_len */
    if (!addr) { free(ibuf); return 64; }
    memset(addr, 0, MAXPATHLEN + 64);

    /* volatile function pointer: forbid the compiler from inlining get_conn_text (it's
     * `static inline`) away so its frame stays visible in the ASan backtrace. Touches nothing
     * of the target function's own bytes. */
    void (*volatile vb_get_conn_text)(const conn *, const int, char *, struct sockaddr *) = get_conn_text;

    if (family_sel == 0) {
        /* ---- AF_UNIX: the buggy branch. sock_addr sized EXACTLY sizeof(struct sockaddr_un)
         * so sun_path's last byte is the allocation's last byte -- the ASan redzone starts
         * immediately after. ---- */
        struct sockaddr_un *su = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
        if (!su) { free(addr); free(ibuf); return 64; }
        su->sun_family = AF_UNIX;
        for (size_t i = 0; i < sizeof(su->sun_path); i++) {
            su->sun_path[i] = bodyn ? (char)body[i % bodyn] : (char)'A';
        }
        vb_get_conn_text(&c, AF_UNIX, addr, (struct sockaddr *)su);
        /* only reached on a SAFE run (sun_path had an in-bounds NUL) */
        free(su);
    } else if (family_sel == 1) {
        /* ---- AF_INET: real, unrelated branch (also exercises conn.transport / IS_UDP()). */
        struct sockaddr_in *si = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
        if (!si) { free(addr); free(ibuf); return 64; }
        memset(si, 0, sizeof(*si));
        si->sin_family = AF_INET;
        unsigned short port = 0;
        if (bodyn >= 2) port = (unsigned short)((body[0] << 8) | body[1]);
        si->sin_port = htons(port);
        uint32_t a = 0;
        for (size_t i = 0; i < 4; i++) {
            unsigned char bb = (bodyn > 2) ? body[2 + (i % (bodyn - 2))] : 0;
            a = (a << 8) | bb;
        }
        si->sin_addr.s_addr = htonl(a);
        vb_get_conn_text(&c, AF_INET, addr, (struct sockaddr *)si);
        free(si);
    } else {
        /* ---- AF_INET6: real, unrelated branch. */
        struct sockaddr_in6 *si6 = (struct sockaddr_in6 *)malloc(sizeof(struct sockaddr_in6));
        if (!si6) { free(addr); free(ibuf); return 64; }
        memset(si6, 0, sizeof(*si6));
        si6->sin6_family = AF_INET6;
        unsigned short port = 0;
        if (bodyn >= 2) port = (unsigned short)((body[0] << 8) | body[1]);
        si6->sin6_port = htons(port);
        for (size_t i = 0; i < 16; i++) {
            si6->sin6_addr.s6_addr[i] = (bodyn > 2) ? body[2 + (i % (bodyn - 2))] : 0;
        }
        vb_get_conn_text(&c, AF_INET6, addr, (struct sockaddr *)si6);
        free(si6);
    }

    free(addr);
    free(ibuf);
    return 0;
}

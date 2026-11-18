/*
 * Direct-call ASAN harness for cve_7c5721b3 (sniproxy new_address stack buffer overflow).
 *
 * Vulnerability: sniproxy src/address.c new_address(), "[IPv6 address]" branch. When
 * hostname_or_ip starts with '[' and contains a later ']', the code computes
 *     len = (size_t)(port - hostname_or_ip - 1);
 * (the length of the text between the brackets) and does
 *     strncpy(ip_buf, hostname_or_ip + 1, len);
 *     ip_buf[len] = '\0';
 * WITHOUT ever checking len against sizeof(ip_buf) (== ADDRESS_BUFFER_SIZE == 262). If the
 * bracketed text is longer than 262 bytes this overflows the stack array ip_buf, which is a
 * local of new_address() itself. The upstream fix (commit f8d9a433) added
 *     if (len >= INET6_ADDRSTRLEN) return NULL;
 * right before the strncpy -- confirming the missing bounds check is the trigger condition.
 * CWE-787 (stack-based buffer overflow, WRITE), the fix's own commit message: "Fix buffer
 * overflow in address module".
 *
 * This harness reproduces the bug by calling new_address() directly and in isolation, with
 * the real struct Address layout plus the real (verbatim) callees new_address() itself
 * transitively needs: new_address_sa, address_sa, address_port, address_set_port, is_numeric,
 * valid_hostname. Everything else the function uses is libc (memset/strncmp/strrchr/strchr/
 * strcmp/inet_pton/atoi/tolower/malloc/memcpy/offsetof), resolved with -lm alone.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>      /* tolower */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  /* inet_pton */
#include <sys/un.h>
#include <assert.h>
#include <inttypes.h>

/* ---------------------------------------------------------------------
 * From src/address.h (real names, verbatim)
 * --------------------------------------------------------------------- */

#define ADDRESS_BUFFER_SIZE 262

struct Address;

struct Address *new_address(const char *);
struct Address *new_address_sa(const struct sockaddr *, socklen_t);
const struct sockaddr *address_sa(const struct Address *);
uint16_t address_port(const struct Address *);
void address_set_port(struct Address *, uint16_t);
int is_numeric(const char *);

/* ---------------------------------------------------------------------
 * From src/address.c (real names, verbatim)
 * --------------------------------------------------------------------- */

struct Address {
    enum {
        HOSTNAME,
        SOCKADDR,
        WILDCARD,
    } type;

    size_t len;     /* length of data */
    uint16_t port;  /* for hostname and wildcard */
    char data[];
};


static const char valid_label_bytes[] =
"-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";


static int valid_hostname(const char *);


/* ---- verbatim callees new_address() needs (copied byte-for-byte from src/address.c) ---- */

struct Address *
new_address_sa(const struct sockaddr *sa, socklen_t sa_len) {
    struct Address *addr = malloc(offsetof(struct Address, data) + sa_len);
    if (addr != NULL) {
        addr->type = SOCKADDR;
        addr->len = sa_len;
        memcpy(addr->data, sa, sa_len);
        addr->port = address_port(addr);
    }

    return addr;
}

const struct sockaddr *
address_sa(const struct Address *addr) {
    if (addr->type != SOCKADDR)
        return NULL;

    return (struct sockaddr *)addr->data;
}

uint16_t
address_port(const struct Address *addr) {
    switch (addr->type) {
        case HOSTNAME:
            return addr->port;
        case SOCKADDR:
            switch (address_sa(addr)->sa_family) {
                case AF_INET:
                    return ntohs(((struct sockaddr_in *)addr->data)
                            ->sin_port);
                case AF_INET6:
                    return ntohs(((struct sockaddr_in6 *)addr->data)
                            ->sin6_port);
                case AF_UNIX:
                case AF_UNSPEC:
                    return 0;
                default:
                    assert(0);
                    return 0;
            }
        case WILDCARD:
            return addr->port;
        default:
            /* invalid Address type */
            assert(0);
            return 0;
    }
}

void
address_set_port(struct Address *addr, uint16_t port) {
    switch (addr->type) {
        case SOCKADDR:
            switch (address_sa(addr)->sa_family) {
                case AF_INET:
                    (((struct sockaddr_in *)addr->data) ->sin_port) =
                        htons(port);
                    break;
                case AF_INET6:
                    (((struct sockaddr_in6 *)addr->data) ->sin6_port) =
                        htons(port);
                    break;
                case AF_UNIX:
                case AF_UNSPEC:
                    /* no op */
                    break;
                default:
                    assert(0);
            }
            /* fall through */
        case HOSTNAME:
        case WILDCARD:
            addr->port = port;
            break;
        default:
            /* invalid Address type */
            assert(0);
    }
}

int
is_numeric(const char *s) {
    char *p;

    if (s == NULL || *s == '\0')
        return 0;

    int n = strtod(s, &p);
    (void)n; /* unused */

    return *p == '\0'; /* entire string was numeric */
}

static int
valid_hostname(const char *hostname) {
    if (hostname == NULL)
        return 0;

    size_t hostname_len = strlen(hostname);
    if (hostname_len < 1 || hostname_len > 255)
        return 0;

    if (hostname[0] == '.')
        return 0;

    const char *hostname_end = hostname + hostname_len;
    for (const char *label = hostname; label < hostname_end;) {
        size_t label_len = (size_t)(hostname_end - label);
        char *next_dot = strchr(label, '.');
        if (next_dot != NULL)
            label_len = (size_t)(next_dot - label);
        assert(label + label_len <= hostname_end);

        if (label_len > 63 || label_len < 1)
            return 0;

        if (label[0] == '-' || label[label_len - 1] == '-')
            return 0;

        if (strspn(label, valid_label_bytes) < label_len)
            return 0;

        label += label_len + 1;
    }

    return 1;
}

/* ---------------------------------------------------------------------
 * new_address() -- pasted BYTE-FOR-BYTE from
 * data_cve/cve_7c5721b3/target/original_function.c
 * --------------------------------------------------------------------- */

struct Address *
new_address(const char *hostname_or_ip) {
    union {
        struct sockaddr a;
        struct sockaddr_in in;
        struct sockaddr_in6 in6;
        struct sockaddr_un un;
        struct sockaddr_storage s;
    } s;
    char ip_buf[ADDRESS_BUFFER_SIZE];
    char *port;
    size_t len;

    if (hostname_or_ip == NULL)
        return NULL;

    /* IPv6 address */
    /* we need to test for raw IPv6 address for IPv4 port combinations since a
     * colon would give false positives
     */
    memset(&s, 0, sizeof(s));
    if (inet_pton(AF_INET6, hostname_or_ip,
                &s.in6.sin6_addr) == 1) {
        s.in6.sin6_family = AF_INET6;

        return new_address_sa(&s.a, sizeof(s.in6));
    }

    /* Unix socket */
    memset(&s, 0, sizeof(s));
    if (strncmp("unix:", hostname_or_ip, 5) == 0) {
        if (strlen(hostname_or_ip) >=
                sizeof(s.un.sun_path))
            return NULL;

        /* XXX: only supporting pathname unix sockets */
        s.un.sun_family = AF_UNIX;
        strncpy(s.un.sun_path,
                hostname_or_ip + 5,
                sizeof(s.un.sun_path) - 1);

        return new_address_sa(&s.a, offsetof(struct sockaddr_un, sun_path) +
                              strlen(s.un.sun_path) + 1);
    }

    /* Trailing port */
    if ((port = strrchr(hostname_or_ip, ':')) != NULL &&
            is_numeric(port + 1)) {
        len = (size_t)(port - hostname_or_ip);
        int port_num = atoi(port + 1);

        if (len < sizeof(ip_buf) && port_num >= 0 && port_num <= 65535) {
            strncpy(ip_buf, hostname_or_ip, len);
            ip_buf[len] = '\0';

            struct Address *addr = new_address(ip_buf);
            if (addr != NULL)
                address_set_port(addr, (uint16_t) port_num);

            return addr;
        }
    }

    /* Wildcard */
    if (strcmp("*", hostname_or_ip) == 0) {
        struct Address *addr = malloc(sizeof(struct Address));
        if (addr != NULL) {
            addr->type = WILDCARD;
            addr->len = 0;
            address_set_port(addr, 0);
        }
        return addr;
    }

    /* IPv4 address */
    memset(&s, 0, sizeof(s));
    if (inet_pton(AF_INET, hostname_or_ip,
                  &s.in.sin_addr) == 1) {
        s.in.sin_family = AF_INET;

        return new_address_sa(&s.a, sizeof(s.in));
    }

    /* [IPv6 address] */
    memset(&s, 0, sizeof(s));
    if (hostname_or_ip[0] == '[' &&
            (port = strchr(hostname_or_ip, ']')) != NULL) {
        len = (size_t)(port - hostname_or_ip - 1);

        /* inet_pton() will not parse the IP correctly unless it is in a
         * separate string.
         */
        strncpy(ip_buf, hostname_or_ip + 1, len);
        ip_buf[len] = '\0';

        if (inet_pton(AF_INET6, ip_buf,
                      &s.in6.sin6_addr) == 1) {
            s.in6.sin6_family = AF_INET6;

            return new_address_sa(&s.a, sizeof(s.in6));
        }
    }

    /* hostname */
    if (valid_hostname(hostname_or_ip)) {
        len = strlen(hostname_or_ip);
        struct Address *addr = malloc(
                offsetof(struct Address, data) + len + 1);
        if (addr != NULL) {
            addr->type = HOSTNAME;
            addr->port = 0;
            addr->len = len;
            memcpy(addr->data, hostname_or_ip, len);
            addr->data[addr->len] = '\0';

            /* Store address in lower case */
            for (char *c = addr->data; *c != '\0'; c++)
                *c = tolower(*c);
        }

        return addr;
    }

    return NULL;
}

/* ---------------------------------------------------------------------
 * Driver: read argv[1] into a HEAP buffer, call new_address() directly.
 * --------------------------------------------------------------------- */

int
main(int argc, char **argv) {
    if (argc < 2)
        return 0;

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
        return 0;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    char *buf = malloc((size_t)sz + 1);
    if (buf == NULL) { fclose(f); return 0; }

    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[rd] = '\0';

    /* strip a single trailing newline (CRLF or LF) for convenience */
    if (rd > 0 && buf[rd - 1] == '\n') {
        buf[--rd] = '\0';
        if (rd > 0 && buf[rd - 1] == '\r')
            buf[--rd] = '\0';
    }

    struct Address *addr = new_address(buf);
    if (addr != NULL)
        free(addr);
    free(buf);

    return 0;
}

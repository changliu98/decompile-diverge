/*
 * Direct-call harness for CVE-2025-44951 (open5gs PFCP subnet DNN overflow).
 *
 * Target: ogs_pfcp_subnet_add()  (lib/pfcp/context.c)
 * Bug:    strcpy(subnet->dnn, dnn) has no bounds check. subnet->dnn is a
 *         fixed OGS_MAX_DNN_LEN+1 = 101 byte buffer embedded inside the
 *         heap-allocated ogs_pfcp_subnet_t struct. A dnn string longer than
 *         100 bytes overflows past the struct's heap allocation.
 * CWE:    CWE-787 (out-of-bounds WRITE), ASAN class heap-buffer-overflow.
 *
 * main() reads the whole input file into a HEAP buffer (malloc) and passes
 * it as the `dnn` argument, so the attacker-controlled bytes -- and the
 * overflow write into `subnet->dnn` -- live entirely on the ASAN-visible
 * heap. ogs_pfcp_subnet_add() is called exactly once, directly, with no
 * dependency on the rest of open5gs (config parser, PFCP protocol stack,
 * etc.).
 *
 * Type/macro names below are taken from the real open5gs headers:
 *   lib/proto/types.h       OGS_MAX_DNN_LEN            = 100
 *   lib/pfcp/context.h      OGS_MAX_NUM_OF_SUBNET      = 16
 *                           OGS_MAX_NUM_OF_SUBNET_RANGE= 16
 *                           ogs_pfcp_subnet_s / ogs_pfcp_dev_s (field layout)
 *   lib/core/ogs-macros.h   OGS_MAX_IFNAME_LEN         = 32
 *   lib/core/ogs-list.h     ogs_list_s / ogs_lnode_t / ogs_list_add()
 *   lib/core/ogs-sockaddr.h ogs_ipsubnet_s / ogs_ipsubnet_t
 * The pool allocator (ogs_pool_alloc against a fixed-size slab pool) and
 * the config-parser/PFCP-stack callers are replaced with a minimal
 * heap-backed stand-in (pool_alloc/pool_init, ogs_pfcp_dev_find_by_ifname,
 * ogs_pfcp_dev_add, ogs_ipsubnet, ogs_list_add) so the target function runs
 * unmodified with no other project code.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

/* === Type/macro definitions (real names from open5gs headers) === */

#define OGS_MAX_DNN_LEN            100   /* lib/proto/types.h */
#define OGS_MAX_IFNAME_LEN         32    /* lib/core/ogs-macros.h */
#define OGS_MAX_NUM_OF_SUBNET      16    /* lib/pfcp/context.h */
#define OGS_MAX_NUM_OF_SUBNET_RANGE 16   /* lib/pfcp/context.h */
#define OGS_OK  0
#define AF_UNSPEC 0

/* lib/core/ogs-list.h: struct ogs_list_s { struct ogs_list_s *prev,*next; };
 * typedef struct ogs_list_s ogs_list_t; typedef struct ogs_list_s ogs_lnode_t; */
typedef struct ogs_list_s {
    struct ogs_list_s *prev, *next;
} ogs_list_t, ogs_lnode_t;

/* lib/core/ogs-sockaddr.h: typedef struct ogs_ipsubnet_s { int family;
 * uint32_t sub[4]; uint32_t mask[4]; } ogs_ipsubnet_t; */
typedef struct ogs_ipsubnet_s {
    int family;
    uint32_t sub[4];
    uint32_t mask[4];
} ogs_ipsubnet_t;

/* lib/pfcp/context.h: typedef struct ogs_pfcp_dev_s { ogs_lnode_t lnode;
 * char ifname[OGS_MAX_IFNAME_LEN]; ... } ogs_pfcp_dev_t; (fd/poll/is_tap/
 * mac_addr fields are network-plumbing state, not touched by the target
 * function -- omitted from this stand-in.) */
typedef struct ogs_pfcp_dev_s {
    ogs_lnode_t lnode;
    char        ifname[OGS_MAX_IFNAME_LEN];
} ogs_pfcp_dev_t;

/* lib/pfcp/context.h: typedef struct ogs_pfcp_subnet_s {
 *   ogs_lnode_t lnode; ogs_ipsubnet_t sub, gw;
 *   char dnn[OGS_MAX_DNN_LEN+1];              <- the overflow target
 *   struct { const char *low, *high; } range[OGS_MAX_NUM_OF_SUBNET_RANGE];
 *   int num_of_range; int family; uint8_t prefixlen;
 *   OGS_POOL(pool, ogs_pfcp_ue_ip_t);         <- real slab-pool bookkeeping,
 *                                                 not exercised by this fn
 *   ogs_pfcp_dev_t *dev;
 * } ogs_pfcp_subnet_t; */
typedef struct ogs_pfcp_subnet_s {
    ogs_lnode_t     lnode;
    ogs_ipsubnet_t  sub;
    ogs_ipsubnet_t  gw;
    char            dnn[OGS_MAX_DNN_LEN + 1];  /* 101 bytes -- overflow target */

    struct {
        const char *low;
        const char *high;
    } range[OGS_MAX_NUM_OF_SUBNET_RANGE];
    int      num_of_range;
    int      family;
    uint8_t  prefixlen;

    ogs_pfcp_dev_t *dev;
} ogs_pfcp_subnet_t;

/* lib/core/ogs-log.h: ogs_assert() fatal-asserts and aborts; stand-in with
 * the same control-flow effect (never actually taken on our call paths). */
#define ogs_assert(expr) \
    do { if (!(expr)) { fprintf(stderr, "ogs_assert failed: %s (line %d)\n", #expr, __LINE__); abort(); } } while (0)

/* === Minimal heap-backed stand-ins for the real pool allocator / device
 * registry / config-parser callers (project plumbing the target function
 * depends on but that has no bearing on the CWE-787 write itself). Every
 * ogs_pfcp_subnet_t is its own malloc(3) allocation so ASAN's redzones sit
 * immediately after `dnn`'s containing struct. === */

static ogs_pfcp_subnet_t *subnet_ptrs[OGS_MAX_NUM_OF_SUBNET];
static int subnet_alloc_count = 0;

static void pool_alloc(ogs_pfcp_subnet_t **out) {
    if (subnet_alloc_count < OGS_MAX_NUM_OF_SUBNET) {
        ogs_pfcp_subnet_t *p = malloc(sizeof(ogs_pfcp_subnet_t));
        if (p) {
            subnet_ptrs[subnet_alloc_count++] = p;
            *out = p;
        } else {
            *out = NULL;
        }
    } else {
        *out = NULL;
    }
}

static void pool_init(void) {
    memset(subnet_ptrs, 0, sizeof(subnet_ptrs));
    subnet_alloc_count = 0;
}

static ogs_pfcp_dev_t *dev_list[16];
static int dev_count = 0;

static ogs_pfcp_dev_t *ogs_pfcp_dev_find_by_ifname(const char *ifname) {
    for (int i = 0; i < dev_count; i++)
        if (strcmp(dev_list[i]->ifname, ifname) == 0)
            return dev_list[i];
    return NULL;
}

static ogs_pfcp_dev_t *ogs_pfcp_dev_add(const char *ifname) {
    if (dev_count >= 16) return NULL;
    ogs_pfcp_dev_t *d = calloc(1, sizeof(ogs_pfcp_dev_t));
    if (!d) return NULL;
    strncpy(d->ifname, ifname, OGS_MAX_IFNAME_LEN - 1);
    d->ifname[OGS_MAX_IFNAME_LEN - 1] = '\0';
    dev_list[dev_count++] = d;
    return d;
}

/* lib/pfcp/context.c ogs_ipsubnet(): parses ipstr/mask into an
 * ogs_ipsubnet_t. Not part of the DNN overflow path -- our call site
 * always passes ipstr/gateway == NULL, so this is never invoked; kept as
 * a faithful no-op stand-in only so the target function links. */
static int ogs_ipsubnet(ogs_ipsubnet_t *dst, const char *ipstr, const char *mask) {
    (void)ipstr; (void)mask;
    if (dst) { dst->family = 2; memset(dst->sub, 0, sizeof(dst->sub)); memset(dst->mask, 0, sizeof(dst->mask)); }
    return OGS_OK;
}

/* lib/core/ogs-list.h ogs_list_add(): prepend `lnode` to `list`. */
static ogs_list_t subnet_list = { NULL, NULL };
static void ogs_list_add(ogs_list_t *list, void *lnode) {
    ogs_lnode_t *node = (ogs_lnode_t *)lnode;
    node->prev = NULL;
    node->next = list->next;
    if (list->next) ((ogs_lnode_t *)list->next)->prev = node;
    list->next = node;
}

/* === The target function, VERBATIM from target/original_function.c === */

ogs_pfcp_subnet_t *ogs_pfcp_subnet_add(
        const char *ipstr, const char *mask_or_numbits,
        const char *gateway, const char *dnn, const char *ifname)
{
    int rv;
    ogs_pfcp_dev_t *dev = NULL;
    ogs_pfcp_subnet_t *subnet = NULL;

    ogs_assert(ifname);

    dev = ogs_pfcp_dev_find_by_ifname(ifname);
    if (!dev)
        dev = ogs_pfcp_dev_add(ifname);
    ogs_assert(dev);

    pool_alloc(&subnet);
    ogs_assert(subnet);
    memset(subnet, 0, sizeof *subnet);

    subnet->family = AF_UNSPEC;
    subnet->dev = dev;

    if (ipstr && mask_or_numbits) {
        rv = ogs_ipsubnet(&subnet->gw, ipstr, NULL);
        ogs_assert(rv == OGS_OK);

        rv = ogs_ipsubnet(&subnet->sub, ipstr, mask_or_numbits);
        ogs_assert(rv == OGS_OK);

        subnet->family = subnet->gw.family;
    }

    if (gateway) {
        rv = ogs_ipsubnet(&subnet->gw, gateway, NULL);
        ogs_assert(rv == OGS_OK);
    }

    if (dnn)
        strcpy(subnet->dnn, dnn);   /* <<< VULNERABLE: no bounds check! */

    ogs_list_add(&subnet_list, subnet);

    return subnet;
}

/* === main: read the whole input file into a HEAP buffer, call the target
 * function ONCE directly with it as the `dnn` argument. === */

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 1; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) { fclose(f); return 1; }
    if (sz > 65536) sz = 65536; /* generous cap; corpus inputs are far smaller */

    /* Heap buffer for the attacker-controlled DNN bytes -- required so ASAN
     * tracks it and the redzone sits right after the string. */
    char *dnn = malloc((size_t)sz + 1);
    if (!dnn) { fclose(f); return 1; }
    size_t rd = fread(dnn, 1, (size_t)sz, f);
    fclose(f);
    dnn[rd] = '\0';

    pool_init();
    dev_count = 0;
    subnet_list.next = subnet_list.prev = NULL;

    ogs_pfcp_subnet_t *result =
        ogs_pfcp_subnet_add(NULL, NULL, NULL, dnn, "eth0");

    if (!result) {
        fprintf(stderr, "ogs_pfcp_subnet_add returned NULL\n");
        free(dnn);
        return 1;
    }

    printf("subnet added, dnn (first 40 bytes): '%.40s'\n", result->dnn);
    free(dnn);
    return 0;
}

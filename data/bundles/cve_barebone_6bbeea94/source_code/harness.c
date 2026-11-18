/*
 * Direct-call crash harness for dataset/cve_6bbeea94 (CVE-2024-56826, openjpeg,
 * src/lib/openjp2/j2k.c, function opj_j2k_add_tlmarker).
 *
 * Root cause (verified against the upstream fix commit
 * e492644fbded4c820ca55b5e50e598d346e850e8, "opj_j2k_add_tlmarker(): validate
 * that current tile-part number if smaller that total number of tile-parts",
 * fetched live via `curl https://github.com/uclouvain/openjpeg/commit/<sha>.patch`;
 * matches baseline.dedup_token
 * "opj_j2k_add_tlmarker--opj_j2k_read_tile_header--opj_j2k_decode_tiles" and
 * baseline.summary "j2k.c:8460:84 in opj_j2k_add_tlmarker", access=WRITE,
 * cwe=CWE-787, bug_class=heap-buffer-overflow):
 *
 *   if (type == J2K_MS_SOT) {
 *       OPJ_UINT32 l_current_tile_part =
 *           cstr_index->tile_index[tileno].current_tpsno;
 *       if (cstr_index->tile_index[tileno].tp_index) {
 *           cstr_index->tile_index[tileno].tp_index[l_current_tile_part].start_pos = pos;   // <-- OOB WRITE
 *       }
 *   }
 *
 * `tp_index` is a heap array allocated (by the real caller,
 * opj_j2k_read_tile_header()) with exactly `nb_tps`/`current_nb_tps` entries.
 * `current_tpsno` is attacker-controlled tile-part-number state that is NEVER
 * validated against the array's allocated size before being used as an index
 * -- the fix adds exactly that bound check
 * (`l_current_tile_part < cstr_index->tile_index[tileno].nb_tps`). Any SOT
 * marker whose tile-part number is >= the array's allocated length drives an
 * out-of-bounds heap WRITE through `tp_index[l_current_tile_part].start_pos`.
 *
 * Direct-call semantics: opj_j2k_add_tlmarker() takes no buffer parameter --
 * its 5 scalar/pointer arguments (tileno, cstr_index, type, pos, len) are
 * exactly the real caller's arguments (see opj_j2k_read_tile_header(),
 * src/lib/openjp2/j2k.c ~line 9861:
 *   opj_j2k_add_tlmarker(p_j2k->m_current_tile_number, p_j2k->cstr_index,
 *                         l_marker_handler->id, ..., l_marker_size + 4)
 * ). main() reads argv[1] into a malloc'd HEAP buffer (never stack/global for
 * attacker data) and derives every argument -- crucially `current_tpsno`
 * (the value that drives the OOB index) and the `type`/`pos`/`len` scalars --
 * from that heap buffer, exactly mirroring how a real j2k_read_tile_header()
 * call chain would populate `cstr_index->tile_index[tileno].current_tpsno`
 * from attacker-controlled codestream bytes before calling this function.
 * `tp_index` itself is allocated on the heap (opj_calloc-equivalent, single
 * malloc()) with exactly ONE entry -- exactly like the real single-tile-part
 * case (nb_tps==1) the CVE's upstream issue (#1564) was filed against -- so
 * any current_tpsno >= 1 is a genuine heap-buffer-overflow WRITE, matching
 * the baseline's access=WRITE/bug_class=heap-buffer-overflow exactly.
 *
 * opj_j2k_add_tlmarker() is embedded byte-for-byte verbatim from
 * target/original_function.c (only a forward prototype carrying
 * __attribute__((noinline)) is added above the verbatim definition, so the
 * function keeps its own frame in the ASAN backtrace at -O1 -- the
 * definition's name/signature/logic are completely unmodified). All struct/
 * typedef/macro definitions below (opj_packet_info_t, opj_marker_info_t,
 * opj_tp_index_t, opj_tile_index_t, opj_codestream_index_t, OPJ_BOOL/
 * OPJ_UINT32/OPJ_UINT16/OPJ_INT32/OPJ_UINT64/OPJ_OFF_T/OPJ_FLOAT32,
 * J2K_MS_SOT) and the opj_realloc()/opj_free() helper the target function
 * calls are copied verbatim (real names, real field order/types) from
 * source_code/src/lib/openjp2/openjpeg.h, source_code/src/lib/openjp2/j2k.h
 * and source_code/src/lib/openjp2/opj_malloc.{h,c}.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ==================================================================== *
 * Base scalar typedefs -- verbatim from src/lib/openjp2/openjpeg.h
 * ==================================================================== */
typedef int OPJ_BOOL;
#define OPJ_TRUE 1
#define OPJ_FALSE 0
typedef float         OPJ_FLOAT32;
typedef uint16_t OPJ_UINT16;
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;
typedef uint64_t OPJ_UINT64;
typedef int64_t  OPJ_OFF_T; /* 64-bit file offset type */

/* ==================================================================== *
 * Marker id -- verbatim from src/lib/openjp2/j2k.h
 * ==================================================================== */
#define J2K_MS_SOT 0xff90   /**< SOT marker value */

/* ==================================================================== *
 * Index structs -- verbatim from src/lib/openjp2/openjpeg.h
 * ==================================================================== */

/**
 * Index structure : Information concerning a packet inside tile
 * */
typedef struct opj_packet_info {
    /** packet start position (including SOP marker if it exists) */
    OPJ_OFF_T start_pos;
    /** end of packet header position (including EPH marker if it exists)*/
    OPJ_OFF_T end_ph_pos;
    /** packet end position */
    OPJ_OFF_T end_pos;
    /** packet distortion */
    double disto;
} opj_packet_info_t;

/**
 * Marker structure
 * */
typedef struct opj_marker_info {
    /** marker type */
    unsigned short int type;
    /** position in codestream */
    OPJ_OFF_T pos;
    /** length, marker val included */
    int len;
} opj_marker_info_t;

/**
 * Index structure about a tile part
 */
typedef struct opj_tp_index {
    /** start position */
    OPJ_OFF_T start_pos;
    /** end position of the header */
    OPJ_OFF_T end_header;
    /** end position */
    OPJ_OFF_T end_pos;

} opj_tp_index_t;

/**
 * Index structure about a tile
 */
typedef struct opj_tile_index {
    /** tile index */
    OPJ_UINT32 tileno;

    /** number of tile parts */
    OPJ_UINT32 nb_tps;
    /** current nb of tile part (allocated)*/
    OPJ_UINT32 current_nb_tps;
    /** current tile-part index */
    OPJ_UINT32 current_tpsno;
    /** information concerning tile parts */
    opj_tp_index_t *tp_index;

    /* UniPG>> */ /* NOT USED FOR THE MOMENT IN THE V2 VERSION */
    /** number of markers */
    OPJ_UINT32 marknum;
    /** list of markers */
    opj_marker_info_t *marker;
    /** actual size of markers array */
    OPJ_UINT32 maxmarknum;
    /* <<UniPG */

    /** packet number */
    OPJ_UINT32 nb_packet;
    /** information concerning packets inside tile */
    opj_packet_info_t *packet_index;

} opj_tile_index_t;

/**
 * Index structure of the codestream (FIXME should be expand and enhance)
 */
typedef struct opj_codestream_index {
    /** main header start position (SOC position) */
    OPJ_OFF_T main_head_start;
    /** main header end position (first SOT position) */
    OPJ_OFF_T main_head_end;

    /** codestream's size */
    OPJ_UINT64 codestream_size;

    /* UniPG>> */ /* NOT USED FOR THE MOMENT IN THE V2 VERSION */
    /** number of markers */
    OPJ_UINT32 marknum;
    /** list of markers */
    opj_marker_info_t *marker;
    /** actual size of markers array */
    OPJ_UINT32 maxmarknum;
    /* <<UniPG */

    /** */
    OPJ_UINT32 nb_of_tiles;
    /** */
    opj_tile_index_t *tile_index; /* FIXME not used for the moment */

} opj_codestream_index_t;

/* ==================================================================== *
 * opj_realloc()/opj_free() -- verbatim from src/lib/openjp2/opj_malloc.c
 * (the two helpers the target function calls; thin wrappers over the libc
 * allocator, unmodified).
 * ==================================================================== */
void * opj_realloc(void *ptr, size_t new_size)
{
    if (new_size == 0U) { /* prevent implementation defined behavior of realloc */
        return NULL;
    }
    return realloc(ptr, new_size);
}
void opj_free(void *ptr)
{
    free(ptr);
}

/* ==================================================================== *
 * TARGET FUNCTION -- byte-for-byte verbatim from target/original_function.c.
 * Only a forward prototype with __attribute__((noinline)) is added above
 * the definition (so it keeps its own frame in the ASAN stack trace at
 * -O1); the definition itself, its name, its signature and its logic are
 * completely unmodified.
 * ==================================================================== */

static OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno,
                                     opj_codestream_index_t *cstr_index, OPJ_UINT32 type, OPJ_OFF_T pos,
                                     OPJ_UINT32 len)
    __attribute__((noinline));

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

/* ==================================================================== *
 * Direct-call driver.
 *
 * argv[1] byte layout (attacker input, read into a malloc'd HEAP buffer;
 * short files are zero-padded in the heap buffer itself -- never copied to
 * a stack/global staging buffer):
 *   [0..3]  little-endian uint32  tps_raw   -> tile_index[0].current_tpsno
 *                                              (the OOB index; the real bug
 *                                              is that this attacker value
 *                                              is NEVER bounds-checked)
 *   [4]     byte                  sot_flag  -> bit0 set  => type = J2K_MS_SOT
 *                                               (the vulnerable branch)
 *                                               bit0 clear => type = a
 *                                               different marker id (branch
 *                                               not taken -> safe)
 *   [5..8]  little-endian uint32  pos_raw   -> pos  (OPJ_OFF_T)
 *   [9..12] little-endian uint32  len_raw   -> len  (OPJ_UINT32)
 *   [13..]  ignored padding, only present to vary the on-disk file length /
 *           byte pattern across corpus entries.
 *
 * `tile_index[0].tp_index` is allocated with exactly ONE opj_tp_index_t
 * entry (the real single-tile-part case), so tps_raw >= 1 together with
 * sot_flag's bit0 set is an out-of-bounds heap WRITE through
 * tp_index[tps_raw].start_pos -- the real CVE-2024-56826 trigger, driven
 * entirely by attacker-controlled bytes from argv[1].
 * ==================================================================== */

static OPJ_UINT32 rd_u32le(const unsigned char *p, size_t n, size_t off)
{
    OPJ_UINT32 v = 0;
    for (int i = 0; i < 4; i++) {
        unsigned char b = (off + (size_t)i < n) ? p[off + (size_t)i] : 0;
        v |= ((OPJ_UINT32)b) << (8 * i);
    }
    return v;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 64;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 64; }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 64; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 64; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 64; }

    /* Attacker data lives ONLY on the heap. */
    unsigned char *buf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!buf) { fclose(f); return 64; }
    size_t n = fread(buf, 1, (size_t)fsz, f);
    fclose(f);

    OPJ_UINT32 tps_raw = rd_u32le(buf, n, 0);
    unsigned char sot_flag = (n > 4) ? buf[4] : 0;
    OPJ_UINT32 pos_raw = rd_u32le(buf, n, 5);
    OPJ_UINT32 len_raw = rd_u32le(buf, n, 9);

    OPJ_UINT32 type = (sot_flag & 1U) ? (OPJ_UINT32)J2K_MS_SOT : (OPJ_UINT32)0x0001u;
    OPJ_OFF_T pos = (OPJ_OFF_T)(OPJ_INT32)pos_raw;
    OPJ_UINT32 len = len_raw;

    /* Build cstr_index / tile_index[0] the way the real
     * opj_j2k_read_tile_header() caller would have it set up: a
     * single-tile codestream index whose tp_index array holds exactly ONE
     * entry (nb_tps == 1, the real single-tile-part case CVE-2024-56826's
     * upstream issue #1564 was filed against). */
    opj_codestream_index_t cstr_index;
    memset(&cstr_index, 0, sizeof(cstr_index));
    cstr_index.nb_of_tiles = 1;
    cstr_index.tile_index = (opj_tile_index_t *) malloc(sizeof(opj_tile_index_t) * 1);
    if (!cstr_index.tile_index) { free(buf); return 64; }
    memset(cstr_index.tile_index, 0, sizeof(opj_tile_index_t) * 1);

    cstr_index.tile_index[0].tileno = 0;
    cstr_index.tile_index[0].nb_tps = 1;
    cstr_index.tile_index[0].current_nb_tps = 1;
    cstr_index.tile_index[0].current_tpsno = tps_raw;   /* attacker-controlled OOB index */
    cstr_index.tile_index[0].tp_index =
        (opj_tp_index_t *) malloc(sizeof(opj_tp_index_t) * 1); /* real single-tile-part alloc */
    if (!cstr_index.tile_index[0].tp_index) { free(cstr_index.tile_index); free(buf); return 64; }
    memset(cstr_index.tile_index[0].tp_index, 0, sizeof(opj_tp_index_t) * 1);
    cstr_index.tile_index[0].marknum = 0;
    cstr_index.tile_index[0].marker = NULL;
    cstr_index.tile_index[0].maxmarknum = 0;
    cstr_index.tile_index[0].nb_packet = 0;
    cstr_index.tile_index[0].packet_index = NULL;

    (void) opj_j2k_add_tlmarker(0, &cstr_index, type, pos, len);

    /* Only reached on the safe path. */
    opj_free(cstr_index.tile_index[0].marker);
    free(cstr_index.tile_index[0].tp_index);
    free(cstr_index.tile_index);
    free(buf);
    return 0;
}

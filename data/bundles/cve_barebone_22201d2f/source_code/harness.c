/* cve_barebone direct-call harness for cve_22201d2f (openjpeg CVE-2017-14039)
 * Target: opj_j2k_write_sod  (src/lib/openjp2/j2k.c, byte-for-byte below)
 * Bug class: heap-buffer-overflow WRITE (CWE-787) -- missing buffer-capacity check.
 *
 * See scripts/gen_dc_cve_22201d2f.py module docstring for the full analysis. Short
 * version: opj_j2k_write_sod's very first action, pre-fix, is an UNCONDITIONAL
 * opj_write_bytes(p_data, J2K_MS_SOD, 2) -- 2 bytes written into p_data with no check
 * that p_total_data_size (the documented remaining capacity of that buffer) is even
 * that large. Calling it directly with p_total_data_size in {0,1} and a p_data buffer
 * malloc'd to exactly that many bytes overflows on the spot, inside opj_write_bytes_LE
 * (the real callee, pasted verbatim below), called from opj_j2k_write_sod's own body.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdarg.h>

/* ==== VERBATIM base scalar typedefs (openjpeg.h) ==== */
typedef int OPJ_BOOL;
#define OPJ_TRUE 1
#define OPJ_FALSE 0

typedef char          OPJ_CHAR;
typedef float         OPJ_FLOAT32;
typedef double        OPJ_FLOAT64;
typedef unsigned char OPJ_BYTE;

/* ==== VERBATIM (openjpeg.h): OPJ_INT8..OPJ_UINT64, OPJ_OFF_T ==== */
typedef int8_t   OPJ_INT8;
typedef uint8_t  OPJ_UINT8;
typedef int16_t  OPJ_INT16;
typedef uint16_t OPJ_UINT16;
typedef int32_t  OPJ_INT32;
typedef uint32_t OPJ_UINT32;
typedef int64_t  OPJ_INT64;
typedef uint64_t OPJ_UINT64;

typedef int64_t  OPJ_OFF_T; /* 64-bit file offset type */

/* ==== VERBATIM (openjpeg.h): the message-callback function-pointer typedef ==== */
typedef void (*opj_msg_callback)(const char *msg, void *client_data);

/* ==== VERBATIM (j2k.h): the SOD marker constant opj_j2k_write_sod writes ==== */
#define J2K_MS_SOD 0xff93   /**< SOD marker value */

/* ==== VERBATIM (j2k.c line 51): the local OPJ_UNUSED macro opj_j2k_write_sod uses ==== */
#define OPJ_UNUSED(x) (void)x

/* ==== VERBATIM (event.h): opj_event_mgr_t + its EVT_* dispatch codes ==== */
typedef struct opj_event_mgr {
    /** Data to call the event manager upon */
    void *          m_error_data;
    /** Data to call the event manager upon */
    void *          m_warning_data;
    /** Data to call the event manager upon */
    void *          m_info_data;
    /** Error message callback if available, NULL otherwise */
    opj_msg_callback error_handler;
    /** Warning message callback if available, NULL otherwise */
    opj_msg_callback warning_handler;
    /** Debug message callback if available, NULL otherwise */
    opj_msg_callback info_handler;
} opj_event_mgr_t;
#define EVT_ERROR   1   /**< Error event type */
#define EVT_WARNING 2   /**< Warning event type */
#define EVT_INFO    4   /**< Debug event type */

/* ---- Trimmed, real-named/real-typed structs (see harness header + task rules: no
 * invented names/fields). opj_j2k_t/opj_tcd_t/opj_j2k_enc_t/opj_j2k_dec_t are big
 * real structs in the library; this is a single self-contained translation unit (no
 * external code links against these types), so only the fields opj_j2k_write_sod's
 * own body actually reads/writes need to be present, in their real relative order --
 * trailing fields it never touches are omitted, which cannot desync any offset the
 * pasted function uses (there is nothing after them for the offsets to disagree
 * about). ---- */

/* real name/shape: opj_j2k_write_sod only ever touches p_j2k->m_specific_param.
 * m_encoder.{m_current_poc_tile_part_number,m_current_tile_part_number} -- never
 * .m_decoder -- so opj_j2k_dec_t keeps just its real first field for a realistic
 * union shape. */
typedef struct opj_j2k_dec {
    OPJ_UINT32 m_state;   /* real first field (j2k.h); unused by opj_j2k_write_sod */
} opj_j2k_dec_t;

typedef struct opj_j2k_enc {
    /* Tile part number, regardless of poc, for each new poc, tp is reset to 1*/
    OPJ_UINT32 m_current_poc_tile_part_number; /* tp_num */
    /* Tile part number currently coding. */
    OPJ_UINT32 m_current_tile_part_number; /*cur_tp_num */
    /* remaining real opj_j2k_enc_t fields (m_tlm_start, m_tlm_sot_offsets_*,
     * m_total_tile_parts, m_encoded_tile_*, m_header_tile_*) are never touched by
     * opj_j2k_write_sod and are omitted. */
} opj_j2k_enc_t;

typedef struct opj_j2k {
    union {
        opj_j2k_dec_t m_decoder;
        opj_j2k_enc_t m_encoder;
    } m_specific_param;
    /** number of the tile currently concern by coding/decoding */
    OPJ_UINT32 m_current_tile_number;
    /* remaining real opj_j2k_t fields (m_is_decoder, m_private_image, m_output_image,
     * m_cp, m_procedure_list, m_validation_list, cstr_index, m_tcd, m_num_threads,
     * m_tp, ihdr_w/h, enumcs, dump_state) are never touched by opj_j2k_write_sod and
     * are omitted. */
} opj_j2k_t;

/* real name/shape (tcd.h): opj_j2k_write_sod only writes ->packno, inside the
 * "m_current_tile_part_number==0" branch. */
typedef struct opj_tcd_tile {
    OPJ_UINT32 packno;    /* packet number -- real, only field opj_j2k_write_sod touches */
    /* remaining real opj_tcd_tile_t fields (x0/y0/x1/y1, numcomps, comps, numpix,
     * distotile, distolayer[100]) are never touched and are omitted. */
} opj_tcd_tile_t;

typedef struct opj_tcd_image {
    opj_tcd_tile_t *tiles;      /* Tiles information -- real, only field (tcd.h) */
} opj_tcd_image_t;

typedef struct opj_tcd {
    /** Tile part number*/
    OPJ_UINT32 tp_num;
    /** Current tile part number*/
    OPJ_UINT32 cur_tp_num;
    /** info on each image tile */
    opj_tcd_image_t *tcd_image;
    /* remaining real opj_tcd_t fields (tp_pos, cur_totnum_tp, cur_pino, image, cp,
     * tcp, tcd_tileno, m_is_decoder, thread_pool) are never touched by
     * opj_j2k_write_sod and are omitted. */
} opj_tcd_t;

/* opj_j2k_write_sod's local `opj_codestream_info_t *l_cstr_info` is always NULL at
 * runtime (set at top, only ever read inside `if (l_cstr_info)`, never assigned) --
 * but the dead `l_cstr_info->packno = 0;` inside that always-false branch is still
 * type-checked at compile time, so the type must be COMPLETE with a real `packno`
 * member (openjpeg.h: `double D_max; int packno; ...`). Trimmed to the real fields up
 * to and including the one this dead code names; the rest are never referenced. */
typedef struct opj_codestream_info {
    double D_max;   /* real first field (openjpeg.h) */
    int packno;     /* real field opj_j2k_write_sod's dead branch assigns */
} opj_codestream_info_t;

/* p_stream is only ever passed through OPJ_UNUSED(p_stream) -- never dereferenced.
 * Real name, incomplete type (cio.c's real opj_stream_private_t is a full struct;
 * this TU never needs its layout). */
struct opj_stream_private;
typedef struct opj_stream_private opj_stream_private_t;

/* ---- incidental callees: real name + real signature, minimal faithful bodies ---- */

/* real signature (event.h); this exact overload is never actually invoked by any
 * crafted input below (opj_tcd_encode_tile's stub always returns OPJ_TRUE, so the
 * "Cannot encode tile" call site is dead for us) -- implemented properly anyway
 * rather than as a bare no-op. */
static OPJ_BOOL opj_event_msg(opj_event_mgr_t *event_mgr, OPJ_INT32 event_type,
                              const char *fmt, ...)
{
    opj_msg_callback cb = NULL;
    void *data = NULL;
    if (!event_mgr) {
        return OPJ_FALSE;
    }
    if (event_type == EVT_ERROR) {
        cb = event_mgr->error_handler;
        data = event_mgr->m_error_data;
    } else if (event_type == EVT_WARNING) {
        cb = event_mgr->warning_handler;
        data = event_mgr->m_warning_data;
    } else if (event_type == EVT_INFO) {
        cb = event_mgr->info_handler;
        data = event_mgr->m_info_data;
    }
    if (cb) {
        char buf[512];
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, sizeof(buf), fmt, ap);
        va_end(ap);
        cb(buf, data);
    }
    return OPJ_TRUE;
}

/* real signature (tcd.h): OPJ_BOOL opj_tcd_encode_tile(opj_tcd_t*, OPJ_UINT32,
 * OPJ_BYTE*, OPJ_UINT32*, OPJ_UINT32, struct opj_codestream_info*, opj_event_mgr_t*).
 * The real implementation is the whole tier-1/tier-2 wavelet+entropy tile encoder
 * (thousands of lines across t1.c/t2.c/tcd.c), which needs a fully populated
 * opj_image_t/opj_tcp_t/opj_cp_t coding/coefficient state that cannot be faithfully
 * constructed from this one function's binary -- exactly the "deep call graph /
 * elaborate object state" case the task rules say to route around, not fake. This
 * function is OFF the crash path this harness reproduces: for every triggering input
 * below, opj_j2k_write_sod already crashed (on its own unconditional 2-byte
 * opj_write_bytes call) before this would ever be reached. It is written to be
 * memory-safe for EVERY p_len value it could be called with, including an
 * underflowed one -- it never writes to p_dest -- so it cannot manufacture a crash of
 * its own on the "safe" inputs. */
static OPJ_BOOL opj_tcd_encode_tile(opj_tcd_t *p_tcd, OPJ_UINT32 p_tile_no,
                                    OPJ_BYTE *p_dest, OPJ_UINT32 *p_data_written,
                                    OPJ_UINT32 p_len, struct opj_codestream_info *p_cstr_info,
                                    opj_event_mgr_t *p_manager)
{
    (void)p_tcd; (void)p_tile_no; (void)p_dest; (void)p_len;
    (void)p_cstr_info; (void)p_manager;
    if (p_data_written) {
        *p_data_written = 0;
    }
    return OPJ_TRUE;
}


/* ==== VERBATIM real crash-path callee (cio.c): opj_write_bytes(p_data, J2K_MS_SOD,
 * 2) resolves (via the macro below) to this function -- a plain byte-by-byte copy
 * loop with NO bounds check of its own. noinline is a build attribute on OUR wrapper
 * declaration, added here, NOT a change to the pasted bytes below (there are none to
 * change -- this is the real callee, not the target). ==== */
#define opj_write_bytes opj_write_bytes_LE
__attribute__((noinline))
void opj_write_bytes_LE(OPJ_BYTE * p_buffer, OPJ_UINT32 p_value,
                        OPJ_UINT32 p_nb_bytes)
{
    const OPJ_BYTE * l_data_ptr = ((const OPJ_BYTE *) &p_value) + p_nb_bytes - 1;
    OPJ_UINT32 i;

    assert(p_nb_bytes > 0 && p_nb_bytes <= sizeof(OPJ_UINT32));

    for (i = 0; i < p_nb_bytes; ++i) {
        *(p_buffer++) = *(l_data_ptr--);
    }
}

/* ==== end verbatim opj_write_bytes_LE ==== */

/* ==== TARGET (VERBATIM, byte-for-byte target/original_function.c; checked) ==== */
static OPJ_BOOL opj_j2k_write_sod(opj_j2k_t *p_j2k,
                                  opj_tcd_t * p_tile_coder,
                                  OPJ_BYTE * p_data,
                                  OPJ_UINT32 * p_data_written,
                                  OPJ_UINT32 p_total_data_size,
                                  const opj_stream_private_t *p_stream,
                                  opj_event_mgr_t * p_manager
                                 )
{
    opj_codestream_info_t *l_cstr_info = 00;
    OPJ_UINT32 l_remaining_data;

    /* preconditions */
    assert(p_j2k != 00);
    assert(p_manager != 00);
    assert(p_stream != 00);

    OPJ_UNUSED(p_stream);

    opj_write_bytes(p_data, J2K_MS_SOD,
                    2);                                 /* SOD */
    p_data += 2;

    /* make room for the EOF marker */
    l_remaining_data =  p_total_data_size - 4;

    /* update tile coder */
    p_tile_coder->tp_num =
        p_j2k->m_specific_param.m_encoder.m_current_poc_tile_part_number ;
    p_tile_coder->cur_tp_num =
        p_j2k->m_specific_param.m_encoder.m_current_tile_part_number;

    /* INDEX >> */
    /* TODO mergeV2: check this part which use cstr_info */
    /*l_cstr_info = p_j2k->cstr_info;
    if (l_cstr_info) {
            if (!p_j2k->m_specific_param.m_encoder.m_current_tile_part_number ) {
                    //TODO cstr_info->tile[p_j2k->m_current_tile_number].end_header = p_stream_tell(p_stream) + p_j2k->pos_correction - 1;
                    l_cstr_info->tile[p_j2k->m_current_tile_number].tileno = p_j2k->m_current_tile_number;
            }
            else {*/
    /*
    TODO
    if
            (cstr_info->tile[p_j2k->m_current_tile_number].packet[cstr_info->packno - 1].end_pos < p_stream_tell(p_stream))
    {
            cstr_info->tile[p_j2k->m_current_tile_number].packet[cstr_info->packno].start_pos = p_stream_tell(p_stream);
    }*/
    /*}*/
    /* UniPG>> */
#ifdef USE_JPWL
    /* update markers struct */
    /*OPJ_BOOL res = j2k_add_marker(p_j2k->cstr_info, J2K_MS_SOD, p_j2k->sod_start, 2);
    */
    assert(0 && "TODO");
#endif /* USE_JPWL */
    /* <<UniPG */
    /*}*/
    /* << INDEX */

    if (p_j2k->m_specific_param.m_encoder.m_current_tile_part_number == 0) {
        p_tile_coder->tcd_image->tiles->packno = 0;
        if (l_cstr_info) {
            l_cstr_info->packno = 0;
        }
    }

    *p_data_written = 0;

    if (! opj_tcd_encode_tile(p_tile_coder, p_j2k->m_current_tile_number, p_data,
                              p_data_written, l_remaining_data, l_cstr_info,
                              p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "Cannot encode tile\n");
        return OPJ_FALSE;
    }

    *p_data_written += 2;

    return OPJ_TRUE;
}
/* ==== end verbatim opj_j2k_write_sod ==== */

/* ================= driver =================
 * Input layout (attacker-controlled bytes, FDP-style):
 *   b0 (bit0): 0 => TRIGGER branch, 1 => SAFE branch
 *   b1: TRIGGER -> total_data_size = b1 & 1 (0 or 1, both < 2 -> overflow the very
 *                  first 2-byte SOD-marker write)
 *       SAFE    -> total_data_size = 4 + b1 (>=4 -> matches the patched guard's own
 *                  threshold: the SOD write, and the underflow-avoided
 *                  l_remaining_data, both stay in-bounds/correct)
 *   b2: m_current_tile_part_number low byte (both branches: safe regardless of value,
 *       see the always-valid tcd_image/tile chain built below)
 *   b3: m_current_poc_tile_part_number low byte (never dereferenced further; only
 *       copied into p_tile_coder->tp_num)
 * p_data is a HEAP buffer malloc'd to EXACTLY total_data_size bytes -- the ASAN
 * redzone starts right where the real caller's buffer capacity would end.
 */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;
    unsigned char *seed = (unsigned char *)malloc(n ? n : 1);   /* HEAP input */
    size_t got = n ? fread(seed, 1, n, fp) : 0;
    (void)got;
    fclose(fp);

    unsigned char b0 = n > 0 ? seed[0] : 0;
    unsigned char b1 = n > 1 ? seed[1] : 0;
    unsigned char b2 = n > 2 ? seed[2] : 0;
    unsigned char b3 = n > 3 ? seed[3] : 0;

    OPJ_UINT32 total_data_size;
    if (b0 & 1) {
        total_data_size = 4u + (OPJ_UINT32)b1;      /* SAFE: guard-satisfying size */
    } else {
        total_data_size = (OPJ_UINT32)(b1 & 1u);    /* TRIGGER: 0 or 1 (< 2) */
    }

    /* Destination buffer: exactly total_data_size bytes, heap, ASAN-guarded. This
     * mirrors what p_total_data_size documents elsewhere in this same file
     * (opj_tcd_encode_tile's own doc comment: "Maximum length of the destination
     * buffer") -- the buffer's real capacity IS this value. */
    OPJ_BYTE *p_data = (OPJ_BYTE *)malloc(total_data_size);

    OPJ_UINT32 data_written = 0;

    /* p_tile_coder: always a fully valid tp_num/cur_tp_num/tcd_image->tiles chain,
     * regardless of which branch m_current_tile_part_number==0 takes. */
    opj_tcd_tile_t tile;
    memset(&tile, 0, sizeof(tile));
    opj_tcd_image_t tcd_image;
    tcd_image.tiles = &tile;
    opj_tcd_t tile_coder;
    memset(&tile_coder, 0, sizeof(tile_coder));
    tile_coder.tcd_image = &tcd_image;

    opj_j2k_t j2k;
    memset(&j2k, 0, sizeof(j2k));
    j2k.m_specific_param.m_encoder.m_current_poc_tile_part_number = b3;
    j2k.m_specific_param.m_encoder.m_current_tile_part_number = b2;
    j2k.m_current_tile_number = 0;

    opj_event_mgr_t manager;
    memset(&manager, 0, sizeof(manager));

    /* p_stream: real incomplete type, only ever cast to void -- any non-NULL value
     * satisfies opj_j2k_write_sod's own `assert(p_stream != 00)`. */
    int stream_marker = 0;
    opj_stream_private_t *p_stream = (opj_stream_private_t *)&stream_marker;

    /* Call through a volatile function pointer so this static target cannot be
     * inlined into main() (keeps it a real, named frame in the ASAN backtrace) --
     * this is a property of OUR call site, not an edit to opj_j2k_write_sod's own
     * (unreachable-to-us) declaration/definition text. */
    OPJ_BOOL (*volatile fn)(opj_j2k_t *, opj_tcd_t *, OPJ_BYTE *, OPJ_UINT32 *,
                            OPJ_UINT32, const opj_stream_private_t *, opj_event_mgr_t *) =
        opj_j2k_write_sod;
    (void)fn(&j2k, &tile_coder, p_data, &data_written, total_data_size, p_stream, &manager);

    free(p_data);
    free(seed);
    return 0;
}

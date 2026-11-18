/* cve_barebone direct-call harness for cve_41e43e19 (WavPack)
 * Target: read_new_config_info  (src/open_utils.c)
 * CVE-2016-10169 -- heap-buffer-overflow READ (CWE-125).
 *
 * fix_commit 4bc05fc490b66ef2d45b1de26abf1455b486b0dc changed the function's first data
 * gate from `if (bytecnt)` to `if (bytecnt >= 2)`: the old code unconditionally consumed
 * TWO bytes (file_format, qmode) as soon as byte_length was merely non-zero. With
 * byte_length == 1 and wpmd->data sized to exactly that (the real, upstream-enforced
 * invariant from read_metadata_buff() -- byte_length IS the metadata sub-block's true
 * available size), the second read runs one byte past the allocation.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FALSE 0
#define TRUE 1

/* ---- WavpackConfig: real struct, verbatim (wavpack_local.h) -- no further type deps. ---- */
typedef struct {
    float bitrate, shaping_weight;
    int bits_per_sample, bytes_per_sample;
    int qmode, flags, xmode, num_channels, float_norm_exp;
    int32_t block_samples, extra_flags, sample_rate, channel_mask;
    unsigned char md5_checksum [16], md5_read;
    int num_tag_strings;
    char **tag_strings;
} WavpackConfig;

/* ---- WavpackMetadata: real struct, verbatim (wavpack_local.h). ---- */
typedef struct {
    int32_t byte_length;
    void *data;
    unsigned char id;
} WavpackMetadata;

/* ---- WavpackContext: real field NAMES and TYPES (wavpack_local.h), trimmed to exactly
 * what read_new_config_info's own body touches. This is a single, self-contained TU (no
 * linking against the rest of libwavpack), so only the touched storage needs to actually
 * exist -- the omitted real members (read/write callbacks, WavpackStream **streams,
 * M_Tag, bitstream decode state, ...) are never referenced by this function. */
typedef struct {
    WavpackConfig config;
    int version_five;
    unsigned char file_format, *channel_reordering, *channel_identities;
    uint32_t channel_layout;
} WavpackContext;

/* ==== VERBATIM from data_cve/cve_41e43e19/target/original_function.c ====
 * noinline so the crash keeps its own stack frame (dc_batch requires the target
 * function name in the ASAN backtrace). */
__attribute__((noinline))
static int read_new_config_info (WavpackContext *wpc, WavpackMetadata *wpmd)
{
    int bytecnt = wpmd->byte_length;
    unsigned char *byteptr = wpmd->data;

    wpc->version_five = 1;      // just having this block signals version 5.0

    wpc->file_format = wpc->config.qmode = wpc->channel_layout = 0;

    if (wpc->channel_reordering) {
        free (wpc->channel_reordering);
        wpc->channel_reordering = NULL;
    }

    // if there's any data, the first two bytes are file_format and qmode flags

    if (bytecnt) {
        wpc->file_format = *byteptr++;
        wpc->config.qmode = (wpc->config.qmode & ~0xff) | *byteptr++;
        bytecnt -= 2;

        // another byte indicates a channel layout

        if (bytecnt) {
            int nchans, i;

            wpc->channel_layout = (int32_t) *byteptr++ << 16;
            bytecnt--;

            // another byte means we have a channel count for the layout and maybe a reordering

            if (bytecnt) {
                wpc->channel_layout += nchans = *byteptr++;
                bytecnt--;

                // any more means there's a reordering string

                if (bytecnt) {
                    if (bytecnt > nchans)
                        return FALSE;

                    wpc->channel_reordering = malloc (nchans);

                    // note that redundant reordering info is not stored, so we fill in the rest

                    if (wpc->channel_reordering) {
                        for (i = 0; i < nchans; ++i)
                            if (bytecnt) {
                                wpc->channel_reordering [i] = *byteptr++;
                                bytecnt--;
                            }
                            else
                                wpc->channel_reordering [i] = i;
                    }
                }
            }
            else
                wpc->channel_layout += wpc->config.num_channels;
        }
    }

    return TRUE;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input (ASAN-guarded); its bytes only SELECT/SEED the
     * WavpackMetadata block constructed below -- they are not blitted in verbatim. */
    unsigned char *raw = (unsigned char *)malloc((size_t)sz + 1);
    if (!raw) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(raw, 1, (size_t)sz, f) : 0;
    fclose(f);
    if (n < 1) { free(raw); return 0; }        /* nothing to seed from -> clean exit */

    WavpackContext wpc;
    memset(&wpc, 0, sizeof wpc);
    wpc.config.num_channels = 2;               /* plausible default; only read on one safe path */

    WavpackMetadata wpmd;
    memset(&wpmd, 0, sizeof wpmd);

    int trigger = raw[0] & 1;
    int bytecnt;
    unsigned char *buf;

    if (trigger) {
        /* TRIGGER: byte_length == 1, wpmd->data sized to exactly that (the real
         * upstream invariant -- see header comment). read_new_config_info's own first
         * gate (pre-fix `if (bytecnt)`) still reads a SECOND byte for qmode ->
         * heap-buffer-overflow READ of size 1, one byte past this 1-byte allocation. */
        bytecnt = 1;
        buf = (unsigned char *)malloc(1);
        buf[0] = (n > 1) ? raw[1] : 0x41;
    } else {
        /* SAFE: byte_length values whose consumption the function provably keeps within
         * a buffer sized to exactly that length (hand-traced in the header comment --
         * every read past the first two bytes is individually gated by its own
         * `if (bytecnt)` that decrements in lockstep with bytes actually consumed, so it
         * never overruns as long as bytecnt never goes negative, i.e. byte_length != 1).
         * Spans every branch: 0 (no data at all), 2/3/4 (partial header, no reordering
         * string), and >=5 (full reordering-string loop, both the `bytecnt > nchans`
         * early-FALSE path and the fully-consumed path). */
        static const int lens[] = {0, 2, 3, 4, 6, 9, 14, 20, 30, 45};
        int L = lens[(size_t)((n > 1 ? raw[1] : 0)) % (sizeof(lens) / sizeof(lens[0]))];
        bytecnt = L;
        buf = (unsigned char *)malloc(L ? (size_t)L : 1);
        for (int i = 0; i < L; i++)
            buf[i] = (n > (size_t)(2 + i)) ? raw[2 + i] : (unsigned char)(0x30 + i);
        if (L >= 5) {
            /* buf[3] is the nchans byte; bias it >= (L-4) so the reordering loop
             * consumes exactly its remaining bytecnt down to 0 (fully exercises the
             * malloc+loop body) instead of always taking the early `return FALSE`. */
            int need = L - 4;
            if ((int)buf[3] < need) buf[3] = (unsigned char)(need < 255 ? need : 255);
        }
    }

    wpmd.byte_length = bytecnt;
    wpmd.data = buf;
    wpmd.id = 0;

    /* volatile function pointer: forbid inlining/interprocedural proof that the call
     * (and the memory accesses inside it) has no observable effect. */
    int (*volatile fn)(WavpackContext *, WavpackMetadata *) = read_new_config_info;
    int rc = fn(&wpc, &wpmd);

    /* Use the mutated fields so the compiler can't retroactively prove the call's
     * writes (and therefore its reads) were dead. Unreached on the TRIGGER path --
     * ASAN aborts inside the call above. */
    volatile unsigned char sink = wpc.file_format ^ (unsigned char)wpc.channel_layout ^ (unsigned char)rc;
    (void)sink;
    if (wpc.channel_reordering) free(wpc.channel_reordering);
    free(buf);
    free(raw);
    return 0;
}

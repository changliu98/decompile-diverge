/* cve_barebone harness -- CVE-2016-10170 / WavPack read_new_config_info()
 *
 * Isolated reproduction. read_new_config_info() is driven directly with a
 * WavpackMetadata sub-block whose declared byte_length/data buffer are both attacker-
 * controlled (heap-allocated, exact size == the declared length -- matching how the
 * real caller pre-sizes the metadata buffer from the block's own byte_length). A
 * declared length of exactly 1 makes the buggy top-level `if (bytecnt)` guard (should
 * be `if (bytecnt >= 2)`) read a 2nd byte that does not exist -> heap-buffer-overflow
 * READ (CWE-125), immediately inside read_new_config_info's own frame.
 *
 * Crash stack: read_new_config_info -- main
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- real macros (wavpack_local.h) ---- */
#define FALSE 0
#define TRUE 1

/* ---- WavpackConfig: VERBATIM (wavpack_local.h) ---- */
typedef struct {
    float bitrate, shaping_weight;
    int bits_per_sample, bytes_per_sample;
    int qmode, flags, xmode, num_channels, float_norm_exp;
    int32_t block_samples, extra_flags, sample_rate, channel_mask;
    unsigned char md5_checksum [16], md5_read;
    int num_tag_strings;
    char **tag_strings;
} WavpackConfig;

/* ---- WavpackMetadata: VERBATIM (wavpack_local.h) ---- */
typedef struct {
    int32_t byte_length;
    void *data;
    unsigned char id;
} WavpackMetadata;

/* ---- WavpackContext: TRIMMED to the fields read_new_config_info touches.
 * Every kept field is verbatim (name + type) from wavpack_local.h, in the same
 * relative order as the real struct. The full struct also carries WavpackMetadata*,
 * WavpackBlockOutput, WavpackStreamReader64*, M_Tag, WavpackStream**, etc. that this
 * function never references, so they are omitted rather than dragging in their whole
 * (unrelated) type graph. */
typedef struct {
    WavpackConfig config;
    int version_five;
    unsigned char file_format, *channel_reordering;
    uint32_t channel_layout;
} WavpackContext;

/* ---- TARGET (VERBATIM, byte-for-byte original_function.c); noinline to keep the
 * crash frame -- same pattern used across the other cve_barebone harnesses. ---- */
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

/* ================= driver ================= */
/* File byte[0] = declared metadata byte_length (0..255). File bytes[1..] = the
 * metadata sub-block content, copied verbatim (missing trailing bytes default to 0).
 * The metadata buffer is malloc'd to EXACTLY the declared length -- an ASAN-visible
 * heap allocation the same size the real parser would carve for this sub-block --
 * so any out-of-bounds read past it is a genuine heap-buffer-overflow.
 *
 * declared_len == 1 -> deterministically triggers the CVE (2nd byte read is already
 * past a 1-byte allocation). declared_len == 0, or >= 2 with the data fully
 * accounting for its own consumption, is SAFE (matches the intended parse). */
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
    unsigned char *raw = (unsigned char *)malloc(n ? n : 1);   /* HEAP input */
    size_t got = fread(raw, 1, n, fp);
    fclose(fp);

    int declared_len = (got >= 1) ? raw[0] : 0;
    size_t avail = (got > 1) ? (got - 1) : 0;

    unsigned char *mdata = NULL;
    if (declared_len > 0) {
        mdata = (unsigned char *)malloc((size_t)declared_len);  /* HEAP, EXACT size */
        for (int i = 0; i < declared_len; i++)
            mdata[i] = ((size_t)i < avail) ? raw[1 + i] : 0;
    }

    WavpackContext wpc;
    memset(&wpc, 0, sizeof wpc);
    wpc.config.num_channels = 2;   /* plausible real value; only read on one safe path */

    WavpackMetadata wpmd;
    memset(&wpmd, 0, sizeof wpmd);
    wpmd.byte_length = declared_len;
    wpmd.data = mdata;

    /* volatile pointer: forbid inlining read_new_config_info into main so it stays a
     * real stack frame (dc_batch requires the target function in the crash stack). */
    int (*volatile fn)(WavpackContext *, WavpackMetadata *) = read_new_config_info;
    fn(&wpc, &wpmd);

    if (wpc.channel_reordering)
        free(wpc.channel_reordering);
    free(mdata);
    free(raw);
    return 0;
}

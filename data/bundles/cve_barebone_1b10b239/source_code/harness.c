/* Direct-call crash harness for CVE-2016-10171 (wavpack, read_new_config_info).
 *
 * Real bug (src/open_utils.c): read_new_config_info() walks the "new config"
 * metadata block with a SIGNED counter `bytecnt = wpmd->byte_length` and a raw
 * pointer `byteptr = wpmd->data`. After it reads the first two bytes it does
 * `bytecnt -= 2`, but it only ever guarded the block with `if (bytecnt)` (i.e.
 * bytecnt != 0), never `bytecnt > 0`. So when the metadata declares
 * byte_length == 1, `bytecnt` becomes -1, and every subsequent `if (bytecnt)`
 * is TRUE for the negative value -- the function keeps post-incrementing
 * `byteptr` and reading past the end of the real data buffer. The over-read at
 * `wpc->channel_layout = (int32_t) *byteptr++ << 16;` (open_utils.c:573, the
 * third byte read = index 2) runs off the end of the metadata buffer: a
 * heap-buffer-overflow READ (CWE-125), exactly the reference crash
 *   AddressSanitizer: heap-buffer-overflow src/open_utils.c:573:45
 *   dedup: read_new_config_info--process_metadata--unpack_init
 *
 * Faithful isolation model: in the real unpacker read_metadata_buff() reserves
 * `byte_length + (byte_length & 1)` bytes for wpmd->data (open_utils.c:686 --
 * the declared length rounded up to even for the block's word alignment). This
 * harness reproduces that footprint EXACTLY: it heap-allocates the data buffer
 * with size `byte_length + (byte_length & 1)`. With byte_length == 1 that is a
 * 2-byte chunk (indices 0,1 valid); the buggy third read at index 2 (line 573)
 * overflows it -- byte-for-byte the same access the reference PoC hits.
 *
 * Input format (FDP-style, first byte drives the metadata, rest is the data):
 *   raw[0]            -> wpmd.byte_length   (the attacker-declared length)
 *   raw[1 ..]         -> the metadata data bytes, copied into a heap buffer of
 *                        size (byte_length + (byte_length & 1)); short inputs
 *                        are zero-padded to that size.
 * TRIGGER  <=> byte_length == 1  (the unique value that drives bytecnt negative
 *              and over-reads at line 573).
 * SAFE     <=> byte_length in {0,2,3,4,...}: every byteptr read stays within the
 *              padded buffer, the function returns cleanly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- REAL macros, verbatim from src/wavpack_local.h:68-69 ---- */
#define FALSE 0
#define TRUE 1

/* ---- REAL type defs, verbatim names/fields from src/wavpack_local.h ---- */

/* src/wavpack_local.h:268-276 (the internal WavpackConfig; qmode + num_channels
 * are the fields read_new_config_info touches) */
typedef struct {
    float bitrate, shaping_weight;
    int bits_per_sample, bytes_per_sample;
    int qmode, flags, xmode, num_channels, float_norm_exp;
    int32_t block_samples, extra_flags, sample_rate, channel_mask;
    unsigned char md5_checksum [16], md5_read;
    int num_tag_strings;
    char **tag_strings;
} WavpackConfig;

/* src/wavpack_local.h:222-226 (WavpackMetadata -- byte_length + data drive the
 * walk) */
typedef struct {
    int32_t byte_length;
    void *data;
    unsigned char id;
} WavpackMetadata;

/* src/wavpack_local.h WavpackContext -- the four verbatim member-declaration
 * lines carrying every field read_new_config_info accesses (config,
 * version_five, file_format, channel_reordering, channel_layout). The full
 * struct also holds the stream/reader/tag machinery, none of which this
 * function references, so only the real declarations it needs are kept. */
typedef struct {
    WavpackConfig config;
    int wvc_flag, open_flags, norm_offset, reduced_channels, lossy_blocks, version_five;
    unsigned char file_format, *channel_reordering, *channel_identities;
    uint32_t channel_layout, dsd_multiplier;
} WavpackContext;

/* ================= TARGET FUNCTION (verbatim, next) ================= */
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

/* Call the target through a volatile function pointer so the -O1 optimizer
 * cannot inline the static function into main -- this keeps read_new_config_info
 * as its own frame in the ASAN backtrace (the target-in-stack check). */
static int (*volatile call_target)(WavpackContext *, WavpackMetadata *) = read_new_config_info;

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 64; }

    /* slurp the whole input into a heap buffer */
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 64; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }
    unsigned char *raw = (unsigned char *)malloc((size_t)fsz + 1);
    if (!raw) { fclose(fp); return 64; }
    size_t got = fread(raw, 1, (size_t)fsz, fp);
    fclose(fp);

    /* raw[0] -> declared byte_length; the rest -> the metadata data bytes */
    int32_t byte_length = (got >= 1) ? (int32_t)raw[0] : 0;

    /* EXACT real footprint from read_metadata_buff (open_utils.c:686):
     * reserve byte_length + (byte_length & 1) bytes for wpmd->data. Heap-alloc
     * it (malloc) so the over-read is ASAN-visible; never a stack/static array. */
    size_t data_alloc = (size_t)byte_length + (size_t)(byte_length & 1);
    unsigned char *data = (unsigned char *)malloc(data_alloc ? data_alloc : 1);
    if (!data) { free(raw); return 64; }
    /* copy up to data_alloc data bytes from raw[1..], zero-pad the remainder */
    for (size_t i = 0; i < data_alloc; ++i)
        data[i] = (1 + i < got) ? raw[1 + i] : 0;

    WavpackContext wpc;
    memset(&wpc, 0, sizeof wpc);      /* channel_reordering = NULL etc. */
    WavpackMetadata wpmd;
    memset(&wpmd, 0, sizeof wpmd);
    wpmd.byte_length = byte_length;
    wpmd.data = data;

    int rv = call_target(&wpc, &wpmd);
    (void)rv;

    if (wpc.channel_reordering) free(wpc.channel_reordering);
    free(data);
    free(raw);
    return 0;
}

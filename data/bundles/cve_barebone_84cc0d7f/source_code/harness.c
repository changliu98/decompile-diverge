/* cve_barebone direct-call harness for CVE-2019-15296 (faad2)
 * Target: faad_resetbits  (libfaad/bits.c)
 * Bug class: CWE-125 heap-buffer-overflow READ.
 *
 * See scripts/gen_dc_cve_84cc0d7f.py for the full bug writeup. In short: faad_resetbits's own
 * `ld->bytes_left = ld->buffer_size - words*4;` (both uint32_t) underflows to a huge value
 * whenever `words*4 > ld->buffer_size` (`words` derived from the function's own unchecked
 * `bits` argument), which makes the immediately-following `if (ld->bytes_left >= 4)` take the
 * "read a full dword" branch and call `getdword(&ld->start[words])` -- 4 bytes at an offset
 * already past the `ld->start` allocation.
 *
 * Build: clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real struct (VERBATIM, libfaad/bits.h) ---- */
typedef struct _bitfile
{
    /* bit input */
    uint32_t bufa;
    uint32_t bufb;
    uint32_t bits_left;
    uint32_t buffer_size; /* size of the buffer in bytes */
    uint32_t bytes_left;
    uint8_t error;
    uint32_t *tail;
    uint32_t *start;
    const void *buffer;
} bitfile;

/* ---- real crash-path callees (VERBATIM, libfaad/bits.h; INLINE -> inline, see header
 * comment above -- a macro-expansion, the bodies are untouched) ---- */

/* circumvent memory alignment errors on ARM */
static inline uint32_t getdword(void *mem)
{
    uint32_t tmp;
    ((uint8_t*)&tmp)[0] = ((uint8_t*)mem)[3];
    ((uint8_t*)&tmp)[1] = ((uint8_t*)mem)[2];
    ((uint8_t*)&tmp)[2] = ((uint8_t*)mem)[1];
    ((uint8_t*)&tmp)[3] = ((uint8_t*)mem)[0];

    return tmp;
}

/* reads only n bytes from the stream instead of the standard 4 */
static uint32_t getdword_n(void *mem, int n)
{
    uint32_t tmp = 0;
    switch (n)
    {
    case 3:
        ((uint8_t*)&tmp)[1] = ((uint8_t*)mem)[2];
    case 2:
        ((uint8_t*)&tmp)[2] = ((uint8_t*)mem)[1];
    case 1:
        ((uint8_t*)&tmp)[3] = ((uint8_t*)mem)[0];
    default:
        break;
    }

    return tmp;
}

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_84cc0d7f/target/original_function.c */
/* ======================================================================================== */
void faad_resetbits(bitfile *ld, int bits)
{
    uint32_t tmp;
    int words = bits >> 5;
    int remainder = bits & 0x1F;

    ld->bytes_left = ld->buffer_size - words*4;

    if (ld->bytes_left >= 4)
    {
        tmp = getdword(&ld->start[words]);
        ld->bytes_left -= 4;
    } else {
        tmp = getdword_n(&ld->start[words], ld->bytes_left);
        ld->bytes_left = 0;
    }
    ld->bufa = tmp;

    if (ld->bytes_left >= 4)
    {
        tmp = getdword(&ld->start[words+1]);
        ld->bytes_left -= 4;
    } else {
        tmp = getdword_n(&ld->start[words+1], ld->bytes_left);
        ld->bytes_left = 0;
    }
    ld->bufb = tmp;

    ld->bits_left = 32 - remainder;
    ld->tail = &ld->start[words+2];

    /* recheck for reading too many bytes */
    ld->error = 0;
//    if (ld->bytes_left == 0)
//        ld->no_more_reading = 1;
//    if (ld->bytes_left < 0)
//        ld->error = 1;
}
/* ==== end verbatim target function ==== */

/* ---- driver ---------------------------------------------------------------------------
 * argv[1] is read whole into a HEAP buffer (ASAN-guarded). The first 4 bytes decode
 * (native/little-endian on this x86-64 build) as `bits` -- faad_resetbits's own unchecked
 * `int bits` parameter (in the real decoder, a bitstream-derived bit position, e.g.
 * sbr_syntax.c: `faad_resetbits(ld, num_sbr_bits1 + 8*cnt)`). The remaining bytes become a
 * SEPARATE heap allocation playing the role of the real `ld->start`/`ld->buffer` byte buffer
 * (what faad_initbits() would have pointed `start` at), with `ld->buffer_size` set to its
 * REAL size -- the bug is a mismatch between that real size and the attacker-chosen `bits`,
 * not a lie about the size. */
int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long flen = ftell(f);
    if (flen < 4) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    unsigned char *filebuf = (unsigned char *)malloc((size_t)flen);
    if (!filebuf) { fclose(f); return 0; }
    size_t got = fread(filebuf, 1, (size_t)flen, f);
    fclose(f);
    if (got != (size_t)flen) { free(filebuf); return 0; }

    int32_t bits;
    memcpy(&bits, filebuf, 4);

    size_t buffer_size = (size_t)flen - 4;
    unsigned char *heapbuf = (unsigned char *)malloc(buffer_size);
    if (!heapbuf) { free(filebuf); return 0; }
    if (buffer_size) memcpy(heapbuf, filebuf + 4, buffer_size);
    free(filebuf);

    bitfile ld;
    memset(&ld, 0, sizeof(ld));
    ld.buffer = heapbuf;
    ld.start = (uint32_t *)heapbuf;
    ld.buffer_size = (uint32_t)buffer_size;   /* the REAL size of the ld->start allocation */

    faad_resetbits(&ld, (int)bits);

    /* Only reached on a SAFE input -- a triggering input aborts inside
     * faad_resetbits/getdword above. Touch the outputs so the call can't be optimized away. */
    volatile uint32_t sink = ld.bufa ^ ld.bufb ^ ld.bits_left ^ ld.bytes_left;
    (void)sink;

    free(heapbuf);
    return 0;
}

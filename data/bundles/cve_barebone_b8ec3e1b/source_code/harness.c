/* Direct-call harness for cve_b8ec3e1b (ffmpeg, libavcodec/xpmdec.c,
 * xpm_decode_frame).
 *
 * Fix commit cb243972b121b1ae6b60a78ff55a0506c69f3879 bundles several XPM
 * decoder hardening fixes. The one this harness reproduces is the very
 * first hunk touching xpm_decode_frame's own body:
 *
 *   -    end = avpkt->data + avpkt->size;
 *   -    while (memcmp(ptr, SIGNATURE, 9) && ptr < end - 9)
 *   +    ... (copies avpkt->data into a padded, NUL-terminated x->buf first)
 *   +    while (end - ptr > 9 && memcmp(ptr, SIGNATURE, 9))
 *   (SIGNATURE = the 9-byte XPM magic comment; see the memcmp call in
 *   xpm_decode_frame's own body below for its exact literal bytes)
 *
 * In the VULNERABLE code (reproduced verbatim below), the while-loop
 * condition is `memcmp(...) && ptr < end - 9` -- because && evaluates its
 * LEFT operand first, `memcmp(ptr, SIGNATURE, 9)` always executes BEFORE
 * the bounds check `ptr < end - 9`, on every iteration including the very
 * first. When avpkt->size < 9, ptr (== avpkt->data == end - avpkt->size)
 * is only avpkt->size bytes long, so this unconditional memcmp reads
 * (9 - avpkt->size) bytes past the end of the allocation on the FIRST
 * check, before the loop body ever runs and before any other line of the
 * function executes. This is a heap-buffer-overflow READ (CWE-125),
 * reachable by calling xpm_decode_frame() directly with any packet whose
 * size is 1..8 bytes -- no valid XPM header, dimensions, or color table
 * needed at all. The fix's reordering (`end - ptr > 9 && memcmp(...)`)
 * checks the bound FIRST, closing exactly this hole.
 *
 * xpm_decode_frame() below (through its closing brace) is pasted
 * BYTE-FOR-BYTE from target/original_function.c -- no edits.
 *
 * Supporting real callees (mod_strcspn, ascii2index, color_string_to_rgba,
 * hex_char_to_number, color_table_compare, color_table[]) are pure,
 * framework-free functions copied verbatim from source_code's
 * libavcodec/xpmdec.c so the file compiles; they are never exercised by
 * the triggering inputs (execution returns at the very first check) but
 * are needed for a complete, faithful, self-contained translation unit.
 * AVCodecContext/AVFrame/AVPacket/XPMDecContext carry only the fields
 * xpm_decode_frame's own body touches. av_log/ff_set_dimensions/
 * ff_get_buffer/av_fast_padded_malloc/av_strcasecmp are minimal faithful
 * stubs of the real FFmpeg API surface (logging is a no-op; the buffer
 * helpers allocate/validate the way the real ones do) -- none of them run
 * on the triggering path.
 *
 * main() reads argv[1] into a HEAP buffer (malloc'd to the EXACT file
 * size, no padding/NUL added -- this is essential: it is precisely what
 * lets the unconditional memcmp read past the allocation for short
 * inputs) and calls xpm_decode_frame() exactly once with it as the
 * AVPacket payload.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <strings.h>
#include <errno.h>

/* ---- minimal FFmpeg types: only the fields xpm_decode_frame touches ---- */

typedef struct AVFrame {
    uint8_t *data[8];
    int      linesize[8];
    int      key_frame;
    int      pict_type;
} AVFrame;

typedef struct AVPacket {
    uint8_t *data;
    int      size;
} AVPacket;

typedef struct XPMContext {
    uint32_t  *pixels;
    int        pixels_size;
} XPMDecContext;

typedef struct AVCodecContext {
    void *priv_data;
    int   pix_fmt;
    int   width;
    int   height;
} AVCodecContext;

/* ---- constants xpm_decode_frame references ---- */
#define AVERROR(e)          (-(e))
#define AVERROR_INVALIDDATA  (-1094995529)   /* real FFmpeg value, MKTAG-based */
#define AV_LOG_ERROR          16
#define AV_PIX_FMT_BGRA        1
#define AV_PICTURE_TYPE_I       1
#define AV_INPUT_BUFFER_PADDING_SIZE 64
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

/* ---- minimal faithful stubs of the FFmpeg API surface ---- */

static void av_log(void *avcl, int level, const char *fmt, ...)
{
    (void)avcl; (void)level; (void)fmt;
    /* logging is not memory-safety relevant; no-op */
}

static int av_strcasecmp(const char *a, const char *b)
{
    return strcasecmp(a, b);
}

static int ff_set_dimensions(AVCodecContext *avctx, int w, int h)
{
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096)
        return AVERROR(EINVAL);
    avctx->width = w;
    avctx->height = h;
    return 0;
}

static int ff_get_buffer(AVCodecContext *avctx, AVFrame *frame, int flags)
{
    size_t linesize, total;
    (void)flags;
    if (avctx->width <= 0 || avctx->height <= 0)
        return AVERROR(EINVAL);
    linesize = (size_t)avctx->width * 4;
    total = linesize * (size_t)avctx->height;
    frame->data[0] = (uint8_t *)malloc(total ? total : 1);
    if (!frame->data[0])
        return AVERROR(ENOMEM);
    memset(frame->data[0], 0, total);
    frame->linesize[0] = (int)linesize;
    return 0;
}

static void av_fast_padded_malloc(void *ptr, int *size, int64_t min_size)
{
    uint8_t **p = (uint8_t **)ptr;
    size_t alloc_size;
    free(*p);
    *p = NULL;
    *size = 0;
    if (min_size < 0)
        return;
    alloc_size = (size_t)min_size + AV_INPUT_BUFFER_PADDING_SIZE;
    *p = (uint8_t *)malloc(alloc_size);
    if (*p) {
        memset(*p, 0, alloc_size);
        *size = (int)alloc_size;
    }
}

/* =====================================================================
 * Everything below through the end of xpm_decode_frame is copied
 * VERBATIM from source_code/libavcodec/xpmdec.c (real names/logic
 * unchanged).
 * ===================================================================== */

typedef struct ColorEntry {
    const char *name;         ///< a string representing the name of the color
    uint32_t    rgb_color;    ///< RGB values for the color
} ColorEntry;

static int color_table_compare(const void *lhs, const void *rhs)
{
    return av_strcasecmp(lhs, ((const ColorEntry *)rhs)->name);
}

static const ColorEntry color_table[] = {
    { "AliceBlue",            0xFFF0F8FF },
    { "AntiqueWhite",         0xFFFAEBD7 },
    { "Aqua",                 0xFF00FFFF },
    { "Aquamarine",           0xFF7FFFD4 },
    { "Azure",                0xFFF0FFFF },
    { "Beige",                0xFFF5F5DC },
    { "Bisque",               0xFFFFE4C4 },
    { "Black",                0xFF000000 },
    { "BlanchedAlmond",       0xFFFFEBCD },
    { "Blue",                 0xFF0000FF },
    { "BlueViolet",           0xFF8A2BE2 },
    { "Brown",                0xFFA52A2A },
    { "BurlyWood",            0xFFDEB887 },
    { "CadetBlue",            0xFF5F9EA0 },
    { "Chartreuse",           0xFF7FFF00 },
    { "Chocolate",            0xFFD2691E },
    { "Coral",                0xFFFF7F50 },
    { "CornflowerBlue",       0xFF6495ED },
    { "Cornsilk",             0xFFFFF8DC },
    { "Crimson",              0xFFDC143C },
    { "Cyan",                 0xFF00FFFF },
    { "DarkBlue",             0xFF00008B },
    { "DarkCyan",             0xFF008B8B },
    { "DarkGoldenRod",        0xFFB8860B },
    { "DarkGray",             0xFFA9A9A9 },
    { "DarkGreen",            0xFF006400 },
    { "DarkKhaki",            0xFFBDB76B },
    { "DarkMagenta",          0xFF8B008B },
    { "DarkOliveGreen",       0xFF556B2F },
    { "Darkorange",           0xFFFF8C00 },
    { "DarkOrchid",           0xFF9932CC },
    { "DarkRed",              0xFF8B0000 },
    { "DarkSalmon",           0xFFE9967A },
    { "DarkSeaGreen",         0xFF8FBC8F },
    { "DarkSlateBlue",        0xFF483D8B },
    { "DarkSlateGray",        0xFF2F4F4F },
    { "DarkTurquoise",        0xFF00CED1 },
    { "DarkViolet",           0xFF9400D3 },
    { "DeepPink",             0xFFFF1493 },
    { "DeepSkyBlue",          0xFF00BFFF },
    { "DimGray",              0xFF696969 },
    { "DodgerBlue",           0xFF1E90FF },
    { "FireBrick",            0xFFB22222 },
    { "FloralWhite",          0xFFFFFAF0 },
    { "ForestGreen",          0xFF228B22 },
    { "Fuchsia",              0xFFFF00FF },
    { "Gainsboro",            0xFFDCDCDC },
    { "GhostWhite",           0xFFF8F8FF },
    { "Gold",                 0xFFFFD700 },
    { "GoldenRod",            0xFFDAA520 },
    { "Gray",                 0xFFBEBEBE },
    { "Green",                0xFF00FF00 },
    { "GreenYellow",          0xFFADFF2F },
    { "HoneyDew",             0xFFF0FFF0 },
    { "HotPink",              0xFFFF69B4 },
    { "IndianRed",            0xFFCD5C5C },
    { "Indigo",               0xFF4B0082 },
    { "Ivory",                0xFFFFFFF0 },
    { "Khaki",                0xFFF0E68C },
    { "Lavender",             0xFFE6E6FA },
    { "LavenderBlush",        0xFFFFF0F5 },
    { "LawnGreen",            0xFF7CFC00 },
    { "LemonChiffon",         0xFFFFFACD },
    { "LightBlue",            0xFFADD8E6 },
    { "LightCoral",           0xFFF08080 },
    { "LightCyan",            0xFFE0FFFF },
    { "LightGoldenRodYellow", 0xFFFAFAD2 },
    { "LightGreen",           0xFF90EE90 },
    { "LightGrey",            0xFFD3D3D3 },
    { "LightPink",            0xFFFFB6C1 },
    { "LightSalmon",          0xFFFFA07A },
    { "LightSeaGreen",        0xFF20B2AA },
    { "LightSkyBlue",         0xFF87CEFA },
    { "LightSlateGray",       0xFF778899 },
    { "LightSteelBlue",       0xFFB0C4DE },
    { "LightYellow",          0xFFFFFFE0 },
    { "Lime",                 0xFF00FF00 },
    { "LimeGreen",            0xFF32CD32 },
    { "Linen",                0xFFFAF0E6 },
    { "Magenta",              0xFFFF00FF },
    { "Maroon",               0xFFB03060 },
    { "MediumAquaMarine",     0xFF66CDAA },
    { "MediumBlue",           0xFF0000CD },
    { "MediumOrchid",         0xFFBA55D3 },
    { "MediumPurple",         0xFF9370D8 },
    { "MediumSeaGreen",       0xFF3CB371 },
    { "MediumSlateBlue",      0xFF7B68EE },
    { "MediumSpringGreen",    0xFF00FA9A },
    { "MediumTurquoise",      0xFF48D1CC },
    { "MediumVioletRed",      0xFFC71585 },
    { "MidnightBlue",         0xFF191970 },
    { "MintCream",            0xFFF5FFFA },
    { "MistyRose",            0xFFFFE4E1 },
    { "Moccasin",             0xFFFFE4B5 },
    { "NavajoWhite",          0xFFFFDEAD },
    { "Navy",                 0xFF000080 },
    { "None",                 0x00000000 },
    { "OldLace",              0xFFFDF5E6 },
    { "Olive",                0xFF808000 },
    { "OliveDrab",            0xFF6B8E23 },
    { "Orange",               0xFFFFA500 },
    { "OrangeRed",            0xFFFF4500 },
    { "Orchid",               0xFFDA70D6 },
    { "PaleGoldenRod",        0xFFEEE8AA },
    { "PaleGreen",            0xFF98FB98 },
    { "PaleTurquoise",        0xFFAFEEEE },
    { "PaleVioletRed",        0xFFD87093 },
    { "PapayaWhip",           0xFFFFEFD5 },
    { "PeachPuff",            0xFFFFDAB9 },
    { "Peru",                 0xFFCD853F },
    { "Pink",                 0xFFFFC0CB },
    { "Plum",                 0xFFDDA0DD },
    { "PowderBlue",           0xFFB0E0E6 },
    { "Purple",               0xFFA020F0 },
    { "Red",                  0xFFFF0000 },
    { "RosyBrown",            0xFFBC8F8F },
    { "RoyalBlue",            0xFF4169E1 },
    { "SaddleBrown",          0xFF8B4513 },
    { "Salmon",               0xFFFA8072 },
    { "SandyBrown",           0xFFF4A460 },
    { "SeaGreen",             0xFF2E8B57 },
    { "SeaShell",             0xFFFFF5EE },
    { "Sienna",               0xFFA0522D },
    { "Silver",               0xFFC0C0C0 },
    { "SkyBlue",              0xFF87CEEB },
    { "SlateBlue",            0xFF6A5ACD },
    { "SlateGray",            0xFF708090 },
    { "Snow",                 0xFFFFFAFA },
    { "SpringGreen",          0xFF00FF7F },
    { "SteelBlue",            0xFF4682B4 },
    { "Tan",                  0xFFD2B48C },
    { "Teal",                 0xFF008080 },
    { "Thistle",              0xFFD8BFD8 },
    { "Tomato",               0xFFFF6347 },
    { "Turquoise",            0xFF40E0D0 },
    { "Violet",               0xFFEE82EE },
    { "Wheat",                0xFFF5DEB3 },
    { "White",                0xFFFFFFFF },
    { "WhiteSmoke",           0xFFF5F5F5 },
    { "Yellow",               0xFFFFFF00 },
    { "YellowGreen",          0xFF9ACD32 }
};

static unsigned hex_char_to_number(uint8_t x)
{
    if (x >= 'a' && x <= 'f')
        x -= 'a' - 10;
    else if (x >= 'A' && x <= 'F')
        x -= 'A' - 10;
    else if (x >= '0' && x <= '9')
        x -= '0';
    else
        x = 0;
    return x;
}

/*
 * Function same as strcspn but ignores characters if they are inside a C style comments
 */
static size_t mod_strcspn(const char *string, const char *reject)
{
    int i, j;

    for (i = 0; string && string[i]; i++) {
        if (string[i] == '/' && string[i+1] == '*') {
            i += 2;
            while ( string && string[i] && (string[i] != '*' || string[i+1] != '/') )
                i++;
            i++;
        } else if (string[i] == '/' && string[i+1] == '/') {
            i += 2;
            while ( string && string[i] && string[i] != '\n' )
                i++;
        } else {
            for (j = 0; reject && reject[j]; j++) {
                if (string[i] == reject[j])
                    break;
            }
            if (reject && reject[j])
                break;
        }
    }
    return i;
}

static uint32_t color_string_to_rgba(const char *p, int len)
{
    uint32_t ret = 0xFF000000;
    const ColorEntry *entry;
    char color_name[100];

    if (*p == '#') {
        p++;
        len--;
        if (len == 3) {
            ret |= (hex_char_to_number(p[2]) <<  4) |
                   (hex_char_to_number(p[1]) << 12) |
                   (hex_char_to_number(p[0]) << 20);
        } else if (len == 4) {
            ret  = (hex_char_to_number(p[3]) <<  4) |
                   (hex_char_to_number(p[2]) << 12) |
                   (hex_char_to_number(p[1]) << 20) |
                   (hex_char_to_number(p[0]) << 28);
        } else if (len == 6) {
            ret |=  hex_char_to_number(p[5])        |
                   (hex_char_to_number(p[4]) <<  4) |
                   (hex_char_to_number(p[3]) <<  8) |
                   (hex_char_to_number(p[2]) << 12) |
                   (hex_char_to_number(p[1]) << 16) |
                   (hex_char_to_number(p[0]) << 20);
        } else if (len == 8) {
            ret  =  hex_char_to_number(p[7])        |
                   (hex_char_to_number(p[6]) <<  4) |
                   (hex_char_to_number(p[5]) <<  8) |
                   (hex_char_to_number(p[4]) << 12) |
                   (hex_char_to_number(p[3]) << 16) |
                   (hex_char_to_number(p[2]) << 20) |
                   (hex_char_to_number(p[1]) << 24) |
                   (hex_char_to_number(p[0]) << 28);
        }
    } else {
        strncpy(color_name, p, len);
        color_name[len] = '\0';

        entry = bsearch(color_name,
                        color_table,
                        FF_ARRAY_ELEMS(color_table),
                        sizeof(ColorEntry),
                        color_table_compare);

        if (!entry)
            return ret;

        ret = entry->rgb_color;
    }
    return ret;
}

static int ascii2index(const uint8_t *cpixel, int cpp)
{
    const uint8_t *p = cpixel;
    int n = 0, m = 1, i;

    for (i = 0; i < cpp; i++) {
        if (*p < ' ' || *p > '~')
            return AVERROR_INVALIDDATA;
        n += (*p++ - ' ') * m;
        m *= 95;
    }
    return n;
}

static int xpm_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame, AVPacket *avpkt)
{
    XPMDecContext *x = avctx->priv_data;
    AVFrame *p=data;
    const uint8_t *end, *ptr = avpkt->data;
    int ncolors, cpp, ret, i, j;
    int64_t size;
    uint32_t *dst;

    avctx->pix_fmt = AV_PIX_FMT_BGRA;

    end = avpkt->data + avpkt->size;
    while (memcmp(ptr, "/* XPM */", 9) && ptr < end - 9)
        ptr++;

    if (ptr >= end) {
        av_log(avctx, AV_LOG_ERROR, "missing signature\n");
        return AVERROR_INVALIDDATA;
    }

    ptr += mod_strcspn(ptr, "\"");
    if (sscanf(ptr, "\"%u %u %u %u\",",
               &avctx->width, &avctx->height, &ncolors, &cpp) != 4) {
        av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_set_dimensions(avctx, avctx->width, avctx->height)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;

    if (cpp <= 0 || cpp >= 5) {
        av_log(avctx, AV_LOG_ERROR, "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return AVERROR_INVALIDDATA;
    }

    size = 1;
    for (i = 0; i < cpp; i++)
        size *= 94;

    if (ncolors <= 0 || ncolors > size) {
        av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);
        return AVERROR_INVALIDDATA;
    }

    size *= 4;

    av_fast_padded_malloc(&x->pixels, &x->pixels_size, size);
    if (!x->pixels)
        return AVERROR(ENOMEM);

    ptr += mod_strcspn(ptr, ",") + 1;
    for (i = 0; i < ncolors; i++) {
        const uint8_t *index;
        int len;

        ptr += mod_strcspn(ptr, "\"") + 1;
        if (ptr + cpp > end)
            return AVERROR_INVALIDDATA;
        index = ptr;
        ptr += cpp;

        ptr = strstr(ptr, "c ");
        if (ptr) {
            ptr += 2;
        } else {
            return AVERROR_INVALIDDATA;
        }

        len = strcspn(ptr, "\" ");

        if ((ret = ascii2index(index, cpp)) < 0)
            return ret;

        x->pixels[ret] = color_string_to_rgba(ptr, len);
        ptr += mod_strcspn(ptr, ",") + 1;
    }

    for (i = 0; i < avctx->height; i++) {
        dst = (uint32_t *)(p->data[0] + i * p->linesize[0]);
        ptr += mod_strcspn(ptr, "\"") + 1;

        for (j = 0; j < avctx->width; j++) {
            if (ptr + cpp > end)
                return AVERROR_INVALIDDATA;

            if ((ret = ascii2index(ptr, cpp)) < 0)
                return ret;

            *dst++ = x->pixels[ret];
            ptr += cpp;
        }
        ptr += mod_strcspn(ptr, ",") + 1;
    }

    p->key_frame = 1;
    p->pict_type = AV_PICTURE_TYPE_I;

    *got_frame = 1;

    return avpkt->size;
}

/* =====================================================================
 * Harness main(): reads argv[1] into a HEAP buffer at EXACTLY the file's
 * size (no padding, no NUL terminator added -- the vulnerable code path
 * requires this) and calls xpm_decode_frame() exactly once with it as
 * the AVPacket payload.
 * ===================================================================== */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 0; }
    rewind(f);

    /* Heap-allocate EXACTLY fsz bytes -- ASAN can only catch out-of-bounds
     * accesses on heap allocations, and only if the allocation is not
     * over-sized/padded past what the file actually contains. */
    uint8_t *raw = (uint8_t *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
    if (!raw) { fclose(f); return 1; }
    size_t n = (fsz > 0) ? fread(raw, 1, (size_t)fsz, f) : 0;
    fclose(f);

    AVCodecContext avctx;
    memset(&avctx, 0, sizeof(avctx));
    XPMDecContext xctx;
    memset(&xctx, 0, sizeof(xctx));
    avctx.priv_data = &xctx;

    AVFrame frame;
    memset(&frame, 0, sizeof(frame));

    AVPacket pkt;
    pkt.data = raw;
    pkt.size = (int)n;

    int got_frame = 0;
    int rc = xpm_decode_frame(&avctx, &frame, &got_frame, &pkt);
    (void)rc;

    free(frame.data[0]);
    free(xctx.pixels);
    free(raw);
    return 0;
}

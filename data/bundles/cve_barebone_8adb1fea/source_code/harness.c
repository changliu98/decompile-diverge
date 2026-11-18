/*
 * cve_8adb1fea direct-call harness for CVE-2022-0629 (vim ga_concat_shorten_esc).
 *
 * Standalone repro: ga_concat_shorten_esc (src/testing.c, vulnerable commit
 * f5288c589500de0677444af4a428cfbccfccb8ce) computes "clen" for the current character via
 * mb_ptr2char_adv(), which (for enc_utf8) advances by utfc_ptr2len() -- the length of the
 * base character PLUS every following Unicode composing character, with NO upper bound.
 * clen is then passed straight to ga_concat_esc(), which does
 *
 *     char_u buf[NUMBUFLEN];             // NUMBUFLEN == 65, src/vim.h
 *     mch_memmove(buf, p, clen);
 *     buf[clen] = NUL;
 *
 * so a single base character followed by enough composing marks (clen > 65) overflows the
 * 65-byte stack buffer. Fixed in 34f8117dec685ace52cd9e578e2729db278163fc by switching to
 * mb_cptr2char_adv(), which advances by just the base character's own length and treats
 * composing characters as separate "characters" (so clen stays 1-4 there).
 *
 * Every function below is copied byte-for-byte from
 * data_cve/cve_8adb1fea/source_code/src/{mbyte.c,alloc.c,testing.c} at the vulnerable
 * commit (function bodies unedited; only file-scope ordering and the surrounding
 * scaffolding -- typedefs, the growarray struct, thin libc wrappers for
 * mch_memmove/vim_realloc/vim_memset/vim_snprintf, and the mb_ptr2char/mb_ptr2len
 * function-pointer globals that mb_init() would normally set up for 'encoding' ==
 * "utf-8" -- are added so the file links standalone with -lm).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ---- real vim type/macro defs (verbatim values, src/vim.h + src/ascii.h + src/structs.h) ---- */
typedef unsigned char char_u;

#define NUL	'\000'
#define BS	'\010'
#define TAB	'\011'
#define NL	'\012'
#define FF	'\014'
#define CAR	'\015'
#define ESC	'\033'

#define OK	1
#define FAIL	0
#define TRUE	1
#define FALSE	0

#define NUMBUFLEN 65

#define STRLEN(s)	    strlen((char *)(s))

typedef struct growarray
{
    int	    ga_len;		    // current number of items used
    int	    ga_maxlen;		    // maximum number of items possible
    int	    ga_itemsize;	    // sizeof(item)
    int	    ga_growsize;	    // number of items to grow each time
    void    *ga_data;		    // pointer to the first item
} garray_T;

/* ---- incidental helpers (not on the crash path): thin libc wrappers standing in for
 * vim's os-layer alloc/format functions, matching their real semantics exactly ---- */
#define mch_memmove(to, from, len) memmove((char*)(to), (char*)(from), (size_t)(len))

    static void *
vim_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

    static void
vim_memset(void *ptr, int val, size_t size)
{
    memset(ptr, val, size);
}

    static int
vim_snprintf(char *str, size_t str_m, const char *fmt, ...)
{
    va_list ap;
    int	    result;

    va_start(ap, fmt);
    result = vsnprintf(str, str_m, fmt, ap);
    va_end(ap);
    return result;
}

static char utf8len_tab[256] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1,
};

static char utf8len_tab_zero[256] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,0,0,
};

    int
utf_ptr2char(char_u *p)
{
    int		len;

    if (p[0] < 0x80)	// be quick for ASCII
	return p[0];

    len = utf8len_tab_zero[p[0]];
    if (len > 1 && (p[1] & 0xc0) == 0x80)
    {
	if (len == 2)
	    return ((p[0] & 0x1f) << 6) + (p[1] & 0x3f);
	if ((p[2] & 0xc0) == 0x80)
	{
	    if (len == 3)
		return ((p[0] & 0x0f) << 12) + ((p[1] & 0x3f) << 6)
		    + (p[2] & 0x3f);
	    if ((p[3] & 0xc0) == 0x80)
	    {
		if (len == 4)
		    return ((p[0] & 0x07) << 18) + ((p[1] & 0x3f) << 12)
			+ ((p[2] & 0x3f) << 6) + (p[3] & 0x3f);
		if ((p[4] & 0xc0) == 0x80)
		{
		    if (len == 5)
			return ((p[0] & 0x03) << 24) + ((p[1] & 0x3f) << 18)
			    + ((p[2] & 0x3f) << 12) + ((p[3] & 0x3f) << 6)
			    + (p[4] & 0x3f);
		    if ((p[5] & 0xc0) == 0x80 && len == 6)
			return ((p[0] & 0x01) << 30) + ((p[1] & 0x3f) << 24)
			    + ((p[2] & 0x3f) << 18) + ((p[3] & 0x3f) << 12)
			    + ((p[4] & 0x3f) << 6) + (p[5] & 0x3f);
		}
	    }
	}
    }
    // Illegal value, just return the first byte
    return p[0];
}

    int
utf_ptr2len(char_u *p)
{
    int		len;
    int		i;

    if (*p == NUL)
	return 0;
    len = utf8len_tab[*p];
    for (i = 1; i < len; ++i)
	if ((p[i] & 0xc0) != 0x80)
	    return 1;
    return len;
}

struct interval
{
    long first;
    long last;
};

    static int
intable(struct interval *table, size_t size, int c)
{
    int mid, bot, top;

    // first quick check for Latin1 etc. characters
    if (c < table[0].first)
	return FALSE;

    // binary search in table
    bot = 0;
    top = (int)(size / sizeof(struct interval) - 1);
    while (top >= bot)
    {
	mid = (bot + top) / 2;
	if (table[mid].last < c)
	    bot = mid + 1;
	else if (table[mid].first > c)
	    top = mid - 1;
	else
	    return TRUE;
    }
    return FALSE;
}

    int
utf_iscomposing(int c)
{
    // Sorted list of non-overlapping intervals.
    // Generated by ../runtime/tools/unicode.vim.
    static struct interval combining[] =
    {
	{0x0300, 0x036f},
	{0x0483, 0x0489},
	{0x0591, 0x05bd},
	{0x05bf, 0x05bf},
	{0x05c1, 0x05c2},
	{0x05c4, 0x05c5},
	{0x05c7, 0x05c7},
	{0x0610, 0x061a},
	{0x064b, 0x065f},
	{0x0670, 0x0670},
	{0x06d6, 0x06dc},
	{0x06df, 0x06e4},
	{0x06e7, 0x06e8},
	{0x06ea, 0x06ed},
	{0x0711, 0x0711},
	{0x0730, 0x074a},
	{0x07a6, 0x07b0},
	{0x07eb, 0x07f3},
	{0x07fd, 0x07fd},
	{0x0816, 0x0819},
	{0x081b, 0x0823},
	{0x0825, 0x0827},
	{0x0829, 0x082d},
	{0x0859, 0x085b},
	{0x08d3, 0x08e1},
	{0x08e3, 0x0903},
	{0x093a, 0x093c},
	{0x093e, 0x094f},
	{0x0951, 0x0957},
	{0x0962, 0x0963},
	{0x0981, 0x0983},
	{0x09bc, 0x09bc},
	{0x09be, 0x09c4},
	{0x09c7, 0x09c8},
	{0x09cb, 0x09cd},
	{0x09d7, 0x09d7},
	{0x09e2, 0x09e3},
	{0x09fe, 0x09fe},
	{0x0a01, 0x0a03},
	{0x0a3c, 0x0a3c},
	{0x0a3e, 0x0a42},
	{0x0a47, 0x0a48},
	{0x0a4b, 0x0a4d},
	{0x0a51, 0x0a51},
	{0x0a70, 0x0a71},
	{0x0a75, 0x0a75},
	{0x0a81, 0x0a83},
	{0x0abc, 0x0abc},
	{0x0abe, 0x0ac5},
	{0x0ac7, 0x0ac9},
	{0x0acb, 0x0acd},
	{0x0ae2, 0x0ae3},
	{0x0afa, 0x0aff},
	{0x0b01, 0x0b03},
	{0x0b3c, 0x0b3c},
	{0x0b3e, 0x0b44},
	{0x0b47, 0x0b48},
	{0x0b4b, 0x0b4d},
	{0x0b55, 0x0b57},
	{0x0b62, 0x0b63},
	{0x0b82, 0x0b82},
	{0x0bbe, 0x0bc2},
	{0x0bc6, 0x0bc8},
	{0x0bca, 0x0bcd},
	{0x0bd7, 0x0bd7},
	{0x0c00, 0x0c04},
	{0x0c3e, 0x0c44},
	{0x0c46, 0x0c48},
	{0x0c4a, 0x0c4d},
	{0x0c55, 0x0c56},
	{0x0c62, 0x0c63},
	{0x0c81, 0x0c83},
	{0x0cbc, 0x0cbc},
	{0x0cbe, 0x0cc4},
	{0x0cc6, 0x0cc8},
	{0x0cca, 0x0ccd},
	{0x0cd5, 0x0cd6},
	{0x0ce2, 0x0ce3},
	{0x0d00, 0x0d03},
	{0x0d3b, 0x0d3c},
	{0x0d3e, 0x0d44},
	{0x0d46, 0x0d48},
	{0x0d4a, 0x0d4d},
	{0x0d57, 0x0d57},
	{0x0d62, 0x0d63},
	{0x0d81, 0x0d83},
	{0x0dca, 0x0dca},
	{0x0dcf, 0x0dd4},
	{0x0dd6, 0x0dd6},
	{0x0dd8, 0x0ddf},
	{0x0df2, 0x0df3},
	{0x0e31, 0x0e31},
	{0x0e34, 0x0e3a},
	{0x0e47, 0x0e4e},
	{0x0eb1, 0x0eb1},
	{0x0eb4, 0x0ebc},
	{0x0ec8, 0x0ecd},
	{0x0f18, 0x0f19},
	{0x0f35, 0x0f35},
	{0x0f37, 0x0f37},
	{0x0f39, 0x0f39},
	{0x0f3e, 0x0f3f},
	{0x0f71, 0x0f84},
	{0x0f86, 0x0f87},
	{0x0f8d, 0x0f97},
	{0x0f99, 0x0fbc},
	{0x0fc6, 0x0fc6},
	{0x102b, 0x103e},
	{0x1056, 0x1059},
	{0x105e, 0x1060},
	{0x1062, 0x1064},
	{0x1067, 0x106d},
	{0x1071, 0x1074},
	{0x1082, 0x108d},
	{0x108f, 0x108f},
	{0x109a, 0x109d},
	{0x135d, 0x135f},
	{0x1712, 0x1714},
	{0x1732, 0x1734},
	{0x1752, 0x1753},
	{0x1772, 0x1773},
	{0x17b4, 0x17d3},
	{0x17dd, 0x17dd},
	{0x180b, 0x180d},
	{0x1885, 0x1886},
	{0x18a9, 0x18a9},
	{0x1920, 0x192b},
	{0x1930, 0x193b},
	{0x1a17, 0x1a1b},
	{0x1a55, 0x1a5e},
	{0x1a60, 0x1a7c},
	{0x1a7f, 0x1a7f},
	{0x1ab0, 0x1ac0},
	{0x1b00, 0x1b04},
	{0x1b34, 0x1b44},
	{0x1b6b, 0x1b73},
	{0x1b80, 0x1b82},
	{0x1ba1, 0x1bad},
	{0x1be6, 0x1bf3},
	{0x1c24, 0x1c37},
	{0x1cd0, 0x1cd2},
	{0x1cd4, 0x1ce8},
	{0x1ced, 0x1ced},
	{0x1cf4, 0x1cf4},
	{0x1cf7, 0x1cf9},
	{0x1dc0, 0x1df9},
	{0x1dfb, 0x1dff},
	{0x20d0, 0x20f0},
	{0x2cef, 0x2cf1},
	{0x2d7f, 0x2d7f},
	{0x2de0, 0x2dff},
	{0x302a, 0x302f},
	{0x3099, 0x309a},
	{0xa66f, 0xa672},
	{0xa674, 0xa67d},
	{0xa69e, 0xa69f},
	{0xa6f0, 0xa6f1},
	{0xa802, 0xa802},
	{0xa806, 0xa806},
	{0xa80b, 0xa80b},
	{0xa823, 0xa827},
	{0xa82c, 0xa82c},
	{0xa880, 0xa881},
	{0xa8b4, 0xa8c5},
	{0xa8e0, 0xa8f1},
	{0xa8ff, 0xa8ff},
	{0xa926, 0xa92d},
	{0xa947, 0xa953},
	{0xa980, 0xa983},
	{0xa9b3, 0xa9c0},
	{0xa9e5, 0xa9e5},
	{0xaa29, 0xaa36},
	{0xaa43, 0xaa43},
	{0xaa4c, 0xaa4d},
	{0xaa7b, 0xaa7d},
	{0xaab0, 0xaab0},
	{0xaab2, 0xaab4},
	{0xaab7, 0xaab8},
	{0xaabe, 0xaabf},
	{0xaac1, 0xaac1},
	{0xaaeb, 0xaaef},
	{0xaaf5, 0xaaf6},
	{0xabe3, 0xabea},
	{0xabec, 0xabed},
	{0xfb1e, 0xfb1e},
	{0xfe00, 0xfe0f},
	{0xfe20, 0xfe2f},
	{0x101fd, 0x101fd},
	{0x102e0, 0x102e0},
	{0x10376, 0x1037a},
	{0x10a01, 0x10a03},
	{0x10a05, 0x10a06},
	{0x10a0c, 0x10a0f},
	{0x10a38, 0x10a3a},
	{0x10a3f, 0x10a3f},
	{0x10ae5, 0x10ae6},
	{0x10d24, 0x10d27},
	{0x10eab, 0x10eac},
	{0x10f46, 0x10f50},
	{0x11000, 0x11002},
	{0x11038, 0x11046},
	{0x1107f, 0x11082},
	{0x110b0, 0x110ba},
	{0x11100, 0x11102},
	{0x11127, 0x11134},
	{0x11145, 0x11146},
	{0x11173, 0x11173},
	{0x11180, 0x11182},
	{0x111b3, 0x111c0},
	{0x111c9, 0x111cc},
	{0x111ce, 0x111cf},
	{0x1122c, 0x11237},
	{0x1123e, 0x1123e},
	{0x112df, 0x112ea},
	{0x11300, 0x11303},
	{0x1133b, 0x1133c},
	{0x1133e, 0x11344},
	{0x11347, 0x11348},
	{0x1134b, 0x1134d},
	{0x11357, 0x11357},
	{0x11362, 0x11363},
	{0x11366, 0x1136c},
	{0x11370, 0x11374},
	{0x11435, 0x11446},
	{0x1145e, 0x1145e},
	{0x114b0, 0x114c3},
	{0x115af, 0x115b5},
	{0x115b8, 0x115c0},
	{0x115dc, 0x115dd},
	{0x11630, 0x11640},
	{0x116ab, 0x116b7},
	{0x1171d, 0x1172b},
	{0x1182c, 0x1183a},
	{0x11930, 0x11935},
	{0x11937, 0x11938},
	{0x1193b, 0x1193e},
	{0x11940, 0x11940},
	{0x11942, 0x11943},
	{0x119d1, 0x119d7},
	{0x119da, 0x119e0},
	{0x119e4, 0x119e4},
	{0x11a01, 0x11a0a},
	{0x11a33, 0x11a39},
	{0x11a3b, 0x11a3e},
	{0x11a47, 0x11a47},
	{0x11a51, 0x11a5b},
	{0x11a8a, 0x11a99},
	{0x11c2f, 0x11c36},
	{0x11c38, 0x11c3f},
	{0x11c92, 0x11ca7},
	{0x11ca9, 0x11cb6},
	{0x11d31, 0x11d36},
	{0x11d3a, 0x11d3a},
	{0x11d3c, 0x11d3d},
	{0x11d3f, 0x11d45},
	{0x11d47, 0x11d47},
	{0x11d8a, 0x11d8e},
	{0x11d90, 0x11d91},
	{0x11d93, 0x11d97},
	{0x11ef3, 0x11ef6},
	{0x16af0, 0x16af4},
	{0x16b30, 0x16b36},
	{0x16f4f, 0x16f4f},
	{0x16f51, 0x16f87},
	{0x16f8f, 0x16f92},
	{0x16fe4, 0x16fe4},
	{0x16ff0, 0x16ff1},
	{0x1bc9d, 0x1bc9e},
	{0x1d165, 0x1d169},
	{0x1d16d, 0x1d172},
	{0x1d17b, 0x1d182},
	{0x1d185, 0x1d18b},
	{0x1d1aa, 0x1d1ad},
	{0x1d242, 0x1d244},
	{0x1da00, 0x1da36},
	{0x1da3b, 0x1da6c},
	{0x1da75, 0x1da75},
	{0x1da84, 0x1da84},
	{0x1da9b, 0x1da9f},
	{0x1daa1, 0x1daaf},
	{0x1e000, 0x1e006},
	{0x1e008, 0x1e018},
	{0x1e01b, 0x1e021},
	{0x1e023, 0x1e024},
	{0x1e026, 0x1e02a},
	{0x1e130, 0x1e136},
	{0x1e2ec, 0x1e2ef},
	{0x1e8d0, 0x1e8d6},
	{0x1e944, 0x1e94a},
	{0xe0100, 0xe01ef}
    };

    return intable(combining, sizeof(combining), c);
}

/*
 * UTF_COMPOSINGLIKE (src/macros.h): the "#else" (non-FEAT_ARABIC) arm -- this harness does
 * not define FEAT_ARABIC, matching a build without Arabic support; for a genuine Unicode
 * combining character (the only kind this repro uses) utf_composinglike() would
 * short-circuit on utf_iscomposing(c2) and return the same TRUE regardless, so the two
 * arms agree for our input class.
 */
#define UTF_COMPOSINGLIKE(p1, p2)  utf_iscomposing(utf_ptr2char(p2))

    int
utfc_ptr2len(char_u *p)
{
    int		len;
    int		b0 = *p;
#ifdef FEAT_ARABIC
    int		prevlen;
#endif

    if (b0 == NUL)
	return 0;
    if (b0 < 0x80 && p[1] < 0x80)	// be quick for ASCII
	return 1;

    // Skip over first UTF-8 char, stopping at a NUL byte.
    len = utf_ptr2len(p);

    // Check for illegal byte.
    if (len == 1 && b0 >= 0x80)
	return 1;

    /*
     * Check for composing characters.  We can handle only the first six, but
     * skip all of them (otherwise the cursor would get stuck).
     */
#ifdef FEAT_ARABIC
    prevlen = 0;
#endif
    for (;;)
    {
	if (p[len] < 0x80 || !UTF_COMPOSINGLIKE(p + prevlen, p + len))
	    return len;

	// Skip over composing char
#ifdef FEAT_ARABIC
	prevlen = len;
#endif
	len += utf_ptr2len(p + len);
    }
}

/*
 * mb_ptr2char / mb_ptr2len (src/globals.h): function-pointer globals mb_init() points at
 * utf_ptr2char/utfc_ptr2len for 'encoding' == "utf-8" (the default, and what the OSS-Fuzz
 * vim harness runs with). Set directly here to the same target functions mb_init() would
 * install, without pulling in the whole option-parsing machinery.
 */
int (*mb_ptr2char)(char_u *p) = utf_ptr2char;
int (*mb_ptr2len)(char_u *p) = utfc_ptr2len;

    int
mb_ptr2char_adv(char_u **pp)
{
    int		c;

    c = (*mb_ptr2char)(*pp);
    *pp += (*mb_ptr2len)(*pp);
    return c;
}

    void
ga_init(garray_T *gap)
{
    gap->ga_data = NULL;
    gap->ga_maxlen = 0;
    gap->ga_len = 0;
}

    void
ga_init2(garray_T *gap, size_t itemsize, int growsize)
{
    ga_init(gap);
    gap->ga_itemsize = (int)itemsize;
    gap->ga_growsize = growsize;
}

    int
ga_grow_inner(garray_T *gap, int n)
{
    size_t	old_len;
    size_t	new_len;
    char_u	*pp;

    if (n < gap->ga_growsize)
	n = gap->ga_growsize;

    // A linear growth is very inefficient when the array grows big.  This
    // is a compromise between allocating memory that won't be used and too
    // many copy operations. A factor of 1.5 seems reasonable.
    if (n < gap->ga_len / 2)
	n = gap->ga_len / 2;

    new_len = (size_t)gap->ga_itemsize * (gap->ga_len + n);
    pp = vim_realloc(gap->ga_data, new_len);
    if (pp == NULL)
	return FAIL;
    old_len = (size_t)gap->ga_itemsize * gap->ga_maxlen;
    vim_memset(pp + old_len, 0, new_len - old_len);
    gap->ga_maxlen = gap->ga_len + n;
    gap->ga_data = pp;
    return OK;
}

    int
ga_grow(garray_T *gap, int n)
{
    if (gap->ga_maxlen - gap->ga_len < n)
	return ga_grow_inner(gap, n);
    return OK;
}

    void
ga_append(garray_T *gap, int c)
{
    if (ga_grow(gap, 1) == OK)
    {
	*((char *)gap->ga_data + gap->ga_len) = c;
	++gap->ga_len;
    }
}

    void
ga_concat(garray_T *gap, char_u *s)
{
    int    len;

    if (s == NULL || *s == NUL)
	return;
    len = (int)STRLEN(s);
    if (ga_grow(gap, len) == OK)
    {
	mch_memmove((char *)gap->ga_data + gap->ga_len, s, (size_t)len);
	gap->ga_len += len;
    }
}

    static void
ga_concat_esc(garray_T *gap, char_u *p, int clen)
{
    char_u  buf[NUMBUFLEN];

    if (clen > 1)
    {
	mch_memmove(buf, p, clen);
	buf[clen] = NUL;
	ga_concat(gap, buf);
    }
    else switch (*p)
    {
	case BS: ga_concat(gap, (char_u *)"\\b"); break;
	case ESC: ga_concat(gap, (char_u *)"\\e"); break;
	case FF: ga_concat(gap, (char_u *)"\\f"); break;
	case NL: ga_concat(gap, (char_u *)"\\n"); break;
	case TAB: ga_concat(gap, (char_u *)"\\t"); break;
	case CAR: ga_concat(gap, (char_u *)"\\r"); break;
	case '\\': ga_concat(gap, (char_u *)"\\\\"); break;
	default:
		   if (*p < ' ' || *p == 0x7f)
		   {
		       vim_snprintf((char *)buf, NUMBUFLEN, "\\x%02x", *p);
		       ga_concat(gap, buf);
		   }
		   else
		       ga_append(gap, *p);
		   break;
    }
}

/*
 * ---- TARGET FUNCTION, byte-for-byte from
 * data_cve/cve_8adb1fea/target/original_function.c (src/testing.c, vulnerable commit
 * f5288c589500de0677444af4a428cfbccfccb8ce) ----
 */
static void
ga_concat_shorten_esc(garray_T *gap, char_u *str)
{
    char_u  *p;
    char_u  *s;
    int	    c;
    int	    clen;
    char_u  buf[NUMBUFLEN];
    int	    same_len;

    if (str == NULL)
    {
	ga_concat(gap, (char_u *)"NULL");
	return;
    }

    for (p = str; *p != NUL; ++p)
    {
	same_len = 1;
	s = p;
	c = mb_ptr2char_adv(&s);
	clen = s - p;
	while (*s != NUL && c == mb_ptr2char(s))
	{
	    ++same_len;
	    s += clen;
	}
	if (same_len > 20)
	{
	    ga_concat(gap, (char_u *)"\\[");
	    ga_concat_esc(gap, p, clen);
	    ga_concat(gap, (char_u *)" occurs ");
	    vim_snprintf((char *)buf, NUMBUFLEN, "%d", same_len);
	    ga_concat(gap, buf);
	    ga_concat(gap, (char_u *)" times]");
	    p = s - 1;
	}
	else
	    ga_concat_esc(gap, p, clen);
    }
}

/*
 * Driver: read argv[1] into a heap buffer sized EXACTLY to the file's bytes (+1 for the NUL
 * terminator ga_concat_shorten_esc's "for (p = str; *p != NUL; ++p)" scan relies on), so an
 * ASAN heap redzone sits immediately past the data with no slack. The differential corpus
 * (io/input/*) supplies the actual trigger/safe bytes -- this driver just feeds them to
 * ga_concat_shorten_esc unmodified.
 */
    int
main(int argc, char **argv)
{
    FILE	*f;
    long	sz;
    size_t	n;
    char_u	*str;
    garray_T	ga;

    if (argc < 2)
	return 1;
    f = fopen(argv[1], "rb");
    if (f == NULL)
	return 1;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    sz = ftell(f);
    if (sz < 0) { fclose(f); return 1; }
    rewind(f);

    str = (char_u *)malloc((size_t)sz + 1);	// heap-allocated, ASAN-guarded
    if (str == NULL) { fclose(f); return 1; }
    n = fread(str, 1, (size_t)sz, f);
    fclose(f);
    str[n] = NUL;

    ga_init2(&ga, sizeof(char_u), 100);
    ga_concat_shorten_esc(&ga, str);

    free(ga.ga_data);
    free(str);
    return 0;
}

/*
 * cve_9a0c270d direct-call ASAN harness for vim's trunc_string()
 * (src/message.c, fixed by vim/vim@3bd7fa12e146c6051490d048a4acbfba974eeb04,
 * patch 8.2.1969).
 *
 * The fix changed the final "can't fit in the ..., just truncate it" branch
 * from `buf[e - 1] = NUL;` to `buf[buflen - 1] = NUL;`.  That is only a real
 * fix if `e` can exceed `buflen` -- and it can: inside the "First part" loop,
 * when `has_mbyte` is set, the inner loop
 *     for (n = (*mb_ptr2len)(s + e); --n > 0; )
 *     {
 *         if (++e == buflen)
 *             break;
 *         buf[e] = s[e];
 *     }
 * caps `e` at exactly `buflen` (it breaks *before* writing buf[buflen]), but
 * the *outer* `for (e = 0; ...; ++e)` then increments `e` again regardless of
 * whether the inner loop broke early -- so `e` becomes `buflen + 1`.  If the
 * "Last part" computation lands in the final else branch (can't fit the
 * "..."), `buf[e - 1] = NUL` writes to `buf[buflen]`: a 1-byte heap-buffer-
 * overflow WRITE (CWE-787), one byte past a buffer sized exactly `buflen`.
 *
 * This harness calls trunc_string() directly and in isolation.  It provides
 * real, faithful (verbatim where practical) implementations of the small
 * slice of vim's multibyte (UTF-8) machinery that trunc_string's own body
 * touches:
 *   - has_mbyte / enc_utf8 / enc_dbcs / mb_ptr2len  (real globals.h names)
 *   - utf8len_tab / utf8len_tab_zero / utf_ptr2len / utf_ptr2char /
 *     utf_head_off                                  (verbatim from mbyte.c)
 * `utf_iscomposing()` and `ptr2cells()` are reduced to minimal, clearly
 * documented stubs: the harness's inputs never use a genuinely composing
 * character (so `utf_iscomposing() -> 0` is factually correct, not
 * fabricated) and only ever use ordinary printable Latin-1 letters, whose
 * true vim cell width really is 1 (real vim's utf_char2cells() agrees for
 * this class of codepoint -- it is not in vim's double-width/ambiguous-width
 * tables); the illegal-byte case (`utf_ptr2len()==1`) still returns 4,
 * matching real vim exactly.  Nothing on the `e`-overflow mechanism itself
 * (the actual vulnerability) is stubbed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal vim.h substitutes (real names/definitions) ---- */
typedef unsigned char char_u;
#define NUL '\0'
#define STRLEN(s)               strlen((char *)(s))
#define mch_memmove(to, from, len) memmove((char *)(to), (char *)(from), (size_t)(len))

/* ---- real vim globals (globals.h names/types/initial values) ---- */
int enc_dbcs = 0;
int enc_utf8 = 0;
int has_mbyte = 0;
int (*mb_ptr2len)(char_u *p);

/* ============================================================
 * Verbatim from src/mbyte.c
 * ============================================================ */

/*
 * Lookup table to quickly get the length in bytes of a UTF-8 character from
 * the first byte of a UTF-8 string.
 * Bytes which are illegal when used as the first byte have a 1.
 * The NUL byte has length 1.
 */
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

/*
 * Like utf8len_tab above, but using a zero for illegal lead bytes.
 */
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

/*
 * Get the length of a UTF-8 byte sequence, not including any following
 * composing characters.
 * Returns 0 for "".
 * Returns 1 for an illegal byte sequence.
 */
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

/*
 * Get a character from a UTF-8 string, doesn't include composing chars.
 */
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

/*
 * Return TRUE if "c" is a composing UTF-8 character.  This means it will be
 * drawn on top of the preceding character.
 *
 * MINIMAL FAITHFUL STUB: real vim checks "c" against a large sorted table of
 * Unicode combining-mark ranges (mbyte.c:utf_iscomposing()).  None of the
 * codepoints used by this harness's crafted inputs (plain ASCII and ordinary
 * printable Latin-1 letters) fall in any such range, so "not composing" is
 * the factually correct answer for every input this harness constructs --
 * this is not a fabricated shortcut, just the real table's answer for our
 * restricted input alphabet, without paying for the whole table.
 */
    int
utf_iscomposing(int c)
{
    (void)c;
    return 0;
}

/*
 * Return the offset from "p" to the first byte of the character it is
 * part of.  Includes composing characters.
 */
    int
utf_head_off(char_u *base, char_u *p)
{
    char_u	*q;
    char_u	*s;
    int		c;
    int		len;

    if (*p < 0x80)		// be quick for ASCII
	return 0;

    // Skip backwards over trailing bytes: 10xx.xxxx
    // Skip backwards again if on a composing char.
    for (q = p; ; --q)
    {
	// Move s to the last byte of this char.
	for (s = q; (s[1] & 0xc0) == 0x80; ++s)
	    ;
	// Move q to the first byte of this char.
	while (q > base && (*q & 0xc0) == 0x80)
	    --q;
	// Check for illegal sequence. Do allow an illegal byte after where we
	// started.
	len = utf8len_tab[*q];
	if (len != (int)(s - q + 1) && len != (int)(p - q + 1))
	    return 0;

	if (q <= base)
	    break;

	c = utf_ptr2char(q);
	if (utf_iscomposing(c))
	    continue;

	break;
    }

    return (int)(p - q);
}

/*
 * ptr2cells() -- from src/charset.c, dispatching (when enc_utf8) into
 * mbyte.c's utf_ptr2cells()/utf_char2cells() chain.
 *
 * MINIMAL FAITHFUL STUB for the display-width computation, which is
 * incidental to the memory-safety bug (the bug is about the byte position
 * `e`, not about display width): illegal/incomplete UTF-8 sequences report
 * cell-width 4, EXACTLY matching real vim's utf_ptr2cells() ("An illegal
 * byte is displayed as <xx>."); every other byte used by this harness's
 * inputs (ASCII, or the ordinary printable Latin-1 letters used as filler)
 * genuinely has cell-width 1 in real vim too (not in utf_char2cells's
 * double-width/ambiguous-width tables, not unprintable) -- so this is a
 * faithful reduction for our input alphabet, not an invented value.
 */
    int
ptr2cells(char_u *p)
{
    if (!has_mbyte)
	return 1;
    if (enc_utf8 && *p >= 0x80)
    {
	if (utf_ptr2len(p) == 1)
	    return 4;		// illegal byte, real vim: "<xx>" = 4 cells
	return 1;
    }
    return 1;
}

/*
 * vim_strsize() -- only called from trunc_string's `enc_dbcs != 0` branch,
 * which this harness never takes (enc_dbcs is always 0 here, no DBCS
 * encoding is exercised). Stub kept only so the reference resolves at
 * link time; it is provably dead code for every input this harness runs.
 */
    int
vim_strsize(char_u *s)
{
    (void)s;
    return 0;
}

/* ============================================================
 * TARGET FUNCTION -- byte-for-byte verbatim copy of
 * data_cve/cve_9a0c270d/target/original_function.c (src/message.c).
 * DO NOT EDIT ANYTHING BELOW THIS LINE THROUGH THE CLOSING BRACE.
 * ============================================================ */
void
trunc_string(
    char_u	*s,
    char_u	*buf,
    int		room_in,
    int		buflen)
{
    size_t	room = room_in - 3; // "..." takes 3 chars
    size_t	half;
    size_t	len = 0;
    int		e;
    int		i;
    int		n;

    if (*s == NUL)
    {
	if (buflen > 0)
	    *buf = NUL;
	return;
    }

    if (room_in < 3)
	room = 0;
    half = room / 2;

    // First part: Start of the string.
    for (e = 0; len < half && e < buflen; ++e)
    {
	if (s[e] == NUL)
	{
	    // text fits without truncating!
	    buf[e] = NUL;
	    return;
	}
	n = ptr2cells(s + e);
	if (len + n > half)
	    break;
	len += n;
	buf[e] = s[e];
	if (has_mbyte)
	    for (n = (*mb_ptr2len)(s + e); --n > 0; )
	    {
		if (++e == buflen)
		    break;
		buf[e] = s[e];
	    }
    }

    // Last part: End of the string.
    i = e;
    if (enc_dbcs != 0)
    {
	// For DBCS going backwards in a string is slow, but
	// computing the cell width isn't too slow: go forward
	// until the rest fits.
	n = vim_strsize(s + i);
	while (len + n > room)
	{
	    n -= ptr2cells(s + i);
	    i += (*mb_ptr2len)(s + i);
	}
    }
    else if (enc_utf8)
    {
	// For UTF-8 we can go backwards easily.
	half = i = (int)STRLEN(s);
	for (;;)
	{
	    do
		half = half - utf_head_off(s, s + half - 1) - 1;
	    while (half > 0 && utf_iscomposing(utf_ptr2char(s + half)));
	    n = ptr2cells(s + half);
	    if (len + n > room || half == 0)
		break;
	    len += n;
	    i = (int)half;
	}
    }
    else
    {
	for (i = (int)STRLEN(s);
		   i - 1 >= 0 && len + (n = ptr2cells(s + i - 1)) <= room; --i)
	    len += n;
    }


    if (i <= e + 3)
    {
	// text fits without truncating
	if (s != buf)
	{
	    len = STRLEN(s);
	    if (len >= (size_t)buflen)
		len = buflen - 1;
	    len = len - e + 1;
	    if (len < 1)
		buf[e - 1] = NUL;
	    else
		mch_memmove(buf + e, s + e, len);
	}
    }
    else if (e + 3 < buflen)
    {
	// set the middle and copy the last part
	mch_memmove(buf + e, "...", (size_t)3);
	len = STRLEN(s + i) + 1;
	if (len >= (size_t)buflen - e - 3)
	    len = buflen - e - 3 - 1;
	mch_memmove(buf + e + 3, s + i, len);
	buf[e + 3 + len - 1] = NUL;
    }
    else
    {
	// can't fit in the "...", just truncate it
	buf[e - 1] = NUL;
    }
}
/* ============================================================
 * END verbatim target function.
 * ============================================================ */

/* ---- harness driver ---- */

/* Fixed call-site parameters.  buflen is odd on purpose: with has_mbyte set
 * and a 2-byte-per-char filler, the "First part" loop's outer `++e` lands
 * `e` at exactly `buflen + 1` whenever `buflen` is odd (see file header) --
 * that is the overflow condition, independent of the input bytes.  Whether
 * a given input actually DRIVES `e` that far (and lands in the final
 * "can't fit" branch) depends on the input content, which is what
 * distinguishes the triggering corpus from the safe corpus below. */
#define VB_BUFLEN   41
#define VB_ROOM_IN  200

int main(int argc, char **argv)
{
    if (argc < 2)
    {
	fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
	return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f)
    {
	fprintf(stderr, "cannot open %s\n", argv[1]);
	return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long fsize = ftell(f);
    if (fsize < 0) { fclose(f); return 1; }
    rewind(f);

    /* Heap-allocate the input buffer (ASAN-guarded), +1 for NUL. */
    char_u *raw = (char_u *)malloc((size_t)fsize + 1);
    if (!raw) { fclose(f); return 1; }
    size_t got = fread(raw, 1, (size_t)fsize, f);
    fclose(f);
    raw[got] = NUL;

    /* Wire up the real vim multibyte globals as mb_init() would for
     * encoding=utf-8: has_mbyte + mb_ptr2len set together. */
    enc_utf8 = 1;
    enc_dbcs = 0;
    has_mbyte = 1;
    mb_ptr2len = utf_ptr2len;

    /* Separate heap allocation for the destination buffer, sized exactly
     * VB_BUFLEN so ASAN's redzone catches any write at or past buf[VB_BUFLEN]. */
    char_u *buf = (char_u *)malloc(VB_BUFLEN);
    if (!buf) { free(raw); return 1; }
    memset(buf, 0, VB_BUFLEN);

    trunc_string(raw, buf, VB_ROOM_IN, VB_BUFLEN);

    /* If we get here, no sanitizer fired: print something harmless. */
    printf("trunc_string returned, buf[0]=%d\n", (int)buf[0]);

    free(buf);
    free(raw);
    return 0;
}

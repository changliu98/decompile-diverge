/* cve_barebone harness -- vim msg_puts_printf unbounded-STRLEN heap-buffer-overflow READ
 * (CWE-125), fix commit c32949b0779106ed5710ae3bffc5053e49083ab4.
 *
 * Isolated reproduction: msg_puts_printf() is called directly on a heap buffer allocated to
 * EXACTLY `maxlen` bytes (the function's own documented contract for "str"). See the top-of-
 * file comment (this generator's docstring) for the exact mechanism.
 *
 * TRIGGER: str = an exactly-maxlen-byte heap allocation with no NUL (and no NL) anywhere in it
 *          -> the scan loop exits on the maxlen bound, *p != NUL, and the vulnerable
 *          STRLEN(p) call walks past the end of the allocation looking for a terminator.
 * SAFE:    str = the same exact-size allocation, but its last byte is an embedded NUL -> the
 *          unbounded STRLEN(p) call finds that terminator in-bounds -> no overflow.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real vim type / constant / macro definitions (src/vim.h, src/ascii.h) ---- */
typedef unsigned char char_u;

#define NUL		'\000'
#define NL		'\012'
#define CAR		'\015'

#ifndef TRUE
# define FALSE	0
# define TRUE	1
#endif

#define STRLEN(s)	    strlen((char *)(s))
#define STRNCPY(d, s, n)    strncpy((char *)(d), (char *)(s), (size_t)(n))

/* ---- real vim globals msg_puts_printf reads (src/globals.h, src/option.h) ---- */
int	silent_mode = FALSE;	/* src/globals.h:1133 */
long	p_verbose = 0;		/* 'verbose' option -- src/option.h:1051 */
int	info_message = FALSE;	/* src/globals.h:206 */
int	msg_col = 0;		/* src/globals.h:187 */
int	msg_didout = FALSE;	/* src/globals.h:201 */

/* MSWIN and FEAT_RIGHTLEFT are left undefined here exactly as they are on vim's own Unix
 * build, so the #ifdef'd mch_settmode()/Columns/cmdmsg_rl blocks below compile out -- the
 * pasted function body is untouched, only the surrounding preprocessor context selects the
 * same branches a real Unix vim build selects. */

/* ---- real vim helpers msg_puts_printf calls (src/alloc.c, src/strings.c) -- reproduced
 * with their real signatures; alloc()/vim_free() mirror the real allocator (lalloc()/free())
 * with vim's out-of-memory retry/message handling elided (incidental to the bug -- this host
 * never runs out of memory), vim_strnsave() is copied verbatim from src/strings.c since it is
 * a real callee on the (safe-path only) truncation branch. mch_msg()/mch_errmsg() are minimal
 * faithful stand-ins for vim's platform tty/gui output routines (src/message.c) -- immaterial
 * to the memory bug, which happens inside msg_puts_printf's own STRLEN(p) call, upstream of
 * either ever being reached on the trigger path. */
    void *
alloc(size_t size)
{
    return malloc(size);
}

    void
vim_free(void *x)
{
    free(x);
}

/* src/strings.c, verbatim */
    char_u *
vim_strnsave(char_u *string, size_t len)
{
    char_u	*p;

    p = alloc(len + 1);
    if (p != NULL)
    {
	STRNCPY(p, string, len);
	p[len] = NUL;
    }
    return p;
}

    void
mch_msg(char *str)
{
    fputs(str, stdout);
}

    void
mch_errmsg(char *str)
{
    fputs(str, stderr);
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the ASAN report keeps msg_puts_printf as its own stack frame (dc_batch requires
 * the target function name in the crash backtrace). */
__attribute__((noinline))
static void
msg_puts_printf(char_u *str, int maxlen)
{
    char_u	*s = str;
    char_u	*buf = NULL;
    char_u	*p = s;

#ifdef MSWIN
    if (!(silent_mode && p_verbose == 0))
	mch_settmode(TMODE_COOK);	// handle CR and NL correctly
#endif
    while ((maxlen < 0 || (int)(s - str) < maxlen) && *s != NUL)
    {
	if (!(silent_mode && p_verbose == 0))
	{
	    // NL --> CR NL translation (for Unix, not for "--version")
	    if (*s == NL)
	    {
		int n = (int)(s - p);

		buf = alloc(n + 3);
		if (buf != NULL)
		{
		    memcpy(buf, p, n);
		    if (!info_message)
			buf[n++] = CAR;
		    buf[n++] = NL;
		    buf[n++] = NUL;
		    if (info_message)   // informative message, not an error
			mch_msg((char *)buf);
		    else
			mch_errmsg((char *)buf);
		    vim_free(buf);
		}
		p = s + 1;
	    }
	}

	// primitive way to compute the current column
#ifdef FEAT_RIGHTLEFT
	if (cmdmsg_rl)
	{
	    if (*s == CAR || *s == NL)
		msg_col = Columns - 1;
	    else
		--msg_col;
	}
	else
#endif
	{
	    if (*s == CAR || *s == NL)
		msg_col = 0;
	    else
		++msg_col;
	}
	++s;
    }

    if (*p != NUL && !(silent_mode && p_verbose == 0))
    {
	char_u *tofree = NULL;

	if (maxlen > 0 && STRLEN(p) > (size_t)maxlen)
	{
	    tofree = vim_strnsave(p, (size_t)maxlen);
	    p = tofree;
	}
	if (p != NULL)
	{
	    if (info_message)
		mch_msg((char *)p);
	    else
		mch_errmsg((char *)p);
	    vim_free(tofree);
	}
    }

    msg_didout = TRUE;	    // assume that line is not empty

#ifdef MSWIN
    if (!(silent_mode && p_verbose == 0))
	mch_settmode(TMODE_RAW);
#endif
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long ln = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 0; }
    if (ln <= 0) { fclose(fp); return 0; }
    size_t n = (size_t)ln;

    /* HEAP-allocate str to EXACTLY n bytes -- msg_puts_printf's own documented contract for
     * "str" is "maxlen valid bytes", nothing more; a NUL terminator is NOT guaranteed to be
     * one of them (that is exactly the assumption the pre-fix STRLEN(p) call violates). */
    char_u *str = (char_u *)malloc(n);
    if (!str) { fclose(fp); return 0; }
    size_t got = fread(str, 1, n, fp);
    fclose(fp);
    if (got != n) { free(str); return 0; }

    /* volatile function pointer: forbid the compiler from inlining/proving-away the call
     * despite __attribute__((noinline)) on the definition. */
    void (* volatile fn)(char_u *, int) = msg_puts_printf;
    fn(str, (int)n);

    free(str);
    return 0;
}

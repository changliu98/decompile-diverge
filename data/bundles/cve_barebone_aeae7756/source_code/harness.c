/*
 * cve_barebone direct-call harness for vim's ex_history() (src/cmdhist.c).
 *
 * Bug (fixed upstream in commit 9198c1f2b1ddecde22af918541e0de2a32f0f45a, vim
 * patch 8.2.2068): get_list_range() parses a decimal number of arbitrary
 * length with vim_str2nr() into a 64-bit varnumber_T, then truncates it to a
 * plain `int` with `(int)num` WITHOUT checking `num > INT_MAX`.  For the
 * classic overflow value 2147483648 (2^31) this truncation yields exactly
 * INT_MIN.  ex_history() then does:
 *
 *     j = hisidx1;
 *     if (j < 0)
 *         j = (-j > hislen) ? 0 : hist[(hislen+j+idx+1) % hislen].hisnum;
 *
 * Negating INT_MIN is itself signed-overflow UB and on this codegen the
 * result stays INT_MIN (still deeply negative), so the `-j > hislen` guard
 * that is supposed to clamp any out-of-range index to a safe `j = 0` is
 * silently defeated, and `hist[(hislen+j+idx+1) % hislen]` is evaluated with
 * a wildly out-of-range negative index -> out-of-bounds heap READ before the
 * `hist` array.  This is exactly the upstream test
 * (src/testdir/test_history.vim, "Test_history_max_val"):
 *     call assert_fails(':history 2147483648', 'E1510:')
 * which the patch turns into a clean E1510 rejection by adding
 * `if (num > INT_MAX) return FAIL;` inside get_list_range().
 *
 * This harness calls ex_history() directly (no vim runtime/buffers/windows)
 * with a heap-allocated `char_u *arg` built from argv[1], and a small,
 * heap-allocated, fully-controlled fake ":history" table (`history[]`,
 * `hisidx[]`, `hislen`) so the out-of-bounds read lands in an ASAN-guarded
 * heap allocation.
 *
 * ex_history() itself (below, between the BEGIN/END markers) is pasted
 * BYTE-FOR-BYTE from data_cve/cve_aeae7756/target/original_function.c.
 *
 * Compiles + links standalone:
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   /* strncasecmp */
#include <limits.h>
#include <signal.h>    /* sig_atomic_t */

/* ---------------------------------------------------------------------
 * Real vim type/macro definitions, copied from src/vim.h, src/structs.h,
 * src/macros.h, src/ex_cmds.h, src/errors.h.
 * ------------------------------------------------------------------- */

typedef unsigned char char_u;                          /* src/vim.h */

#define NUL '\0'
#define IOSIZE (1024+1)                                 /* src/vim.h */

#define STRLEN(s)           strlen((char *)(s))          /* src/vim.h */
#define STRCPY(d, s)        strcpy((char *)(d), (char *)(s))
#define STRCAT(d, s)        strcat((char *)(d), (char *)(s))
#define STRNICMP(d, s, n)   strncasecmp((char *)(d), (char *)(s), (size_t)(n))

#define VIM_ISDIGIT(c)      ((unsigned)(c) - '0' < 10)   /* src/macros.h */
#define ASCII_ISUPPER(c)    ((c) >= 'A' && (c) <= 'Z')
#define ASCII_ISLOWER(c)    ((c) >= 'a' && (c) <= 'z')
#define ASCII_ISALPHA(c)    (ASCII_ISUPPER(c) || ASCII_ISLOWER(c))
#define ASCII_ISALNUM(c)    (ASCII_ISALPHA(c) || VIM_ISDIGIT(c))

#define _(x) ((char *)(x))                                /* src/vim.h, no-NLS */

/* src/vim.h: history table indices */
#define HIST_CMD    0
#define HIST_SEARCH 1
#define HIST_EXPR   2
#define HIST_INPUT  3
#define HIST_DEBUG  4
#define HIST_COUNT  5

/* src/structs.h: 64-bit Number type (Linux, has long long) */
typedef long long          varnumber_T;
typedef unsigned long long uvarnumber_T;
#define VARNUM_MIN  LLONG_MIN
#define VARNUM_MAX  LLONG_MAX
#define UVARNUM_MAX ULLONG_MAX

/* src/vim.h: flags for vim_str2nr() */
#define STR2NR_BIN   0x01
#define STR2NR_OCT   0x02
#define STR2NR_HEX   0x04
#define STR2NR_OOCT  0x08
#define STR2NR_ALL   (STR2NR_BIN + STR2NR_OCT + STR2NR_HEX + STR2NR_OOCT)
#define STR2NR_NO_OCT (STR2NR_BIN + STR2NR_HEX + STR2NR_OOCT)
#define STR2NR_FORCE 0x80
#define STR2NR_QUOTE 0x10

/* src/structs.h: struct hist_entry */
typedef struct hist_entry
{
    int     hisnum;     /* identifying number */
    int     viminfo;    /* when TRUE hisstr comes from viminfo */
    char_u  *hisstr;     /* actual entry, separator char after the NUL */
    long    time_set;   /* when it was typed, zero if unknown (real type time_t) */
} histentry_T;

/*
 * src/ex_cmds.h: struct exarg, trimmed to the ONE field ex_history() reads
 * (`arg`).  The real struct carries ~20 more fields (cmdidx_T, addr ranges,
 * getline callback, ...) that are irrelevant to ex_history()'s own body and
 * would drag in unrelated typedefs; the field that matters keeps its real
 * name and type.
 */
typedef struct exarg
{
    char_u *arg;        /* argument of the command */
} exarg_T;

/* src/errors.h */
static char e_trailing_characters_str[] = "E488: Trailing characters: %s";

/* ---------------------------------------------------------------------
 * Fake ":history" state (real names: history[], hisidx[], hislen from
 * src/cmdhist.c, normally `static` file-scope there -- here they are the
 * file-scope globals ex_history() resolves against in this single TU).
 * ------------------------------------------------------------------- */
static histentry_T *history[HIST_COUNT];
static int          hisidx[HIST_COUNT];
static int          hislen = 0;

/* src/cmdhist.c: table of history names */
static char *(history_names[]) =
{
    "cmd",
    "search",
    "expr",
    "input",
    "debug",
    NULL
};

/* src/globals.h */
static char_u *IObuff;
static long    Columns = 80;
static volatile sig_atomic_t got_int = 0;

/* ---------------------------------------------------------------------
 * Real callees on the crash path, copied (near-)verbatim.
 * ------------------------------------------------------------------- */

/* src/charset.c: hex2nr() */
static int
hex2nr(int c)
{
    if (c >= 'a' && c <= 'f')
	return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
	return c - 'A' + 10;
    return c - '0';
}

/* src/charset.c: vim_isxdigit()/vim_isbdigit()/vim_isodigit() */
static int
vim_isxdigit(int c)
{
    return (c >= '0' && c <= '9')
	|| (c >= 'a' && c <= 'f')
	|| (c >= 'A' && c <= 'F');
}

static int
vim_isbdigit(int c)
{
    return (c == '0' || c == '1');
}

static int
vim_isodigit(int c)
{
    return (c >= '0' && c <= '7');
}

/*
 * src/vim9script.c: in_vim9script() -- global-script-state check, irrelevant
 * to the overflow bug.  We are modelling ":history <arg>" typed directly at
 * the legacy (non-:def, non-vim9script) command line, so FALSE is the exact
 * real answer here, not just an approximation.
 */
static int
in_vim9script(void)
{
    return 0;
}

/*
 * src/charset.c: vim_str2nr() -- copied verbatim.  This is THE function that
 * performs the 64-bit decimal parse whose result get_list_range() then
 * truncates to `int` without a range check; it is essential to the crash
 * mechanism, not incidental.
 */
static void
vim_str2nr(
    char_u		*start,
    int			*prep,
    int			*len,
    int			what,
    varnumber_T		*nptr,
    uvarnumber_T	*unptr,
    int			maxlen,
    int			strict,
    int			*overflow)
{
    char_u	    *ptr = start;
    int		    pre = 0;
    int		    negative = 0;
    uvarnumber_T    un = 0;
    int		    n;

    if (len != NULL)
	*len = 0;

    if (ptr[0] == '-')
    {
	negative = 1;
	++ptr;
    }

    /* Recognize hex, octal, and bin. */
    if (ptr[0] == '0' && ptr[1] != '8' && ptr[1] != '9'
					       && (maxlen == 0 || maxlen > 1))
    {
	pre = ptr[1];
	if ((what & STR2NR_HEX)
		&& (pre == 'X' || pre == 'x') && vim_isxdigit(ptr[2])
		&& (maxlen == 0 || maxlen > 2))
	    ptr += 2;
	else if ((what & STR2NR_BIN)
		&& (pre == 'B' || pre == 'b') && vim_isbdigit(ptr[2])
		&& (maxlen == 0 || maxlen > 2))
	    ptr += 2;
	else if ((what & STR2NR_OOCT)
		&& (pre == 'O' || pre == 'o') && vim_isodigit(ptr[2])
		&& (maxlen == 0 || maxlen > 2))
	    ptr += 2;
	else
	{
	    pre = 0;
	    if (what & STR2NR_OCT)
	    {
		for (n = 1; n != maxlen && VIM_ISDIGIT(ptr[n]); ++n)
		{
		    if (ptr[n] > '7')
		    {
			pre = 0;
			break;
		    }
		    pre = '0';
		}
	    }
	}
    }

    n = 1;
    if (pre == 'B' || pre == 'b'
			     || ((what & STR2NR_BIN) && (what & STR2NR_FORCE)))
    {
	if (pre != 0)
	    n += 2;
	while ('0' <= *ptr && *ptr <= '1')
	{
	    if (un <= UVARNUM_MAX / 2)
		un = 2 * un + (uvarnumber_T)(*ptr - '0');
	    else
	    {
		un = UVARNUM_MAX;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    ++ptr;
	    if (n++ == maxlen)
		break;
	    if ((what & STR2NR_QUOTE) && *ptr == '\''
					     && '0' <= ptr[1] && ptr[1] <= '1')
	    {
		++ptr;
		if (n++ == maxlen)
		    break;
	    }
	}
    }
    else if (pre == 'O' || pre == 'o' ||
		pre == '0' || ((what & STR2NR_OCT) && (what & STR2NR_FORCE)))
    {
	if (pre != 0 && pre != '0')
	    n += 2;
	while ('0' <= *ptr && *ptr <= '7')
	{
	    if (un <= UVARNUM_MAX / 8)
		un = 8 * un + (uvarnumber_T)(*ptr - '0');
	    else
	    {
		un = UVARNUM_MAX;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    ++ptr;
	    if (n++ == maxlen)
		break;
	    if ((what & STR2NR_QUOTE) && *ptr == '\''
					     && '0' <= ptr[1] && ptr[1] <= '7')
	    {
		++ptr;
		if (n++ == maxlen)
		    break;
	    }
	}
    }
    else if (pre != 0 || ((what & STR2NR_HEX) && (what & STR2NR_FORCE)))
    {
	if (pre != 0)
	    n += 2;
	while (vim_isxdigit(*ptr))
	{
	    if (un <= UVARNUM_MAX / 16)
		un = 16 * un + (uvarnumber_T)hex2nr(*ptr);
	    else
	    {
		un = UVARNUM_MAX;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    ++ptr;
	    if (n++ == maxlen)
		break;
	    if ((what & STR2NR_QUOTE) && *ptr == '\'' && vim_isxdigit(ptr[1]))
	    {
		++ptr;
		if (n++ == maxlen)
		    break;
	    }
	}
    }
    else
    {
	/* decimal */
	while (VIM_ISDIGIT(*ptr))
	{
	    uvarnumber_T    digit = (uvarnumber_T)(*ptr - '0');

	    if (un < UVARNUM_MAX / 10
		    || (un == UVARNUM_MAX / 10 && digit <= UVARNUM_MAX % 10))
		un = 10 * un + digit;
	    else
	    {
		un = UVARNUM_MAX;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    ++ptr;
	    if (n++ == maxlen)
		break;
	    if ((what & STR2NR_QUOTE) && *ptr == '\'' && VIM_ISDIGIT(ptr[1]))
	    {
		++ptr;
		if (n++ == maxlen)
		    break;
	    }
	}
    }

    if (strict && n - 1 != maxlen && ASCII_ISALNUM(*ptr))
	return;

    if (prep != NULL)
	*prep = pre;
    if (len != NULL)
	*len = (int)(ptr - start);
    if (nptr != NULL)
    {
	if (negative)
	{
	    if (un > VARNUM_MAX)
	    {
		*nptr = VARNUM_MIN;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    else
		*nptr = -(varnumber_T)un;
	}
	else
	{
	    if (un > VARNUM_MAX)
	    {
		un = VARNUM_MAX;
		if (overflow != NULL)
		    *overflow = 1;
	    }
	    *nptr = (varnumber_T)un;
	}
    }
    if (unptr != NULL)
	*unptr = un;
}

/* src/charset.c: skipwhite() (real, trivial) */
static char_u *
skipwhite(char_u *q)
{
    char_u *p = q;
    while (*p == ' ' || *p == '\t')
	++p;
    return p;
}

/*
 * src/ex_getln.c: get_list_range() -- copied verbatim.  On the crash path:
 * this is where the missing `if (num > INT_MAX) return FAIL;` guard was
 * added by the fix; the version below is the pre-fix (vulnerable) body.
 */
static int
get_list_range(char_u **str, int *num1, int *num2)
{
    int		len;
    int		first = 0;
    varnumber_T	num;

    *str = skipwhite(*str);
    if (**str == '-' || VIM_ISDIGIT(**str))
    {
	vim_str2nr(*str, NULL, &len, 0, &num, NULL, 0, 0, NULL);
	*str += len;
	*num1 = (int)num;
	first = 1;
    }
    *str = skipwhite(*str);
    if (**str == ',')
    {
	*str = skipwhite(*str + 1);
	vim_str2nr(*str, NULL, &len, 0, &num, NULL, 0, 0, NULL);
	if (len > 0)
	{
	    *num2 = (int)num;
	    *str = skipwhite(*str + len);
	}
	else if (!first)
	    return 0; /* FAIL */
    }
    else if (first)
	*num2 = *num1;
    return 1; /* OK */
}

/* ---------------------------------------------------------------------
 * Incidental callees: not on the overflow/OOB-index crash mechanism, only
 * present because they're textually referenced inside ex_history()'s body
 * (some, like get_histtype()/vim_strchr(), only on branches our purely
 * numeric ":history <N>"/":history ,<N>" trigger arguments never reach).
 * Minimal faithful stand-ins so the file compiles & links standalone.
 * ------------------------------------------------------------------- */

/* src/strings.c: vim_strchr() -- single-byte (non-multibyte) case only,
 * matching this harness's (no multibyte state) execution; the multibyte
 * branches of the real function are unreachable here regardless. */
static char_u *
vim_strchr(char_u *string, int c)
{
    char_u *p = string;
    int b;
    while ((b = *p) != NUL)
    {
	if (b == c)
	    return p;
	++p;
    }
    return NULL;
}

/* src/cmdhist.c: get_histtype() -- never invoked by our numeric args (the
 * name-parsing branch in ex_history() is skipped whenever *arg is a digit,
 * '-' or ','), kept as a stub purely so the call site compiles. */
static int
get_histtype(char_u *name)
{
    (void)name;
    return -1;
}

/* src/message.c / src/term.c: display functions.  No memory-safety role;
 * ex_history() only uses them to format/print history lines. */
static int
msg(char *s)
{
    (void)s;
    return 1;
}

static int
semsg(const char *s, ...)
{
    (void)s;
    return 1;
}

static void
msg_puts_title(char *s)
{
    (void)s;
}

static void
msg_putchar(int c)
{
    (void)c;
}

static void
out_flush(void)
{
}

static int
msg_outtrans(char_u *str)
{
    (void)str;
    return 0;
}

/* src/charset.c: vim_strsize() -- real signature returns screen cell width
 * (tabs count double, multibyte width lookups, ...). Every hisstr this
 * harness ever stores is a short single-byte ASCII string with no tabs, so
 * strlen() is the exact real answer for our inputs. */
static int
vim_strsize(char_u *s)
{
    return (int)STRLEN(s);
}

/* src/message.c: trunc_string() -- guarded by `vim_strsize(...) > Columns-10`
 * (Columns=80 here), and every stored hisstr is far shorter than that, so
 * this is never actually invoked; kept safe regardless. */
static void
trunc_string(char_u *s, char_u *buf, int room_in, int buflen)
{
    (void)room_in;
    if (buflen > 0)
    {
	size_t n = STRLEN(s);
	if (n >= (size_t)buflen)
	    n = (size_t)buflen - 1;
	memcpy(buf, s, n);
	buf[n] = NUL;
    }
}

/* ==================== BEGIN ex_history() (verbatim) ==================== */
/* Pasted byte-for-byte from data_cve/cve_aeae7756/target/original_function.c */
void
ex_history(exarg_T *eap)
{
    histentry_T	*hist;
    int		histype1 = HIST_CMD;
    int		histype2 = HIST_CMD;
    int		hisidx1 = 1;
    int		hisidx2 = -1;
    int		idx;
    int		i, j, k;
    char_u	*end;
    char_u	*arg = eap->arg;

    if (hislen == 0)
    {
	msg(_("'history' option is zero"));
	return;
    }

    if (!(VIM_ISDIGIT(*arg) || *arg == '-' || *arg == ','))
    {
	end = arg;
	while (ASCII_ISALPHA(*end)
		|| vim_strchr((char_u *)":=@>/?", *end) != NULL)
	    end++;
	i = *end;
	*end = NUL;
	histype1 = get_histtype(arg);
	if (histype1 == -1)
	{
	    if (STRNICMP(arg, "all", STRLEN(arg)) == 0)
	    {
		histype1 = 0;
		histype2 = HIST_COUNT-1;
	    }
	    else
	    {
		*end = i;
		semsg(_(e_trailing_characters_str), arg);
		return;
	    }
	}
	else
	    histype2 = histype1;
	*end = i;
    }
    else
	end = arg;
    if (!get_list_range(&end, &hisidx1, &hisidx2) || *end != NUL)
    {
	semsg(_(e_trailing_characters_str), end);
	return;
    }

    for (; !got_int && histype1 <= histype2; ++histype1)
    {
	STRCPY(IObuff, "\n      #  ");
	STRCAT(STRCAT(IObuff, history_names[histype1]), " history");
	msg_puts_title((char *)IObuff);
	idx = hisidx[histype1];
	hist = history[histype1];
	j = hisidx1;
	k = hisidx2;
	if (j < 0)
	    j = (-j > hislen) ? 0 : hist[(hislen+j+idx+1) % hislen].hisnum;
	if (k < 0)
	    k = (-k > hislen) ? 0 : hist[(hislen+k+idx+1) % hislen].hisnum;
	if (idx >= 0 && j <= k)
	    for (i = idx + 1; !got_int; ++i)
	    {
		if (i == hislen)
		    i = 0;
		if (hist[i].hisstr != NULL
			&& hist[i].hisnum >= j && hist[i].hisnum <= k)
		{
		    msg_putchar('\n');
		    sprintf((char *)IObuff, "%c%6d  ", i == idx ? '>' : ' ',
							      hist[i].hisnum);
		    if (vim_strsize(hist[i].hisstr) > (int)Columns - 10)
			trunc_string(hist[i].hisstr, IObuff + STRLEN(IObuff),
			     (int)Columns - 10, IOSIZE - (int)STRLEN(IObuff));
		    else
			STRCAT(IObuff, hist[i].hisstr);
		    msg_outtrans(IObuff);
		    out_flush();
		}
		if (i == idx)
		    break;
	    }
    }
}
/* ===================== END ex_history() (verbatim) ====================== */

/* ---------------------------------------------------------------------
 * main(): read argv[1] into a HEAP buffer, build a small heap-allocated
 * fake ":history" table, call ex_history() on the attacker-controlled arg.
 * ------------------------------------------------------------------- */
int
main(int argc, char **argv)
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
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 1; }
    rewind(f);

    /* heap-allocate the input buffer, ASAN-guarded, exactly sized */
    char_u *arg = (char_u *)malloc((size_t)fsz + 1);
    if (!arg) { fclose(f); return 1; }
    size_t got = fread(arg, 1, (size_t)fsz, f);
    fclose(f);
    arg[got] = NUL;

    /* IObuff: sprintf/STRCPY/STRCAT scratch buffer, real size IOSIZE */
    IObuff = (char_u *)malloc(IOSIZE);
    IObuff[0] = NUL;

    /* fake ":history" table: hislen entries, all heap-allocated */
    hislen = 20;
    histentry_T *tbl = (histentry_T *)malloc(sizeof(histentry_T) * (size_t)hislen);
    for (int i = 0; i < hislen; ++i)
    {
	tbl[i].hisnum = i + 1;
	tbl[i].viminfo = 0;
	tbl[i].hisstr = (char_u *)strdup("x");
	tbl[i].time_set = 0;
    }
    history[HIST_CMD] = tbl;
    hisidx[HIST_CMD]  = hislen - 1;   /* most recent entry = last slot */

    exarg_T ea;
    ea.arg = arg;

    ex_history(&ea);

    /* if we get here, ex_history() returned without triggering ASAN */
    free(arg);
    free(IObuff);
    for (int i = 0; i < hislen; ++i)
	free(tbl[i].hisstr);
    free(tbl);
    return 0;
}

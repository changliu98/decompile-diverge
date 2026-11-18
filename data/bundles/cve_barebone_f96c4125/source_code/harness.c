/* cve_barebone harness -- vim CVE-2026-26269 / special_keys() netbeans handler
 * stack-buffer-overflow (CWE-787).
 *
 * Isolated reproduction: special_keys() is called directly on a heap-held argument
 * string shaped exactly like the netbeans "specialKeys" wire argument (a double-quoted,
 * possibly-backslash-escaped string; nb_unquote() -- the real callee -- strips the
 * quoting before tokenization, exactly as it does in the live netbeans command path).
 *
 * TRIGGER: a space-separated token containing '-' whose pre-dash run holds >= 33
 *          characters from {A,M,C,S} -> the unchecked `keybuf[i++] = ...` loop in
 *          special_keys() writes past the 64-byte stack array `keybuf` -> ASAN
 *          stack-buffer-overflow WRITE, caught inside special_keys() itself.
 * SAFE:    pre-dash modifier-letter run <= 32 (keeps the write loop fully in-bounds;
 *          the code either strcpy's a bounded suffix or, when it wouldn't fit, just
 *          skips that token) -- exercises the exact same tokenizer/loop with no crash.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/* ---- vim base typedef/macros special_keys()'s body needs (real names, vim.h/ascii.h) ---- */
typedef unsigned char char_u;
#define NUL		'\000'		/* ascii.h */
#define FALSE		0		/* vim.h: "note: this is an int, not a long!" */
#define TRUE		1
#define STRLEN(s)	strlen((char *)(s))	/* vim.h */

/* do_map()'s maptype/mode arguments special_keys() passes (real values, vim.h) */
#define MAPTYPE_MAP	0
#define MODE_NORMAL	0x01

/* netbeans debug hook: a no-op in a non-NBDEBUG build, which is what nb_unquote() compiles
 * against here (real definition, vim.h: "#ifdef NBDEBUG ... #else # define nbdebug(a)"). */
#define nbdebug(a)

/* ---- minimal faithful stubs, real names/signatures (proto.h), off special_keys()'s own
 * crash path: alloc_clear only shapes nb_unquote()'s OUTPUT buffer (a generic zeroing
 * allocator, nothing bug-specific); vim_snprintf/do_map/vim_free are only reached AFTER
 * the vulnerable loop already returned safely (a triggering run aborts inside that loop
 * and never reaches them). ---- */
static void *alloc_clear(size_t size)
{
    return calloc(1, size ? size : 1);
}

static void vim_free(void *x)
{
    free(x);
}

static int vim_snprintf(char *str, size_t str_m, const char *fmt, ...)
{
    va_list ap;
    int r;
    va_start(ap, fmt);
    r = vsnprintf(str, str_m, fmt, ap);
    va_end(ap);
    return r;
}

static int do_map(int maptype, char_u *arg, int mode, int abbrev)
{
    (void)maptype; (void)arg; (void)mode; (void)abbrev;
    return 0;
}

/* ---- nb_unquote: VERBATIM (src/netbeans.c) -- the one real callee on the crash path:
 * it turns the raw wire argument special_keys() receives into the string it tokenizes. ---- */
/*
 * Remove top level double quotes; convert backslashed chars.
 * Returns an allocated string (NULL for failure).
 * If "endp" is not NULL it is set to the character after the terminating
 * quote.
 */
    static char *
nb_unquote(char_u *p, char_u **endp)
{
    char *result = 0;
    char *q;
    int done = 0;

    // result is never longer than input
    result = alloc_clear(STRLEN(p) + 1);
    if (result == NULL)
	return NULL;

    if (*p++ != '"')
    {
	nbdebug(("nb_unquote called with string that doesn't start with a quote!: %s\n",
			p));
	result[0] = NUL;
	return result;
    }

    for (q = result; !done && *p != NUL;)
    {
	switch (*p)
	{
	    case '"':
		/*
		 * Unbackslashed dquote marks the end, if first char was dquote.
		 */
		done = 1;
		break;

	    case '\\':
		++p;
		switch (*p)
		{
		    case '\\':	*q++ = '\\';	break;
		    case 'n':	*q++ = '\n';	break;
		    case 't':	*q++ = '\t';	break;
		    case 'r':	*q++ = '\r';	break;
		    case '"':	*q++ = '"';	break;
		    case NUL:	--p;		break;
		    // default: skip over illegal chars
		}
		++p;
		break;

	    default:
		*q++ = *p++;
	}
    }

    if (endp != NULL)
	*endp = p;

    return result;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
__attribute__((noinline))
static void
special_keys(char_u *args)
{
    char *save_str = nb_unquote(args, NULL);
    char *tok = strtok(save_str, " ");
    char *sep;
#define KEYBUFLEN 64
    char keybuf[KEYBUFLEN];
    char cmdbuf[256];

    while (tok != NULL)
    {
	int i = 0;

	if ((sep = strchr(tok, '-')) != NULL)
	{
	    *sep = NUL;
	    while (*tok)
	    {
		switch (*tok)
		{
		    case 'A':
		    case 'M':
		    case 'C':
		    case 'S':
			keybuf[i++] = *tok;
			keybuf[i++] = '-';
			break;
		}
		tok++;
	    }
	    tok++;
	}

	if (strlen(tok) + i < KEYBUFLEN)
	{
	    strcpy(&keybuf[i], tok);
	    vim_snprintf(cmdbuf, sizeof(cmdbuf),
				 "<silent><%s> :nbkey %s<CR>", keybuf, keybuf);
	    do_map(MAPTYPE_MAP, (char_u *)cmdbuf, MODE_NORMAL, FALSE);
	}
	tok = strtok(NULL, " ");
    }
    vim_free(save_str);
}

/* ================= driver ================= */
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
    char *args = (char *)malloc(n + 1);        /* HEAP input, ASAN-guarded, +1 for NUL */
    size_t got = fread(args, 1, n, fp);
    fclose(fp);
    args[got] = '\0';
    if (got < 2) { free(args); return 0; }     /* too small to matter -> clean exit */

    /* volatile function pointer: forbid the compiler from proving away / hoisting the call. */
    void (*volatile fn)(char_u *) = special_keys;
    fn((char_u *)args);

    free(args);
    return 0;
}

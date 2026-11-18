/*
 * ddiv cve_barebone direct-call harness
 * bid=cve_57c4d8ba  project=vim  target=compile_get_env  (src/vim9expr.c)
 * CVE-2022-0158 / CWE-125 (heap-buffer-overflow, out-of-bounds READ)
 *
 * fix_commit 5f25c3855071bd7e26255c68bf458b1b5cf92f39 changes
 *     semsg(_(e_syntax_error_at_str), start - 1);
 * to
 *     semsg(_(e_syntax_error_at_str), start);
 * inside compile_get_env().  "start" is the position of the '$' that
 * introduces a vim9 "$VAR" expression.  When the character right after
 * '$' is not a valid identifier character, get_env_len() returns 0 and
 * the (pre-fix) error path formats a message with "%s" pointed at
 * start - 1 -- one byte BEFORE the '$'.  Vim parses source one line at a
 * time, each line living in its own freshly heap-allocated buffer
 * (getsourceline()/vim_strsave() family), so when the '$' is the very
 * first character of that line (e.g. a bare "$" on a line by itself --
 * exactly the regression test the fix commit adds:
 * CheckDefAndScriptFailure(["$"], ['E1002:', 'E15:'], 1)), start - 1
 * underflows the line's own allocation by one byte.  The actual invalid
 * memory ACCESS happens where the "%s" is consumed (vim_vsnprintf's
 * STRLEN(str) walk) -- semsg() is reproduced below as a minimal, but
 * behaviourally faithful, stub that performs exactly that STRLEN() walk
 * (STRLEN is literally `strlen` in real vim, see vim.h), so the resulting
 * ASAN fault is the SAME access the real engine makes, not a synthetic one.
 *
 * This harness reproduces the vulnerable line-buffer allocation directly:
 * argv[1]'s bytes are copied into a fresh malloc() buffer, and
 * compile_get_env() is invoked with *arg pointing at byte 0 of that
 * buffer -- so a triggering input is simply "$" followed by any byte
 * that is not a legal identifier character (or end-of-buffer).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/* ---------------------------------------------------------------------
 * vim.h (subset) -- verbatim macro/type definitions compile_get_env's
 * body and its immediate callees need.
 * --------------------------------------------------------------------- */
typedef unsigned char char_u;

#define NUL   0
#define OK    1
#define FAIL  0

#define _(x)              ((char *)(x))
#define STRLEN(s)         strlen((char *)(s))
#define STRNCPY(d, s, n)  strncpy((char *)(d), (char *)(s), (size_t)(n))

/* ---------------------------------------------------------------------
 * errors.h (verbatim message text)
 * --------------------------------------------------------------------- */
char e_syntax_error_at_str[] = "E1002: Syntax error at %s";

/* ---------------------------------------------------------------------
 * alloc.c (minimal faithful stubs -- real alloc()/vim_free() are
 * malloc()/free() wrappers with out-of-memory handling bolted on; the
 * OOM handling is incidental to this fault).
 * --------------------------------------------------------------------- */
static void *
alloc(size_t size)
{
    return malloc(size);
}

    void
vim_free(void *x)
{
    free(x);
}

/* ---------------------------------------------------------------------
 * charset.c -- vim_isIDc() is backed by the runtime g_chartab[], which
 * real vim initialises from several options ('isident' etc). Out of
 * scope here; vb_init_chartab() below sets g_chartab up to match the
 * DEFAULT 'isident' class ("@,48-57,_,192-255": letters, digits,
 * underscore, and the Latin-1 letter range), which is exactly what
 * vim_isIDc() consults -- same signature, same CT_ID_CHAR bit test.
 * --------------------------------------------------------------------- */
#define CT_ID_CHAR 0x02
static unsigned char g_chartab[256];

static void
vb_init_chartab(void)
{
    int c;
    for (c = 0; c < 256; ++c)
        g_chartab[c] = 0;
    for (c = 0; c < 256; ++c)
        if (isalpha(c))
            g_chartab[c] |= CT_ID_CHAR;
    for (c = '0'; c <= '9'; ++c)
        g_chartab[c] |= CT_ID_CHAR;
    g_chartab[(unsigned char)'_'] |= CT_ID_CHAR;
    for (c = 192; c <= 255; ++c)
        g_chartab[c] |= CT_ID_CHAR;
}

    int
vim_isIDc(int c)
{
    return (c > 0 && c < 0x100 && (g_chartab[c] & CT_ID_CHAR));
}

/* ---------------------------------------------------------------------
 * eval.c:get_env_len -- verbatim (src/eval.c, near line 5541). Directly
 * decides whether compile_get_env takes the buggy branch.
 * --------------------------------------------------------------------- */
    int
get_env_len(char_u **arg)
{
    char_u	*p;
    int		len;

    for (p = *arg; vim_isIDc(*p); ++p)
	;
    if (p == *arg)	    // no name found
	return 0;

    len = (int)(p - *arg);
    *arg = p;
    return len;
}

/* ---------------------------------------------------------------------
 * strings.c:vim_strnsave -- verbatim (src/strings.c, near line 40).
 * --------------------------------------------------------------------- */
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

/* ---------------------------------------------------------------------
 * message.c:semsg -- minimal faithful stub. Real semsg() formats through
 * vim_vsnprintf(), whose "%s" conversion calls STRLEN(str) (== strlen())
 * on the pointer it was handed before copying any bytes. That STRLEN()
 * walk is reproduced verbatim below: it is the actual memory access that
 * turns compile_get_env's bad "start - 1" pointer into an ASAN report,
 * so this is on the crash path, not incidental scaffolding. Everything
 * else real semsg() does (gettext lookup, IObuff formatting, screen
 * redraw, message history) has no bearing on whether/where the invalid
 * access happens and is left out.
 * --------------------------------------------------------------------- */
static volatile size_t vb_semsg_sink;

int
semsg(const char *fmt, ...)
{
    va_list	ap;
    const char_u *s;

    va_start(ap, fmt);
    s = va_arg(ap, const char_u *);
    va_end(ap);

    /* the exact %s walk vim_vsnprintf() performs. Stored through a
     * volatile (rather than discarded) so -O1 cannot prove the call has
     * no observable effect and fold it away as a dead pure-builtin --
     * that would silently skip the very memory access this stub exists
     * to reproduce. */
    vb_semsg_sink = STRLEN(s);
    (void)fmt;
    return 0;
}

/* ---------------------------------------------------------------------
 * vim9.h (subset). compile_get_env only ever FORWARDS cctx/type
 * pointers (to generate_LOAD) -- it never dereferences them itself --
 * so cctx_T/type_T are kept opaque here; the real structs are ~100
 * fields deep across a dozen other types that are irrelevant to this
 * fault. t_string is the real global name generate_LOAD is normally
 * handed for a $VAR load. isntype_T is trimmed to the one enumerator
 * this call site uses.
 * --------------------------------------------------------------------- */
typedef struct cctx_S cctx_T;
struct cctx_S { int unused_; };

typedef struct type_S type_T;
struct type_S { int unused_; };
type_T t_string;

typedef enum { ISN_LOADENV } isntype_T;

/* ---------------------------------------------------------------------
 * vim9instr.c:generate_LOAD -- minimal faithful stub. Only reached on
 * the NON-crashing branch (len != 0), so it is incidental to the fault;
 * modelled behaviour keeps the real contract that matters to the
 * caller: it does not take ownership of `name` (real generate_LOAD
 * vim_strsave()s its own copy into an isn_T growarray slot), and
 * returns OK/FAIL. The growarray/isn_T instruction-stream machinery
 * itself has no bearing on whether compile_get_env() crashes.
 * --------------------------------------------------------------------- */
int
generate_LOAD(cctx_T *cctx, isntype_T isn_type, int idx, char_u *name, type_T *type)
{
    (void)cctx; (void)isn_type; (void)idx; (void)type;
    if (name != NULL)
    {
        char_u *copy = vim_strnsave(name, STRLEN(name));
        vim_free(copy);
    }
    return OK;
}

/* ==== TARGET FUNCTION -- byte-for-byte from
 * data_cve/cve_57c4d8ba/target/original_function.c (src/vim9expr.c:1224) ==== */
static int
compile_get_env(char_u **arg, cctx_T *cctx)
{
    char_u	*start = *arg;
    int		len;
    int		ret;
    char_u	*name;

    ++*arg;
    len = get_env_len(arg);
    if (len == 0)
    {
	semsg(_(e_syntax_error_at_str), start - 1);
	return FAIL;
    }

    // include the '$' in the name, eval_env_var() expects it.
    name = vim_strnsave(start, len + 1);
    ret = generate_LOAD(cctx, ISN_LOADENV, 0, name, &t_string);
    vim_free(name);
    return ret;
}

/* ---------------------------------------------------------------------
 * driver
 * --------------------------------------------------------------------- */
int
main(int argc, char **argv)
{
    FILE   *f;
    long    sz;
    char_u *buf;
    char_u *arg;
    cctx_T  cctx;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 1;
    }
    f = fopen(argv[1], "rb");
    if (!f)
    {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 1)
    {
        fclose(f);
        return 0;
    }

    /* Heap-allocate EXACTLY sz+1 bytes (payload + our own NUL
     * terminator), so byte 0 of the allocation is the first byte of
     * the input file -- reproducing vim's own "this line's buffer
     * starts exactly at the character we're about to parse" layout. A
     * "start - 1" access (start == buf) then lands one byte to the
     * LEFT of this allocation, in ASAN's redzone. */
    buf = (char_u *) malloc((size_t) sz + 1);
    if (!buf)
    {
        fclose(f);
        return 1;
    }
    if (fread(buf, 1, (size_t) sz, f) != (size_t) sz)
    {
        fclose(f);
        free(buf);
        return 1;
    }
    fclose(f);
    buf[sz] = NUL;

    vb_init_chartab();
    memset(&cctx, 0, sizeof(cctx));

    /* compile_get_env() is only ever called by its one real caller
     * (vim9expr.c ~line 2038, `case '$':`) once the parser has already
     * peeked that **arg == '$' -- mirror that precondition here. */
    if (buf[0] != '$')
    {
        free(buf);
        return 0;
    }

    arg = buf;
    (void) compile_get_env(&arg, &cctx);

    free(buf);
    return 0;
}

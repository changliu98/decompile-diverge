/* Direct-call crash harness for vim get_register (src/register.c), the bug
 * fixed by vim/vim@d1ae8366aff286d41e7f5bc513cc0a1af5130aad ("patch 9.1.1531:
 * crash when 'enc' is changed while y_current->y_array is NULL").
 *
 * Real bug (src/register.c, get_register()):
 *
 *     get_yank_register(name, 0);
 *     reg = ALLOC_ONE(yankreg_T);
 *     ...
 *     *reg = *y_current;
 *     if (copy)
 *     {
 *         // If we run out of memory some or all of the lines are empty.
 *         if (reg->y_size == 0)
 *             reg->y_array = NULL;
 *         else
 *             reg->y_array = ALLOC_MULT(char_u *, reg->y_size);
 *         if (reg->y_array != NULL)
 *         {
 *             for (i = 0; i < reg->y_size; ++i)
 *                 reg->y_array[i] = vim_strsave(y_current->y_array[i]);
 *         }
 *     }
 *
 * The guard only checks reg->y_size == 0; it never checks whether
 * y_current->y_array itself is NULL. If a register ends up with y_size > 0
 * but y_array == NULL (the fix's commit message: this can happen when
 * y_append ends up NULL, e.g. via a `norm 0VPSP` sequence combined with an
 * 'encoding' change while editing -- upstream Test_zero_y_append), the
 * `reg->y_array = ALLOC_MULT(...)` branch is taken (reg->y_size != 0), so
 * reg->y_array != NULL, and the loop runs y_current->y_array[i] for
 * i = 0 .. y_size-1 -- dereferencing the NULL y_current->y_array pointer.
 * That is a NULL-pointer read (CWE-476) entirely inside get_register's own
 * body, before vim_strsave is ever reached (the crash is evaluating the
 * *argument* to vim_strsave, y_current->y_array[i], not inside vim_strsave).
 * The fix adds "|| y_current->y_array == NULL" to the y_size==0 check.
 *
 * This harness reproduces that state directly: it selects a register (one of
 * the digit registers "1".."9", exactly like get_yank_register's own
 * VIM_ISDIGIT branch: i = regname - '0') and, for the *triggering* class,
 * pre-sets that register's y_size > 0 and y_array == NULL before calling
 * get_register(name, TRUE) -- i.e. it constructs the exact pre-state the
 * patch's own regression test (Test_zero_y_append) exercises through many
 * layers of the editor, but does it directly at the get_register() call
 * boundary, calling get_register() itself in total isolation.
 *
 * get_yank_register() (src/register.c) is embedded VERBATIM below: it is a
 * real, direct callee of get_register() on the very path that selects which
 * yankreg_T get_register operates on, and it is simple/self-contained enough
 * (only uses VIM_ISDIGIT/ASCII_ISLOWER/ASCII_ISUPPER/CharOrdLow/CharOrdUp/
 * DELETION_REGISTER/TRUE/FALSE and the register.c-local globals y_regs/
 * y_current/y_previous/y_append) to compile standalone once FEAT_CLIPBOARD
 * and FEAT_DND are left undefined (matching how vim compiles without those
 * optional features -- get_register()'s own #ifdef FEAT_CLIPBOARD block at
 * the top of its body is likewise skipped by the preprocessor, unedited).
 *
 * alloc()/vim_strsave() are minimal faithful stubs for incidental allocation
 * helpers (real vim.h ALLOC_ONE/ALLOC_MULT macros are used verbatim; alloc()
 * is a thin malloc() wrapper and vim_strsave() a thin strdup()-equivalent --
 * neither is on the crash path itself for the triggering class, since the
 * crash occurs reading y_current->y_array[i] as vim_strsave's argument,
 * before vim_strsave's body ever executes).
 *
 * Input format (read into a malloc'd heap buffer, >=4 bytes required else the
 * run is a clean no-op):
 *   byte[0] -> selects a digit register '1'..'9' (b0 % 9), avoiding the
 *              regname==0 / '"' y_previous shortcut and any clipboard-only
 *              register names.
 *   byte[1] -> for the SAFE class only, low bit selects copy TRUE/FALSE
 *              (ignored for the triggering class, which always calls with
 *              copy == TRUE, the only value that reaches the buggy branch).
 *   byte[2] -> low bit 1 = TRIGGERING class (y_size>0, y_array=NULL);
 *              low bit 0 = SAFE class (y_size>0, y_array = a valid,
 *              properly populated array of heap-allocated line strings --
 *              get_register's normal, correct behaviour).
 *   byte[3] -> y_size = 1 + (b3 % 8), i.e. 1..8 lines.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- real type defs, verbatim names/layout from src/vim.h / src/structs.h,
 * for the (FEAT_CLIPBOARD, FEAT_DND, FEAT_VIMINFO undefined) build config
 * get_register()'s own #ifdefs already select for. ---- */

typedef unsigned char char_u;
typedef long          linenr_T;   /* src/vim.h */
typedef int           colnr_T;    /* src/vim.h */

#define FALSE 0        /* src/vim.h */
#define TRUE  1        /* src/vim.h */

/* src/macros.h */
#define VIM_ISDIGIT(c)   ((unsigned)(c) - '0' < 10)
#define ASCII_ISLOWER(c) ((unsigned)(c) - 'a' < 26)
#define ASCII_ISUPPER(c) ((unsigned)(c) - 'A' < 26)
/* src/ascii.h */
#define CharOrdLow(x) ((x) - 'a')
#define CharOrdUp(x)  ((x) - 'A')

/* src/structs.h: FEAT_CLIPBOARD undefined -> NUM_REGISTERS 37;
 * DELETION_REGISTER 36 (src/structs.h, unconditional). */
#define NUM_REGISTERS      37
#define DELETION_REGISTER  36

/* src/structs.h: "Each yank register has an array of pointers to lines."
 * (FEAT_VIMINFO left undefined, so y_time_set is omitted -- unused by either
 * get_register or get_yank_register). */
typedef struct
{
    char_u   **y_array;   /* pointer to array of line pointers */
    linenr_T y_size;      /* number of lines in y_array */
    char_u   y_type;      /* MLINE, MCHAR or MBLOCK */
    colnr_T  y_width;     /* only set if y_type == MBLOCK */
} yankreg_T;

/* src/vim.h */
#define ALLOC_ONE(type)         (type *)alloc(sizeof(type))
#define ALLOC_MULT(type, count) (type *)alloc(sizeof(type) * (count))

/* ---- minimal faithful stubs for incidental allocation helpers (real vim
 * alloc()/vim_strsave() do bookkeeping unrelated to this bug; a thin
 * malloc()/strdup()-equivalent preserves their observable behaviour for the
 * SAFE class). ---- */
static void *alloc(size_t sz)
{
    return malloc(sz);
}

static char_u *vim_strsave(char_u *string)
{
    size_t len;
    char_u *p;

    if (string == NULL)
        return NULL;
    len = strlen((char *)string) + 1;
    p = (char_u *)malloc(len);
    if (p != NULL)
        memcpy(p, string, len);
    return p;
}

/* ---- src/register.c file-scope globals, verbatim declarations ---- */
static yankreg_T  y_regs[NUM_REGISTERS];
static yankreg_T  *y_current;      /* ptr to current yankreg */
static int        y_append;        /* TRUE when appending */
static yankreg_T  *y_previous = NULL; /* ptr to last written yankreg */

/* ---- real callee, VERBATIM from src/register.c lines 217-264
 * (get_yank_register) ---- */
    int
get_yank_register(int regname, int writing)
{
    int	    i;
    int	    ret = FALSE;

    y_append = FALSE;
    if ((regname == 0 || regname == '"') && !writing && y_previous != NULL)
    {
	y_current = y_previous;
	return ret;
    }
    i = regname;
    if (VIM_ISDIGIT(i))
	i -= '0';
    else if (ASCII_ISLOWER(i))
	i = CharOrdLow(i) + 10;
    else if (ASCII_ISUPPER(i))
    {
	i = CharOrdUp(i) + 10;
	y_append = TRUE;
    }
    else if (regname == '-')
	i = DELETION_REGISTER;
#ifdef FEAT_CLIPBOARD
    // When selection is not available, use register 0 instead of '*'
    else if (clip_star.available && regname == '*')
    {
	i = STAR_REGISTER;
	ret = TRUE;
    }
    // When clipboard is not available, use register 0 instead of '+'
    else if (clip_plus.available && regname == '+')
    {
	i = PLUS_REGISTER;
	ret = TRUE;
    }
#endif
#ifdef FEAT_DND
    else if (!writing && regname == '~')
	i = TILDE_REGISTER;
#endif
    else		// not 0-9, a-z, A-Z or '-': use register 0
	i = 0;
    y_current = &(y_regs[i]);
    if (writing)	// remember the register we write into for do_put()
	y_previous = y_current;
    return ret;
}

/* ---- target function, VERBATIM (byte-for-byte) from
 * data_cve/cve_a157092c/target/original_function.c ---- */
void *
get_register(
    int		name,
    int		copy)	// make a copy, if FALSE make register empty.
{
    yankreg_T	*reg;
    int		i;

#ifdef FEAT_CLIPBOARD
    // When Visual area changed, may have to update selection.  Obtain the
    // selection too.
    if (name == '*' && clip_star.available)
    {
	if (clip_isautosel_star())
	    clip_update_selection(&clip_star);
	may_get_selection(name);
    }
    if (name == '+' && clip_plus.available)
    {
	if (clip_isautosel_plus())
	    clip_update_selection(&clip_plus);
	may_get_selection(name);
    }
#endif

    get_yank_register(name, 0);
    reg = ALLOC_ONE(yankreg_T);
    if (reg == NULL)
	return (void *)NULL;

    *reg = *y_current;
    if (copy)
    {
	// If we run out of memory some or all of the lines are empty.
	if (reg->y_size == 0)
	    reg->y_array = NULL;
	else
	    reg->y_array = ALLOC_MULT(char_u *, reg->y_size);
	if (reg->y_array != NULL)
	{
	    for (i = 0; i < reg->y_size; ++i)
		reg->y_array[i] = vim_strsave(y_current->y_array[i]);
	}
    }
    else
	y_current->y_array = NULL;
    return (void *)reg;
}

/* ---- driver ---- */

int main(int argc, char **argv)
{
    FILE *fp;
    long fsz;
    unsigned char *buf;
    size_t n;
    unsigned char b0, b1, b2, b3;
    int regname, idx, copy, trigger, ysize, k;
    void *r;

    if (argc < 2)
        return 0;
    fp = fopen(argv[1], "rb");
    if (fp == NULL)
        return 0;
    fseek(fp, 0, SEEK_END);
    fsz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsz < 4)
    {
        fclose(fp);
        return 0;
    }
    /* Heap-allocate the input buffer so ASAN's heap machinery guards it. */
    buf = (unsigned char *)malloc((size_t)fsz);
    if (buf == NULL)
    {
        fclose(fp);
        return 0;
    }
    n = fread(buf, 1, (size_t)fsz, fp);
    fclose(fp);
    if (n < 4)
    {
        free(buf);
        return 0;
    }

    b0 = buf[0];
    b1 = buf[1];
    b2 = buf[2];
    b3 = buf[3];
    free(buf);

    /* Digit register '1'..'9': hits get_yank_register's VIM_ISDIGIT branch
     * (i = regname - '0'), never the regname==0/'"' y_previous shortcut and
     * never a clipboard-only name. */
    regname = '1' + (int)(b0 % 9);
    idx = regname - '0';
    trigger = (int)(b2 & 1);
    ysize = 1 + (int)(b3 % 8);

    if (trigger)
    {
        /* Vulnerable pre-state: y_size > 0 but y_array == NULL -- exactly
         * what the fix commit's "|| y_current->y_array == NULL" guards
         * against. copy MUST be TRUE to reach the buggy branch. */
        y_regs[idx].y_array = NULL;
        y_regs[idx].y_size = ysize;
        y_regs[idx].y_type = 0;
        y_regs[idx].y_width = 0;
        copy = TRUE;
    }
    else
    {
        /* Well-formed pre-state: y_size > 0 and a valid, fully populated
         * y_array -- get_register's normal, correct behaviour. */
        y_regs[idx].y_array = (char_u **)malloc(sizeof(char_u *) * (size_t)ysize);
        for (k = 0; k < ysize; k++)
        {
            char_u *line = (char_u *)malloc(4);
            line[0] = 'a';
            line[1] = 'b';
            line[2] = 'c';
            line[3] = 0;
            y_regs[idx].y_array[k] = line;
        }
        y_regs[idx].y_size = ysize;
        y_regs[idx].y_type = 0;
        y_regs[idx].y_width = 0;
        copy = (int)(b1 & 1);
    }

    r = get_register(regname, copy);
    (void)r;
    return 0;
}

/* cve_0667332f -- vim bracketed_paste() off-by-one heap-buffer-overflow
 * (fixed upstream by 806d037671e133bd28a7864248763f643967973a, vim patch 4218).
 *
 * Root cause (entirely inside bracketed_paste's own body): the PASTE_EX case
 * grows the caller's garray_T by exactly `idx` (the number of freshly-read
 * bytes) before appending them:
 *
 *     case PASTE_EX:
 *         if (gap != NULL && ga_grow(gap, idx) == OK)
 *         {
 *             mch_memmove((char *)gap->ga_data + gap->ga_len, buf, (size_t)idx);
 *             gap->ga_len += idx;
 *         }
 *         break;
 *
 * so after the loop returns, gap->ga_len can equal gap->ga_maxlen exactly
 * (zero slack). Every real call site (src/ex_getln.c, both at the `redraw:`
 * label and in the BS/Ctrl-T handlers) immediately does
 *     p = (char_u *)line_ga.ga_data;
 *     p[line_ga.ga_len] = NUL;
 * right after calling bracketed_paste(PASTE_EX, ...) -- a 1-byte
 * NUL-terminator write that overflows the heap buffer whenever bracketed_paste
 * left zero slack. The upstream fix changes the grow call to
 * `ga_grow(gap, idx + 1)`, reserving that trailing byte.
 *
 * This harness reproduces the exact call/grow pattern: it primes the garray
 * with the same `ga_grow(&gap, 40)` ex_getln.c's outer read-loop issues right
 * before reading a character, calls bracketed_paste(PASTE_EX, FALSE, &gap)
 * with attacker bytes fed through vgetc()/vpeekc(), and then performs the
 * SAME NUL-termination write every real caller performs on return. The
 * garray_T buffer's entire lifecycle (every ga_grow/realloc, including the
 * final one that leaves zero slack) is driven exclusively from calls made
 * inside bracketed_paste's own body, so it is the frame that owns the heap
 * allocation ASAN reports as overflowed.
 */
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char char_u;

#define NUL   0
#define NL    10
#define CAR   13
#define Ctrl_C 3
#define TRUE  1
#define FALSE 0
#define OK    1
#define FAIL  0
#define NUMBUFLEN   65
#define MB_MAXBYTES 21

/* Sentinel "special key" values outside the 0..255 byte range vgetc() ever
 * returns for real content -- real vim encodes these via TERMCAP2KEY(); the
 * exact bit pattern is irrelevant here, only that they never collide with a
 * plain input byte. */
#define K_IGNORE        0x1001
#define K_VER_SCROLLBAR 0x1002
#define K_HOR_SCROLLBAR 0x1003
#define K_KENTER        0x1004

/* src/vim.h:2199-2203 (paste_mode_T), verbatim enumerator names/order */
typedef enum {
    PASTE_INSERT,	// insert mode
    PASTE_CMDLINE,	// command line
    PASTE_EX,		// ex mode line
    PASTE_ONE_CHAR	// return first character
} paste_mode_T;

/* src/structs.h:47-55, verbatim field names/order */
typedef struct growarray
{
    int	    ga_len;		    // current number of items used
    int	    ga_maxlen;		    // maximum number of items possible
    int	    ga_itemsize;	    // sizeof(item)
    int	    ga_growsize;	    // number of items to grow each time
    void    *ga_data;		    // pointer to the first item
} garray_T;

/* src/vim.h macros bracketed_paste relies on */
#define STRLEN(s)	    strlen((char *)(s))
#define STRNCMP(d, s, n)    strncmp((char *)(d), (char *)(s), (size_t)(n))
#define mch_memmove(to, from, len) memmove((char*)(to), (char*)(from), (size_t)(len))
#define vim_memset(ptr, c, size)   memset((ptr), (c), (size))
#define vim_realloc(ptr, size)     realloc((ptr), (size))

/* ---- globals bracketed_paste reads/writes (types match vim's option/global ints) ---- */
int allow_keys;
int p_paste;
int no_mapping;
int ex_normal_busy;
int has_mbyte;
int got_int;

int (*mb_char2bytes)(int c, char_u *buf);
int (*mb_ptr2char)(char_u *p);

/* ---- attacker-controlled input stream (argv[1] file bytes, heap-allocated in main) ---- */
static unsigned char *g_input;
static size_t g_input_len;
static size_t g_input_pos;

/* vpeekc(): look at the next byte without consuming it; NUL (0) == "no more
 * input", exactly the sentinel bracketed_paste's `end == NULL` loop-exit test
 * expects. */
static int vpeekc(void)
{
    if (g_input_pos >= g_input_len)
        return NUL;
    return (int)g_input[g_input_pos];
}

/* vgetc(): consume and return the next byte. */
static int vgetc(void)
{
    if (g_input_pos >= g_input_len)
        return NUL;
    return (int)g_input[g_input_pos++];
}

/* find_termcode("PE"): no paste-end escape known (t_PE unset) -- a real,
 * legal vim state; bracketed_paste then reads "everything there is" and
 * relies purely on vpeekc()==NUL / Ctrl-C / got_int to stop, which is exactly
 * what drives this harness's termination. */
static char_u *find_termcode(char_u *name)
{
    (void)name;
    return NULL;
}

/* Real set_option_value() also redraws/triggers autocommands; none of that
 * touches gap/buf/idx, so a no-op stub is a faithful stand-in for this bug. */
static void set_option_value(char_u *name, long number, char_u *string, int opt_flags)
{
    (void)name; (void)number; (void)string; (void)opt_flags;
}

/* Only reachable via mode==PASTE_CMDLINE/PASTE_INSERT, never taken at
 * runtime here (mode is fixed to PASTE_EX) -- present only so the switch's
 * other cases link. */
static void put_on_cmdline(char_u *buf, int len, int redraw)
{
    (void)buf; (void)len; (void)redraw;
}
static int stop_arrow(void) { return OK; }
static void ins_eol(int c) { (void)c; }
static void ins_char_bytes(char_u *buf, int len) { (void)buf; (void)len; }
static void AppendToRedobuffLit(char_u *str, int len) { (void)str; (void)len; }

/* ---- real vim heap-growth machinery, ported verbatim from src/alloc.c:711-747
 * (ga_grow/ga_grow_inner) -- this IS the allocator bracketed_paste's PASTE_EX
 * case drives; noinline so the ASAN "allocated by" backtrace keeps
 * bracketed_paste as a distinct, attributable frame regardless of -O1
 * heuristics. */
static int ga_grow_inner(garray_T *gap, int n);
static int ga_grow(garray_T *gap, int n);

    __attribute__((noinline)) int
ga_grow(garray_T *gap, int n)
{
    if (gap->ga_maxlen - gap->ga_len < n)
	return ga_grow_inner(gap, n);
    return OK;
}

    __attribute__((noinline)) int
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

    new_len = gap->ga_itemsize * (gap->ga_len + n);
    pp = (char_u *)vim_realloc(gap->ga_data, new_len);
    if (pp == NULL)
	return FAIL;
    old_len = gap->ga_itemsize * gap->ga_maxlen;
    vim_memset(pp + old_len, 0, new_len - old_len);
    gap->ga_maxlen = gap->ga_len + n;
    gap->ga_data = pp;
    return OK;
}

/* ============================================================================
 * bracketed_paste() -- VERBATIM from data_cve/cve_0667332f/target/original_function.c
 * (src/edit.c:4401-4497 @ vul_commit 8d02ce1ed75d008c34a5c9aaa51b67cbb9d33ba).
 * Byte-identical splice below, do not hand-edit.
 * ============================================================================ */
int
bracketed_paste(paste_mode_T mode, int drop, garray_T *gap)
{
    int		c;
    char_u	buf[NUMBUFLEN + MB_MAXBYTES];
    int		idx = 0;
    char_u	*end = find_termcode((char_u *)"PE");
    int		ret_char = -1;
    int		save_allow_keys = allow_keys;
    int		save_paste = p_paste;

    // If the end code is too long we can't detect it, read everything.
    if (end != NULL && STRLEN(end) >= NUMBUFLEN)
	end = NULL;
    ++no_mapping;
    allow_keys = 0;
    if (!p_paste)
	// Also have the side effects of setting 'paste' to make it work much
	// faster.
	set_option_value((char_u *)"paste", TRUE, NULL, 0);

    for (;;)
    {
	// When the end is not defined read everything there is.
	if (end == NULL && vpeekc() == NUL)
	    break;
	do
	    c = vgetc();
	while (c == K_IGNORE || c == K_VER_SCROLLBAR || c == K_HOR_SCROLLBAR);
	if (c == NUL || got_int || (ex_normal_busy > 0 && c == Ctrl_C))
	    // When CTRL-C was encountered the typeahead will be flushed and we
	    // won't get the end sequence.  Except when using ":normal".
	    break;

	if (has_mbyte)
	    idx += (*mb_char2bytes)(c, buf + idx);
	else
	    buf[idx++] = c;
	buf[idx] = NUL;
	if (end != NULL && STRNCMP(buf, end, idx) == 0)
	{
	    if (end[idx] == NUL)
		break; // Found the end of paste code.
	    continue;
	}
	if (!drop)
	{
	    switch (mode)
	    {
		case PASTE_CMDLINE:
		    put_on_cmdline(buf, idx, TRUE);
		    break;

		case PASTE_EX:
		    if (gap != NULL && ga_grow(gap, idx) == OK)
		    {
			mch_memmove((char *)gap->ga_data + gap->ga_len,
							     buf, (size_t)idx);
			gap->ga_len += idx;
		    }
		    break;

		case PASTE_INSERT:
		    if (stop_arrow() == OK)
		    {
			c = buf[0];
			if (idx == 1 && (c == CAR || c == K_KENTER || c == NL))
			    ins_eol(c);
			else
			{
			    ins_char_bytes(buf, idx);
			    AppendToRedobuffLit(buf, idx);
			}
		    }
		    break;

		case PASTE_ONE_CHAR:
		    if (ret_char == -1)
		    {
			if (has_mbyte)
			    ret_char = (*mb_ptr2char)(buf);
			else
			    ret_char = buf[0];
		    }
		    break;
	    }
	}
	idx = 0;
    }

    --no_mapping;
    allow_keys = save_allow_keys;
    if (!save_paste)
	set_option_value((char_u *)"paste", FALSE, NULL, 0);

    return ret_char;
}

/* ============================================================================
 * main() -- reads argv[1] into a HEAP buffer (attacker-controlled bytes),
 * then reproduces the exact ex_getln.c call/consume pattern around
 * bracketed_paste(PASTE_EX, ...):
 *   - src/ex_getln.c:2847  `if (ga_grow(&line_ga, 40) == FAIL) break;`
 *                          (issued right before reading the char that turns
 *                          out to be K_PS, i.e. immediately before entering
 *                          bracketed_paste)
 *   - src/ex_getln.c:2874  `bracketed_paste(PASTE_EX, FALSE, &line_ga);`
 *   - src/ex_getln.c:2932-2933 (redraw:) `p = (char_u *)line_ga.ga_data;
 *                          p[line_ga.ga_len] = NUL;`
 * ============================================================================ */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 1;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    unsigned char *filebuf = (unsigned char *)malloc((size_t)(sz > 0 ? sz : 1));
    if (!filebuf) { fclose(f); return 1; }
    size_t got = (sz > 0) ? fread(filebuf, 1, (size_t)sz, f) : 0;
    fclose(f);

    g_input = filebuf;
    g_input_len = got;
    g_input_pos = 0;

    has_mbyte = 0;
    got_int = 0;
    ex_normal_busy = 0;
    allow_keys = 0;
    p_paste = 0;
    no_mapping = 0;

    garray_T gap;
    gap.ga_itemsize = 1;
    gap.ga_growsize = 30;
    gap.ga_len = 0;
    gap.ga_maxlen = 0;
    gap.ga_data = NULL;

    /* ex_getln.c's outer per-character loop primes 40 items of slack right
     * before every character read -- including the one that turns out to be
     * K_PS and dispatches into bracketed_paste(). */
    ga_grow(&gap, 40);

    (void)bracketed_paste(PASTE_EX, FALSE, &gap);

    if (gap.ga_data != NULL)
    {
        char_u *p = (char_u *)gap.ga_data;
        p[gap.ga_len] = NUL;    /* the real caller's post-call NUL-terminate */
    }

    free(gap.ga_data);
    free(filebuf);
    return 0;
}

/* cve_barebone direct-call harness for a vim shift_line() integer-overflow bug
 * (fixed by vim/vim@6bf131888a3d1de62bbfa8a7ea03c0ddccfd496e).
 * Target: shift_line  (src/ops.c)
 * Bug class: signed-integer-overflow (CWE-190) at `count += sw_val * amount;`
 *   In the "original vi indent" (round==FALSE), shift-right (left==FALSE) branch,
 *   shift_line multiplies the (int) shiftwidth value by the caller-supplied `amount`
 *   and adds it to `count` using plain `int` arithmetic, with no overflow guard.
 *   A large `amount` (e.g. the upstream regression test `V2147483647>`, i.e.
 *   amount == INT_MAX with shiftwidth 8) makes `sw_val * amount` overflow a
 *   32-bit signed int -> undefined behaviour, trapped here by UBSan's
 *   signed-integer-overflow check. The fix widens `count`/the product to
 *   `long long` and clamps to INT_MAX instead of overflowing.
 *
 * shift_line's own body performs no memory access beyond this arithmetic; the
 * function's real work is delegated to get_indent()/get_sw_value_indent() (read
 * editor state) and set_indent()/change_indent() (write the buffer line). None of
 * those are on the integer-overflow crash path, so they are faithful minimal
 * stubs (fixed values matching the upstream PoC's `setl sw=8` on a fresh,
 * zero-indent line) rather than reproductions of vim's full buffer/window model.
 * `curbuf`/`State` are likewise minimal stand-ins for globals shift_line reads
 * verbatim (`State & VREPLACE_FLAG`, `get_sw_value_indent(curbuf)`).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *   + harness.flags: -fsanitize=signed-integer-overflow -fno-sanitize-recover=signed-integer-overflow
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- minimal faithful stand-ins for the vim globals/macros shift_line reads
 * verbatim (real names/values, from src/vim.h + src/globals.h) ---- */
#define VREPLACE_FLAG	0x200	/* src/vim.h: Virtual-replace mode flag */
#define SIN_CHANGED	1	/* src/vim.h: set_indent() flag */
#define INDENT_SET	1	/* src/vim.h: change_indent() type */
#define NUL		'\000'	/* src/ascii.h */
#define FALSE		0
#define TRUE		1

/* buf_T is an opaque forward-declared struct in vim (src/structs.h); shift_line
 * only ever passes `curbuf` through to get_sw_value_indent(), never dereferences
 * it itself, so an opaque stand-in is faithful. */
typedef struct buf_T buf_T;
static buf_T *curbuf = NULL;

/* State defaults to MODE_NORMAL (src/globals.h/vim.h), which does not carry
 * VREPLACE_FLAG (0x200) -- matches the upstream PoC (normal-mode `V...>`). */
static int State = 0x01;

/* ---- faithful minimal stubs for the incidental (non-crash-path) callees ----
 * Real prototypes (src/indent.c / src/ops.c):
 *   long get_sw_value_indent(buf_T *buf);
 *   int  get_indent(void);
 *   int  set_indent(int size, int flags);
 *   void change_indent(int type, int amount, int round, int replaced, int call_changed_bytes);
 * shift_line only uses these for plumbing (read the effective 'shiftwidth' /
 * current indent, then commit the new indent to the buffer) -- none of that is
 * on the integer-overflow crash path, which is pure int arithmetic inside
 * shift_line's own body before any of these calls happen. get_sw_value_indent
 * fixed at 8 and get_indent fixed at 0 reproduce the upstream regression test's
 * `setl sw=8` on a fresh line (`setline(1, "abc")`, indent 0). */
long
get_sw_value_indent(buf_T *buf)
{
    (void)buf;
    return 8;
}

int
get_indent(void)
{
    return 0;
}

int
set_indent(int size, int flags)
{
    (void)size; (void)flags;
    return FALSE;
}

void
change_indent(int type, int amount, int round, int replaced, int call_changed_bytes)
{
    (void)type; (void)amount; (void)round; (void)replaced; (void)call_changed_bytes;
}

/* ==== VERBATIM from data_cve/cve_6027224e/target/original_function.c ==== */
void
shift_line(
    int	left,
    int	round,
    int	amount,
    int call_changed_bytes)	// call changed_bytes()
{
    int		count;
    int		i, j;
    int		sw_val = (int)get_sw_value_indent(curbuf);

    count = get_indent();	// get current indent

    if (round)			// round off indent
    {
	i = count / sw_val;	// number of 'shiftwidth' rounded down
	j = count % sw_val;	// extra spaces
	if (j && left)		// first remove extra spaces
	    --amount;
	if (left)
	{
	    i -= amount;
	    if (i < 0)
		i = 0;
	}
	else
	    i += amount;
	count = i * sw_val;
    }
    else		// original vi indent
    {
	if (left)
	{
	    count -= sw_val * amount;
	    if (count < 0)
		count = 0;
	}
	else
	    count += sw_val * amount;
    }

    // Set new indent
    if (State & VREPLACE_FLAG)
	change_indent(INDENT_SET, count, FALSE, NUL, call_changed_bytes);
    else
	(void)set_indent(count, call_changed_bytes ? SIN_CHANGED : 0);
}
/* ==== end verbatim ==== */

/* FDP-style byte layout (attacker-controlled input file):
 *   bytes[0..3]  int32 little-endian  -> amount  (shift_line's own "amount" param;
 *                                        matches the upstream PoC's V2147483647>)
 *   byte[4]      bit0                 -> left    (0 = shift right = the patched
 *                                        branch, 1 = shift left)
 * round and call_changed_bytes are fixed at 0/FALSE to stay on exactly the
 * branch the fix (6bf131888a3d1de62bbfa8a7ea03c0ddccfd496e) modified. Missing
 * bytes read as 0 (a 0-byte/short file is a valid, safe, no-op input). */
static int32_t
read_le32(const unsigned char *buf, size_t avail)
{
    unsigned char b[4] = {0, 0, 0, 0};
    size_t n = avail < 4 ? avail : 4;
    memcpy(b, buf, n);
    return (int32_t)((uint32_t)b[0] | ((uint32_t)b[1] << 8) |
		      ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24));
}

int
main(int argc, char **argv)
{
    if (argc < 2)
	return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
	return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the input so ASAN guards it (matches the parse_content_length
     * precedent). At least 1 byte so malloc(0) is never taken. */
    size_t cap = (size_t)sz > 0 ? (size_t)sz : 1;
    unsigned char *buf = (unsigned char *)malloc(cap);
    if (!buf) { fclose(f); return 0; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    int32_t amount = read_le32(buf, n);
    int left = (n >= 5) ? (buf[4] & 1) : 0;

    free(buf);

    shift_line(left, /* round = */ 0, amount, /* call_changed_bytes = */ 0);

    fprintf(stderr, "ok left=%d amount=%d\n", left, amount);
    return 0;
}

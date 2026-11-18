/* cve_barebone harness -- vim CVE-2023-0512 / adjust_skipcol() smoothscroll
 * divide-by-zero (CWE-369).
 *
 * adjust_skipcol() recomputes how much of the cursor's screen line is
 * scrolled off when 'wrap' + 'smoothscroll' are set and the cursor sits on
 * the top line (w_topline). It derives two screen-line widths,
 *     int width1 = curwin->w_width - curwin_col_off();
 *     int width2 = width1 + curwin_col_off2();
 * and later does
 *     row += col / width2;
 *     col  = col % width2;
 * with no check that width2 isn't zero. A sufficiently narrow window (e.g.
 * several vertical splits, as in the upstream regression test) drives
 * width1 <= 0; once the column-offset contributions cancel out exactly,
 * width2 lands on 0 and the division is an integer divide-by-zero --
 * caught by the hardware SIGFPE trap (relayed by AddressSanitizer's
 * handle_sigfpe) right inside adjust_skipcol()'s own body. The fix
 * (870219c58c0804bdc55419b2e455c06ac715a835) adds
 * "if (width1 <= 0) return;  // no text will be displayed" immediately
 * after width1 is computed.
 *
 * Isolated reproduction: adjust_skipcol() takes NO arguments -- its whole
 * "input" is curwin (the current window) plus a handful of getter/
 * validator calls that normally derive window-decoration widths from
 * buffer/option/fold/diff state. Reproducing that machinery is not needed
 * to trip the bug: those getters are exactly the numbers adjust_skipcol
 * combines, so this harness builds a minimal, real-named win_T (structs.h
 * "struct window_S", real field names/types, only the fields
 * adjust_skipcol itself touches -- the real struct carries ~200 more
 * fields for folds/diff/popup/quickfix/statuscolumn/... state this
 * function never reads) and feeds every value adjust_skipcol reads/calls
 * directly from the input file, then calls adjust_skipcol() exactly as
 * vim's screen-update code does (curs_columns() / win_update() etc.).
 *
 * TRIGGER: 'wrap'+'smoothscroll' on, cursor on the top line, the "line
 *          just fits" shortcut NOT taken, width1 computes to <= 0 AND
 *          width1 + curwin_col_off2() computes to EXACTLY 0, and the
 *          on-screen column (from w_virtcol) is > 0 -> "col / width2"
 *          divides by zero inside adjust_skipcol().
 * SAFE:    the same code but width2 lands non-zero (a normal window
 *          size), or col is exactly 0 (so the divide is never reached),
 *          or one of the early-return guards fires ('wrap'/'smoothscroll'
 *          off, cursor off the top line, or the "line just fits" path).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real vim base typedefs (structs.h) ---- */
typedef long	linenr_T;	// structs.h
typedef int	colnr_T;	// structs.h

/* ---- real pos_T (structs.h, verbatim -- "Position in file or buffer.") ---- */
typedef struct
{
    linenr_T	lnum;	// line number
    colnr_T	col;	// column number
    colnr_T	coladd; // extra virtual column
} pos_T;

/* ---- real boolean constants (vim.h) ---- */
#define FALSE	0	    // note: this is an int, not a long!
#define TRUE	1

/* ---- real UPD_* redraw-type constants (vim.h) that adjust_skipcol() /
 * reset_skipcol() pass to redraw_later() -- only their identity matters
 * here, redraw_later() itself is a bookkeeping-only stub (see below). ---- */
#define UPD_SOME_VALID		35  // like UPD_NOT_VALID but may scroll
#define UPD_NOT_VALID		40  // buffer needs complete redraw

/* ---- minimal faithful win_T (structs.h: "typedef struct window_S win_T",
 * real field names/types) -- only the fields adjust_skipcol() itself
 * reads or writes. The real struct carries ~200 more fields (folds, diff,
 * popup, quickfix, sign, statuscolumn, ... state) this function never
 * touches. ---- */
typedef struct
{
    int		wo_wrap;	// structs.h winopt_T: 'wrap'
    int		wo_sms;		// structs.h winopt_T: 'smoothscroll'
} winopt_T;

typedef struct window_S win_T;
struct window_S
{
    winopt_T	w_onebuf_opt;
    pos_T	w_cursor;	    // cursor position in buffer
    linenr_T	w_topline;	    // buffer line number of the line at the
				    // top of the window
    int		w_height;	    // number of rows in window, excluding
				    // status/command line
    int		w_width;	    // width of window, excluding separation
    int		w_cline_height;	    // current size of cursor line
    colnr_T	w_virtcol;	    // column number of the cursor in the
				    // screen line
    colnr_T	w_skipcol;	    // starting screen column for the first line
};

/* real macros (structs.h) */
#define w_p_wrap	w_onebuf_opt.wo_wrap	// 'wrap'
#define w_p_sms		w_onebuf_opt.wo_sms	// 'smoothscroll'

/* real global (globals.h: "EXTERN win_T *curwin;  // currently active window") */
win_T *curwin;

/* ---- craft-controlled substitutes for the values adjust_skipcol's
 * callees would normally derive from folds/'number'/'signcolumn'/
 * 'scrolloff' state; set from the input file in main(). ---- */
static int32_t	g_col_off1  = 0;
static int32_t	g_col_off2  = 0;
static long	g_scrolloff = 0;
static int	g_plines    = 0;

/* ---- minimal faithful stubs, real names/signatures (proto.h) -- these
 * are the four getter/validator calls adjust_skipcol() makes. Their own
 * bodies (win_col_off()'s number/sign/fold-column arithmetic,
 * validate_virtcol()'s getvvcol() screen-layout walk, plines_win()'s
 * fold/diff fill-line count) are off adjust_skipcol's own crash path --
 * adjust_skipcol only ever consumes the VALUE each returns / the field
 * each updates, which main() sets directly to the value this run wants
 * to exercise. ---- */
    int
curwin_col_off(void)
{
    return g_col_off1;
}

    int
curwin_col_off2(void)
{
    return g_col_off2;
}

    long
get_scrolloff_value(void)
{
    return g_scrolloff;
}

    void
validate_cheight(void)
{
    // real body recomputes curwin->w_cline_height from fold/diff state;
    // main() already set it to the value this run wants to exercise.
}

    void
validate_virtcol(void)
{
    // real body recomputes curwin->w_virtcol via getvvcol(); main()
    // already set it to the value this run wants to exercise.
}

    int
plines_win(win_T *wp, linenr_T lnum, int winheight)
{
    (void)wp; (void)lnum; (void)winheight;
    return g_plines;
}

    void
redraw_later(int type)
{
    (void)type;	  // real body only updates window redraw-type bookkeeping
		  // (w_redr_type / must_redraw) that adjust_skipcol never
		  // reads back.
}

/* ---- reset_skipcol: VERBATIM (src/move.c, lines 244-256) -- the one real
 * callee on adjust_skipcol's "line just fits" early-return path. ---- */
    static void
reset_skipcol(void)
{
    if (curwin->w_skipcol == 0)
	return;

    curwin->w_skipcol = 0;

    // Should use the least expensive way that displays all that changed.
    // UPD_NOT_VALID is too expensive, UPD_REDRAW_TOP does not redraw
    // enough when the top line gets another screen line.
    redraw_later(UPD_SOME_VALID);
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
__attribute__((noinline))
void
adjust_skipcol(void)
{
    if (!curwin->w_p_wrap
	    || !curwin->w_p_sms
	    || curwin->w_cursor.lnum != curwin->w_topline)
	return;

    int	    width1 = curwin->w_width - curwin_col_off();
    int	    width2 = width1 + curwin_col_off2();
    long    so = get_scrolloff_value();
    int	    scrolloff_cols = so == 0 ? 0 : width1 + (so - 1) * width2;
    int	    scrolled = FALSE;

    validate_cheight();
    if (curwin->w_cline_height == curwin->w_height
	    // w_cline_height may be capped at w_height, check there aren't
	    // actually more lines.
	    && plines_win(curwin, curwin->w_cursor.lnum, FALSE)
							   <= curwin->w_height)
    {
	// the line just fits in the window, don't scroll
	reset_skipcol();
	return;
    }

    validate_virtcol();
    while (curwin->w_skipcol > 0
		 && curwin->w_virtcol < curwin->w_skipcol + 3 + scrolloff_cols)
    {
	// scroll a screen line down
	if (curwin->w_skipcol >= width1 + width2)
	    curwin->w_skipcol -= width2;
	else
	    curwin->w_skipcol -= width1;
	redraw_later(UPD_NOT_VALID);
	scrolled = TRUE;
	validate_virtcol();
    }
    if (scrolled)
	return;  // don't scroll in the other direction now

    int col = curwin->w_virtcol - curwin->w_skipcol + scrolloff_cols;
    int row = 0;
    if (col >= width1)
    {
	col -= width1;
	++row;
    }
    if (col > width2)
    {
	row += col / width2;
	col = col % width2;
    }
    if (row >= curwin->w_height)
    {
	if (curwin->w_skipcol == 0)
	{
	    curwin->w_skipcol += width1;
	    --row;
	}
	if (row >= curwin->w_height)
	    curwin->w_skipcol += (row - curwin->w_height) * width2;
	redraw_later(UPD_NOT_VALID);
    }
}

/* ================= driver ================= */
static int32_t
rd_i32(const unsigned char *p)
{
    int32_t v;
    memcpy(&v, p, sizeof v);
    return v;
}

/* Input layout (29 bytes, all fields little-endian, missing bytes read as
 * 0 -- see the crafting script for the exact per-input rationale):
 *   [0]     flags: bit0=w_p_wrap bit1=w_p_sms bit2=(lnum==topline)
 *                  bit3=force w_cline_height==w_height ("just fits" try)
 *   [1..4]  int32  w_width
 *   [5..8]  int32  col_off1   (curwin_col_off() return)
 *   [9..12] int32  col_off2   (curwin_col_off2() return)
 *   [13..16] int32 w_height
 *   [17..20] int32 cline_delta (w_cline_height = w_height + delta, when
 *                                bit3 is clear)
 *   [21..24] int32 plines_val (plines_win() return, when bit3 is set)
 *   [25..28] int32 w_virtcol
 */
int
main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;
    unsigned char *args = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    size_t got = fread(args, 1, n, fp);
    fclose(fp);

    unsigned char hdr[32];
    memset(hdr, 0, sizeof hdr);
    size_t take = got < sizeof hdr ? got : sizeof hdr;
    memcpy(hdr, args, take);
    free(args);

    unsigned char flags  = hdr[0];
    int32_t f_width      = rd_i32(hdr + 1);
    int32_t f_coloff1    = rd_i32(hdr + 5);
    int32_t f_coloff2    = rd_i32(hdr + 9);
    int32_t f_height     = rd_i32(hdr + 13);
    int32_t f_clinedelta = rd_i32(hdr + 17);
    int32_t f_plines     = rd_i32(hdr + 21);
    int32_t f_virtcol    = rd_i32(hdr + 25);

    win_T win;
    memset(&win, 0, sizeof win);
    curwin = &win;

    curwin->w_p_wrap      = (flags & 0x01) ? TRUE : FALSE;
    curwin->w_p_sms       = (flags & 0x02) ? TRUE : FALSE;
    curwin->w_topline     = 10;
    curwin->w_cursor.lnum = (flags & 0x04) ? curwin->w_topline : curwin->w_topline + 1;
    curwin->w_width       = f_width;
    curwin->w_height      = f_height;
    curwin->w_skipcol     = 0;               /* freshly (re)drawn window: nothing scrolled yet */
    curwin->w_virtcol     = f_virtcol;

    g_col_off1  = f_coloff1;
    g_col_off2  = f_coloff2;
    g_scrolloff = 0;
    g_plines    = f_plines;

    if (flags & 0x08)
	curwin->w_cline_height = curwin->w_height;                 /* "line just fits" candidate */
    else
	curwin->w_cline_height = curwin->w_height + f_clinedelta;  /* generally != w_height */

    /* volatile function pointer: forbid the compiler from proving away / hoisting the call. */
    void (*volatile fn)(void) = adjust_skipcol;
    fn();

    return 0;
}

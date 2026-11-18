/*
 * cve_barebone direct-call harness for vim's adjust_plines_for_skipcol
 * (src/move.c). Bug: CVE fixed by cb0b99f0672d8446585d26e998343dceca17d1ce
 * — a missing "w2 > 0" guard lets the divisor
 * (width + win_col_off2(wp)) reach 0, causing an integer division by zero
 * (CWE-369) inside adjust_plines_for_skipcol's own body.
 *
 * The real win_col_off()/win_col_off2() (src/move.c) are reproduced VERBATIM
 * below, compiled WITHOUT FEAT_FOLDING / FEAT_SIGNS defined (a real vim
 * compile-time feature configuration — the exact #ifdef guards already in
 * the source), so the fold-column / sign-column terms are simply the
 * (real, unmodified) code's own opt-out path rather than an invented stub.
 * With 'number'/'relativenumber' left off in every corpus input, both
 * functions reduce, via their OWN real logic, to depending only on
 * wp->w_width — which the harness controls directly from the input file.
 *
 * number_width()/vim_strchr() remain referenced in win_col_off2()'s dead
 * (nu==0) branch purely so the verbatim callees link; they are never
 * invoked at runtime for any corpus input here (short-circuited by
 * wp->w_p_nu || wp->w_p_rnu == 0), so minimal stand-ins are used for them.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- real vim typedefs (src/vim.h / src/structs.h), copied verbatim ---- */
typedef long   linenr_T;   // line number type
typedef int    colnr_T;    // column number type
typedef unsigned char char_u;

/* ---- minimal real-named window/option structs (only the fields the
 * target function and its two direct callees touch) ---- */
typedef struct
{
    int wo_nu;
    int wo_rnu;
} winopt_T;

typedef struct window_S win_T;
struct window_S
{
    winopt_T    w_onebuf_opt;
    colnr_T     w_skipcol;     // starting screen column for the first
                                // line in the window; used when 'wrap' is
                                // on; does not include win_col_off()
    int         w_width;       // Width of window, excluding separation.
};

/* real macros, src/structs.h */
#define w_p_nu  w_onebuf_opt.wo_nu	// 'number'
#define w_p_rnu w_onebuf_opt.wo_rnu	// 'relativenumber'

/* real option constant, src/option.h */
#define CPO_NUMCOL	'n'	// 'number' column also used for text

/* globals win_col_off()/win_col_off2() reference (src/globals.h /
 * src/move.c); values match vim's real defaults (no cmdline window open,
 * empty 'cpoptions' as far as CPO_NUMCOL is concerned). */
int cmdwin_type = 0;
static win_T dummy_curwin;
win_T *curwin = &dummy_curwin;
char_u *p_cpo = (char_u *)"";

/* minimal faithful stand-ins for callees that are incidental here: with
 * 'number'/'relativenumber' off on every corpus input, the (wp->w_p_nu ||
 * wp->w_p_rnu) guard in both win_col_off() and win_col_off2() below is
 * always false, so neither of these is ever actually called (short
 * circuited) — they exist only so the verbatim callees link. */
static int number_width(win_T *wp) { (void)wp; return 4; }
static char_u *vim_strchr(char_u *string, int c) { return (char_u *)strchr((char *)string, c); }

int adjust_plines_for_skipcol(win_T *wp) __attribute__((noinline));

/* ---- src/move.c, verbatim (compiled with FEAT_FOLDING / FEAT_SIGNS
 * undefined, so the ifdef'd fold-column / sign-column terms below are
 * omitted by the same #ifdef guards vim itself ships) ---- */

    int
win_col_off(win_T *wp)
{
    return (((wp->w_p_nu || wp->w_p_rnu) ? number_width(wp) + 1 : 0)
	    + (cmdwin_type == 0 || wp != curwin ? 0 : 1)
#ifdef FEAT_FOLDING
	    + wp->w_p_fdc
#endif
#ifdef FEAT_SIGNS
	    + (signcolumn_on(wp) ? 2 : 0)
#endif
	   );
}

    int
curwin_col_off(void)
{
    return win_col_off(curwin);
}

    int
win_col_off2(win_T *wp)
{
    if ((wp->w_p_nu || wp->w_p_rnu) && vim_strchr(p_cpo, CPO_NUMCOL) != NULL)
	return number_width(wp) + 1;
    return 0;
}

/* ---- target function, byte-for-byte from
 * data_cve/cve_5381542d/target/original_function.c ---- */
int
adjust_plines_for_skipcol(win_T *wp)
{
    if (wp->w_skipcol == 0)
	return 0;

    int width = wp->w_width - win_col_off(wp);
    if (wp->w_skipcol >= width)
	return (wp->w_skipcol - width) / (width + win_col_off2(wp)) + 1;

    return 0;
}

/* ---- harness driver ---- */
int
main(int argc, char **argv)
{
    if (argc < 2)
	return 1;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
	return 1;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0)
	sz = 0;
    fseek(f, 0, SEEK_SET);

    /* heap-allocate the input buffer so ASAN guards any out-of-bounds
     * access by the (bounds-checked) parsing below */
    unsigned char *buf = malloc(sz > 0 ? (size_t)sz : 1);
    if (!buf)
    {
	fclose(f);
	return 1;
    }
    size_t rd = sz > 0 ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);

    int32_t width_raw = 0;
    int32_t skipcol_raw = 0;
    if (rd >= 4)
	memcpy(&width_raw, buf, 4);
    if (rd >= 8)
	memcpy(&skipcol_raw, buf + 4, 4);
    free(buf);

    win_T win;
    memset(&win, 0, sizeof(win));
    win.w_p_nu = 0;
    win.w_p_rnu = 0;
    win.w_width = (int)width_raw;
    win.w_skipcol = (colnr_T)skipcol_raw;

    int result = adjust_plines_for_skipcol(&win);
    printf("adjust_plines_for_skipcol result=%d width=%d skipcol=%d\n",
	   result, win.w_width, win.w_skipcol);
    return 0;
}

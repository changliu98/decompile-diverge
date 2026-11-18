/* cve_barebone harness -- CVE-2021-27135 / xterm-snapshots SaltTextAway
 * combining-char heap-buffer overflow (CWE-787).
 *
 * Isolated reproduction: SaltTextAway() is the routine xterm uses to copy the selected
 * on-screen text into an internal SelectedCells buffer before handing it to the X selection /
 * clipboard machinery. Its buffer-size estimate ("need *= 4", 4 UTF-8 bytes per selected
 * cell) does not account for stacked Unicode combining characters, which SaveText() also
 * converts to UTF-8 and appends -- so a selection over cells carrying several combining marks
 * makes SaveText() write past the buffer SaltTextAway allocated.
 *
 * This harness builds ONE synthetic screen row (real LineData/TScreen field names, trimmed to
 * only the fields this call chain reads) with K selected cells, each holding a 1-byte ASCII
 * base character plus 0..5 stacked COMBINING ACUTE ACCENT (U+0301, 2 UTF-8 bytes) marks, and
 * calls SaltTextAway() directly with a same-row selection spanning those cells -- exactly the
 * call SaltTextAway's real callers (EditorButton/ComputeSelect/TrackText/etc, all deep
 * GUI/X11 event-handling code with no bearing on this bug) eventually make.
 *
 * getLineData() -- linedata.c's real scrollback/circular-buffer index resolver, pure
 * bookkeeping with no bearing on the overflow arithmetic -- is replaced by a trivial accessor
 * returning the one fabricated row, preserving the real (TScreen*, row) -> LineData* contract
 * GET_LINEDATA()/Length()/SaveText() rely on. Length()/SaveText()/LastTextCol()/convertToUTF8()
 * -- the actual buggy size computation and the writer that overflows -- are pasted VERBATIM
 * from button.c/ptydata.c, each kept noinline so the ASAN report keeps real stack frames.
 *
 * Input format (see the corpus builder at the bottom of this generator):
 *   byte[0]   = K_raw  -> K = 1 + (K_raw % 96)                  selected-cell count, 1..96
 *   byte[1..] = one fill-count byte per cell (cycled if the file has fewer than K of them):
 *               fill_i = byte[1 + (i % navail)] % 6             combining marks on cell i, 0..5
 * Accounting (uniform fill f over K cells): allocated = 4*K+1; actual = K*(1+2*f) [+1 final
 * NUL]. f<=1 -> actual <= 3K+1 < 4K+1 for every K>=1 (SAFE, margin >= K). f>=2 -> actual >=
 * 5K+1 > 4K+1 for every K>=1 (TRIGGERING, overflow >= K-1 bytes) -- see gen_dc_cve_3ec7ab1e.py
 * corpus() for the exact (K, fill) pairs used.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

/* ---------------------------------------------------------------------------------------
 * Real xterm compile-time feature flags (ptyx.h/xterm.h defaults). OPT_WIDE_CHARS is the
 * load-bearing one -- it gates the vulnerable "need *= 4" line and the UTF-8 write path, and
 * is xterm's real default (ptyx.h:824), and a required precondition of this CVE. The others
 * are turned off purely to drop subsystems SaltTextAway/Length/SaveText/LastTextCol never
 * touch (DEC double-width charset trimming, ISO per-cell color storage, debug tracing) --
 * none of them appear anywhere in the arithmetic this bug lives in.
 *
 * NOTE: the verbatim function bodies below still carry their original "#if OPT_WIDE_CHARS" /
 * "#if OPT_DEC_CHRSET" preprocessor guards (untouched, part of the verbatim text). An
 * undefined macro reads as 0 in "#if", so OPT_WIDE_CHARS MUST be explicitly #defined 1 here
 * or the entire UTF-8/combining-char branch (the bug itself) is silently compiled OUT and
 * SaveText falls back to its single-byte-per-cell non-wide-chars "else" arm. OPT_DEC_CHRSET
 * is deliberately left undefined (-> 0 -> off): its guarded lines only halve/double column
 * indices for double-width DEC charsets, never touched by this bug.
 * --------------------------------------------------------------------------------------- */
#define OPT_WIDE_CHARS 1              /* real default, ptyx.h:824; required precondition of the CVE */
#define HIDDEN_CHAR 0xffff            /* real, xterm.h:287 (OPT_WIDE_CHARS) */

/* ---- real base typedefs (ptyx.h) ---- */
typedef unsigned char Char;           /* ptyx.h:314 */
typedef unsigned IChar;               /* ptyx.h:1668, OPT_WIDER_ICHAR (real default, ptyx.h:827) */
typedef IChar CharData;               /* ptyx.h:1817 */
typedef unsigned short IAttr;         /* ptyx.h:1652, OPT_WIDE_ATTRS (real default, ptyx.h:819) */
typedef unsigned short Dimension;     /* real Xt typedef */
typedef unsigned char Boolean;        /* real Xt typedef */
typedef Char RowData;                 /* ptyx.h:1804 */

#define CharOf(n) ((Char)(n))         /* ptyx.h:339, verbatim */
#define E2A(a) (a)                    /* ptyx.h:1601, verbatim (non-EBCDIC) */
#define A2E(a) (a)                    /* ptyx.h:1602, verbatim (non-EBCDIC) */
#define uFalse 0                      /* Xt False */

#define xBIT(n) (1 << (n))            /* ptyx.h:356, verbatim */
#define AttrBIT(n) xBIT(n)            /* ptyx.h:3341, verbatim */
#define CHARDRAWN AttrBIT(7)          /* ptyx.h:3355, verbatim */

#define EXCHANGE(a,b,tmp) tmp = a; a = b; b = tmp     /* ptyx.h:489, verbatim */
#define isSameRow(a,b) ((a)->row == (b)->row)         /* ptyx.h:352, verbatim */

#define BITS2MASK(b) ((1 << b) - 1)                          /* ptyx.h:1776, verbatim */
#define LINEFLAG_BITS 4                                       /* ptyx.h:1806, verbatim */
#define LINEFLAG_MASK BITS2MASK(LINEFLAG_BITS)                /* ptyx.h:1807, verbatim */
#define GetLineFlags(ld) ((ld)->bufHead & LINEFLAG_MASK)      /* ptyx.h:1809, verbatim */
#define LINEWRAPPED AttrBIT(0)                                 /* ptyx.h:3428, verbatim */
#define LineTstFlag(ld, flag) ((GetLineFlags(ld) & flag) != 0) /* xterm.h:1437, verbatim */
#define LineTstWrapped(ld) LineTstFlag(ld, LINEWRAPPED)        /* xterm.h:1447, verbatim */

#define MAX_SELECTION_CODES 3          /* real enum value, ptyx.h:1190-1194 (PRIMARY/CLIPBOARD/SECONDARY) */
#define MAX_CUT_BUFFER 8                /* ptyx.h:2806, verbatim */
#define MAX_SELECTIONS (MAX_SELECTION_CODES + MAX_CUT_BUFFER)  /* ptyx.h:2807, verbatim (== 11) */

#define if_OPT_WIDE_CHARS(screen, code) if(screen->wide_chars) code   /* ptyx.h:1663, verbatim (OPT_WIDE_CHARS branch) */

#define TRACE(p) /* nothing */         /* real fallback, trace.h:168 (OPT_TRACE==0, real default ptyx.h:804) */

/* ---- real structs (ptyx.h), trimmed to the fields SaltTextAway/Length/SaveText/LastTextCol/
 * convertToUTF8 actually dereference; the real TScreen has ~250 GUI/X11/pty-state fields this
 * call chain never reads. ---- */
typedef struct {
    int row;
    int col;
} CELL;                                        /* ptyx.h:341-344, verbatim */

typedef struct {
    Char  *data_buffer;
    size_t data_limit;
    size_t data_length;
} SelectedCells;                               /* ptyx.h:346-350, verbatim */

typedef struct {
    Dimension lineSize;
    RowData   bufHead;
    Char      combSize;
    IAttr     *attribs;
    CharData  *charData;
    CharData  *combData[1];                    /* real flexible-array-of-pointers idiom, ptyx.h:1822-1834 */
} LineData;
typedef const LineData CLineData;              /* ptyx.h:1836, verbatim */

#define for_each_combData(off, ld) for (off = 0; off < ld->combSize; ++off)  /* ptyx.h:1854, verbatim */
#define SizeOfLineData offsetof(LineData, combData)                          /* ptyx.h:1888, verbatim */

typedef struct {
    int max_col;
    int max_row;
    int topline;
    int savedlines;
    int max_combining;
    int utf8_nrc_mode;
    int utf8_mode;
    Boolean wide_chars;
    Boolean trim_selection;
    SelectedCells selected_cells[MAX_SELECTIONS];
} TScreen;                                     /* real field names/types, ptyx.h:2373-2808 (subset) */

#define TScreenOf(xw) (&(xw)->screen)          /* ptyx.h:3471, verbatim */
#define ROW2INX(screen, row) ((row) + (screen)->topline)      /* ptyx.h:1895, verbatim */
#define okScrnRow(screen, row) \
    ((row) <= ((screen)->max_row - (screen)->topline) \
  && (row) >= -((screen)->savedlines))          /* ptyx.h:1904-1906, verbatim */

typedef struct _XtermWidgetRec {
    TScreen screen;                             /* ptyx.h:3298, verbatim */
} XtermWidgetRec, *XtermWidget;                 /* ptyx.h:3288-3319 (subset) */

#define ERROR_BMALLOC2 71                       /* error.h:94, real value ("SaltTextAway: malloc() failed") */
static void SysError(int code)                  /* misc.c:6031 is real (prints + exits); this call site is
                                                  * unreachable here (our mallocs never return NULL) --
                                                  * minimal faithful stub for an off-crash-path error path. */
{
    fprintf(stderr, "SysError(%d)\n", code);
    exit(1);
}

/* DECtoASCII (button.c:1634-1642) is only reached from SaveText's non-UTF-8 "else" arm, which
 * is provably dead in this harness (utf8_mode is always nonzero, set in main() below) but the
 * arm is real C code, not a discarded macro argument, so it must still compile; minimal
 * faithful stub -- the real table only remaps 8 DEC-graphics codepoints below 0x20. */
static unsigned DECtoASCII(unsigned ch) { return ch; }

/* isWide() (xterm.h:955, real font-metric double-width lookup) is only reached from SaveText's
 * `c == HIDDEN_CHAR` arm, which this harness never exercises (no cell is ever given the
 * HIDDEN_CHAR sentinel value) but which must still compile; minimal stub. */
#define isWide(n) (0)

/* ---- getLineData: NOT real -- linedata.c's real getLineData() resolves scrollback/circular-
 * buffer indices, pure bookkeeping with no bearing on the overflow arithmetic. Replaced by a
 * direct accessor into the one synthetic row main() builds, preserving the real
 * (TScreen*, row-index) -> LineData* contract that GET_LINEDATA()/Length()/SaveText() rely
 * on. ---- */
static LineData *g_row;
static LineData *getLineData(TScreen *screen, int inx) { (void) screen; (void) inx; return g_row; }
#define GET_LINEDATA(screen, row) getLineData(screen, ROW2INX(screen, row))  /* button.c:134-135, verbatim */

/* ================= convertToUTF8: VERBATIM (ptydata.c:456-497) =================
 * The routine that actually performs the out-of-bounds writes once SaveText()'s loop runs
 * past the allocated buffer. noinline so it (and SaveText/LastTextCol/Length/SaltTextAway
 * below) keep real stack frames in the ASAN report. */
__attribute__((noinline))
Char *
convertToUTF8(Char *lp, unsigned c)
{
#define CH(n) (Char)((c) >> ((n) * 8))
    if (c < 0x80) {
	/*  0*******  */
	*lp++ = (Char) CH(0);
    } else if (c < 0x800) {
	/*  110***** 10******  */
	*lp++ = (Char) (0xc0 | (CH(0) >> 6) | ((CH(1) & 0x07) << 2));
	*lp++ = (Char) (0x80 | (CH(0) & 0x3f));
    } else if (c < 0x00010000) {
	/*  1110**** 10****** 10******  */
	*lp++ = (Char) (0xe0 | ((int) (CH(1) & 0xf0) >> 4));
	*lp++ = (Char) (0x80 | (CH(0) >> 6) | ((CH(1) & 0x0f) << 2));
	*lp++ = (Char) (0x80 | (CH(0) & 0x3f));
    } else if (c < 0x00200000) {
	*lp++ = (Char) (0xf0 | ((int) (CH(2) & 0x1f) >> 2));
	*lp++ = (Char) (0x80 |
			((int) (CH(1) & 0xf0) >> 4) |
			((int) (CH(2) & 0x03) << 4));
	*lp++ = (Char) (0x80 | (CH(0) >> 6) | ((CH(1) & 0x0f) << 2));
	*lp++ = (Char) (0x80 | (CH(0) & 0x3f));
    } else if (c < 0x04000000) {
	*lp++ = (Char) (0xf8 | (CH(3) & 0x03));
	*lp++ = (Char) (0x80 | (CH(2) >> 2));
	*lp++ = (Char) (0x80 |
			((int) (CH(1) & 0xf0) >> 4) |
			((int) (CH(2) & 0x03) << 4));
	*lp++ = (Char) (0x80 | (CH(0) >> 6) | ((CH(1) & 0x0f) << 2));
	*lp++ = (Char) (0x80 | (CH(0) & 0x3f));
    } else {
	*lp++ = (Char) (0xfc | ((int) (CH(3) & 0x40) >> 6));
	*lp++ = (Char) (0x80 | (CH(3) & 0x3f));
	*lp++ = (Char) (0x80 | (CH(2) >> 2));
	*lp++ = (Char) (0x80 | (CH(1) >> 4) | ((CH(2) & 0x03) << 4));
	*lp++ = (Char) (0x80 | (CH(0) >> 6) | ((CH(1) & 0x0f) << 2));
	*lp++ = (Char) (0x80 | (CH(0) & 0x3f));
    }
    return lp;
#undef CH
}

/* ================= LastTextCol: VERBATIM (button.c:3381-3406) ================= */
__attribute__((noinline))
/*
 * Find the last column at which text was drawn on the given row.
 */
static int
LastTextCol(TScreen *screen, CLineData *ld, int row)
{
    int i = -1;

    if (ld != 0) {
	if (okScrnRow(screen, row)) {
	    const IAttr *ch;
	    for (i = screen->max_col,
		 ch = ld->attribs + i;
		 i >= 0 && !(*ch & CHARDRAWN);
		 ch--, i--) {
		;
	    }
#if OPT_DEC_CHRSET
	    if (CSET_DOUBLE(GetLineDblCS(ld))) {
		i *= 2;
	    }
#endif
	}
    }
    return (i);
}

/* ================= Length: VERBATIM (button.c:5008-5022) ================= */
__attribute__((noinline))
/* returns number of chars in line from scol to ecol out */
/* ARGSUSED */
static int
Length(TScreen *screen,
       int row,
       int scol,
       int ecol)
{
    CLineData *ld = GET_LINEDATA(screen, row);
    const int lastcol = LastTextCol(screen, ld, row);

    if (ecol > lastcol)
	ecol = lastcol;
    return (ecol - scol + 1);
}

/* ================= SaveText: VERBATIM (button.c:5024-5115) -- the writer that overflows ===== */
__attribute__((noinline))
/* copies text into line, preallocated */
static Char *
SaveText(TScreen *screen,
	 int row,
	 int scol,
	 int ecol,
	 Char *lp,		/* pointer to where to put the text */
	 int *eol)
{
    LineData *ld;
    int i = 0;
    Char *result = lp;
#if OPT_WIDE_CHARS
    unsigned previous = 0;
#endif

    ld = GET_LINEDATA(screen, row);
    i = Length(screen, row, scol, ecol);
    ecol = scol + i;
#if OPT_DEC_CHRSET
    if (CSET_DOUBLE(GetLineDblCS(ld))) {
	scol = (scol + 0) / 2;
	ecol = (ecol + 1) / 2;
    }
#endif
    *eol = !LineTstWrapped(ld);
    for (i = scol; i < ecol; i++) {
	unsigned c;
	assert(i < (int) ld->lineSize);
	c = E2A(ld->charData[i]);
#if OPT_WIDE_CHARS
	/* We want to strip out every occurrence of HIDDEN_CHAR AFTER a
	 * wide character.
	 */
	if (c == HIDDEN_CHAR) {
	    if (isWide((int) previous)) {
		previous = c;
		/* Combining characters attached to double-width characters
		   are in memory attached to the HIDDEN_CHAR */
		if_OPT_WIDE_CHARS(screen, {
		    if ((screen->utf8_nrc_mode | screen->utf8_mode) != uFalse) {
			size_t off;
			for_each_combData(off, ld) {
			    unsigned ch = ld->combData[off][i];
			    if (ch == 0)
				break;
			    lp = convertToUTF8(lp, ch);
			}
		    }
		});
		continue;
	    } else {
		c = ' ';	/* should not happen, but just in case... */
	    }
	}
	previous = c;
	if ((screen->utf8_nrc_mode | screen->utf8_mode) != uFalse) {
	    lp = convertToUTF8(lp, (c != 0) ? c : ' ');
	    if_OPT_WIDE_CHARS(screen, {
		size_t off;
		for_each_combData(off, ld) {
		    unsigned ch = ld->combData[off][i];
		    if (ch == 0)
			break;
		    lp = convertToUTF8(lp, ch);
		}
	    });
	} else
#endif
	{
	    if (c == 0) {
		c = E2A(' ');
	    } else if (c < E2A(' ')) {
		c = DECtoASCII(c);
	    } else if (c == 0x7f) {
		c = 0x5f;
	    }
	    *lp++ = CharOf(A2E(c));
	}
	if (c != E2A(' '))
	    result = lp;
    }

    /*
     * If requested, trim trailing blanks from selected lines.  Do not do this
     * if the line is wrapped.
     */
    if (!*eol || !screen->trim_selection)
	result = lp;

    return (result);
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline so it keeps its own frame (dc_batch requires the target function name in the
 * ASAN backtrace). */
__attribute__((noinline))
static void
SaltTextAway(XtermWidget xw,
	     int which,
	     CELL *cellc,
	     CELL *cell)
{
    TScreen *screen = TScreenOf(xw);
    SelectedCells *scp;
    int i;
    int eol;
    int need = 0;
    Char *line;
    Char *lp;
    CELL first = *cellc;
    CELL last = *cell;

    if (which < 0 || which >= MAX_SELECTIONS) {
	TRACE(("SaltTextAway - which selection?\n"));
	return;
    }
    scp = &(screen->selected_cells[which]);

    TRACE(("SaltTextAway which=%d, first=%d,%d, last=%d,%d\n",
	   which, first.row, first.col, last.row, last.col));

    if (isSameRow(&first, &last) && first.col > last.col) {
	int tmp;
	EXCHANGE(first.col, last.col, tmp);
    }

    --last.col;
    /* first we need to know how long the string is before we can save it */

    if (isSameRow(&last, &first)) {
	need = Length(screen, first.row, first.col, last.col);
    } else {			/* two cases, cut is on same line, cut spans multiple lines */
	need += Length(screen, first.row, first.col, screen->max_col) + 1;
	for (i = first.row + 1; i < last.row; i++)
	    need += Length(screen, i, 0, screen->max_col) + 1;
	if (last.col >= 0)
	    need += Length(screen, last.row, 0, last.col);
    }

    /* UTF-8 may require more space */
    if_OPT_WIDE_CHARS(screen, {
	need *= 4;
    });

    /* now get some memory to save it in */
    if (need < 0)
	return;

    if (scp->data_limit <= (unsigned) need) {
	if ((line = (Char *) malloc((size_t) need + 1)) == 0)
	    SysError(ERROR_BMALLOC2);
	free(scp->data_buffer);
	scp->data_buffer = line;
	scp->data_limit = (size_t) (need + 1);
    } else {
	line = scp->data_buffer;
    }

    if (line == 0)
	return;

    line[need] = '\0';		/* make sure it is null terminated */
    lp = line;			/* lp points to where to save the text */
    if (isSameRow(&last, &first)) {
	lp = SaveText(screen, last.row, first.col, last.col, lp, &eol);
    } else {
	lp = SaveText(screen, first.row, first.col, screen->max_col, lp, &eol);
	if (eol)
	    *lp++ = '\n';	/* put in newline at end of line */
	for (i = first.row + 1; i < last.row; i++) {
	    lp = SaveText(screen, i, 0, screen->max_col, lp, &eol);
	    if (eol)
		*lp++ = '\n';
	}
	if (last.col >= 0)
	    lp = SaveText(screen, last.row, 0, last.col, lp, &eol);
    }
    *lp = '\0';			/* make sure we have end marked */

    TRACE(("Salted TEXT:%u:%s\n", (unsigned) (lp - line),
	   visibleChars(line, (unsigned) (lp - line))));

    scp->data_length = (size_t) (lp - line);
}

/* ================= driver ================= */

#define NCOLS 100                 /* max_col+1; comfortably above every K this corpus uses */
#define COMBSIZE 5                /* screen->max_combining -- a real, valid xterm resource
                                    * value (XtNcombiningChars, capped at 5 -- charproc.c:9893) */
#define BASE_CHAR   0x65u          /* 'e', 1 UTF-8 byte */
#define COMB_CHAR   0x0301u        /* U+0301 COMBINING ACUTE ACCENT, 2 UTF-8 bytes -- a real
                                     * Unicode combining mark, not an invented value */

static LineData *build_row(int ncols, int combsize, const unsigned char *cell_drawn,
                            const IChar *base, const unsigned char *fill)
{
    LineData *ld = (LineData *) malloc(SizeOfLineData + (size_t) combsize * sizeof(CharData *));
    ld->lineSize = (Dimension) ncols;
    ld->bufHead = 0;             /* not wrapped -> LineTstWrapped() false */
    ld->combSize = (Char) combsize;
    ld->attribs = (IAttr *) calloc((size_t) ncols, sizeof(IAttr));
    ld->charData = (CharData *) calloc((size_t) ncols, sizeof(CharData));
    for (int c = 0; c < combsize; c++)
        ld->combData[c] = (CharData *) calloc((size_t) ncols, sizeof(CharData));

    for (int i = 0; i < ncols; i++) {
        if (cell_drawn[i])
            ld->attribs[i] = (IAttr) (ld->attribs[i] | CHARDRAWN);
        ld->charData[i] = base[i];
        int f = fill[i];
        if (f > combsize)
            f = combsize;
        for (int c = 0; c < f; c++)
            ld->combData[c][i] = COMB_CHAR;    /* nonzero -> counted by for_each_combData */
        /* slots [f, combsize) stay 0 (calloc) -> for_each_combData's "if (ch==0) break;" stops there */
    }
    return ld;
}

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t) ln;
    unsigned char *data = (unsigned char *) malloc(n ? n : 1);    /* HEAP input, ASAN-guarded */
    size_t got = fread(data, 1, n, fp);
    fclose(fp);
    if (got < 1) { free(data); return 0; }                        /* nothing to parse -> clean exit */

    int K = 1 + (int) (data[0] % 96);                              /* 1..96, always < NCOLS */
    size_t navail = (got >= 2) ? (got - 1) : 0;

    unsigned char *cell_drawn = (unsigned char *) calloc(NCOLS, 1);
    IChar *base = (IChar *) calloc(NCOLS, sizeof(IChar));
    unsigned char *fill = (unsigned char *) calloc(NCOLS, 1);
    for (int i = 0; i < K; i++) {
        cell_drawn[i] = 1;
        base[i] = BASE_CHAR;
        fill[i] = navail ? (unsigned char) (data[1 + (i % navail)] % 6) : 0;   /* 0..5 */
    }
    free(data);

    g_row = build_row(NCOLS, COMBSIZE, cell_drawn, base, fill);
    free(cell_drawn);
    free(base);
    free(fill);

    XtermWidgetRec w;
    memset(&w, 0, sizeof w);
    w.screen.max_col = NCOLS - 1;
    w.screen.max_row = 1000;
    w.screen.topline = 0;
    w.screen.savedlines = 0;
    w.screen.max_combining = COMBSIZE;
    w.screen.utf8_nrc_mode = 0;
    w.screen.utf8_mode = 1;             /* real precondition of this CVE: UTF-8 mode enabled */
    w.screen.wide_chars = 1;            /* real precondition of this CVE: wide-chars build/mode enabled */
    w.screen.trim_selection = 1;
    /* w.screen.selected_cells[] is zero-initialized (memset above) -> data_limit==0, so
     * SaltTextAway always takes its malloc() branch, exactly the vulnerable allocation. */

    CELL cellc, cell;
    cellc.row = 0;
    cellc.col = 0;
    cell.row = 0;
    cell.col = NCOLS;        /* SaltTextAway does "--last.col" first -> becomes max_col */

    /* volatile function pointer: forbid the compiler from inlining/proving-away the call. */
    void (*volatile fn)(XtermWidget, int, CELL *, CELL *) = SaltTextAway;
    fn(&w, 0 /* PRIMARY_CODE */, &cellc, &cell);

    return 0;
}

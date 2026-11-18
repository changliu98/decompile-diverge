void adjust_skipcol(void) {
  int cols, cols1, cols2, lines, lines1, redraw;
  long scrolloff;
  if (!curwin->w_saved_flags.saved_scroll ||
      !curwin->w_saved_flags.saved_skipcol ||
      curwin->w_cursor.lnum != curwin->w_topline)
    return;
  cols = curwin->w_ncolumns;
  cols1 = cols - curcol_off();
  cols2 = cols1 + curcol_off2();
  scrolloff = get_scrolloff_value();
  lines = scrolloff ? cols1 + (scrolloff - 1) * cols2 : 0;
  redraw = 0;
  validate_cheight();
  if (curwin->w_virtcol == curwin->w_virtcol_max &&
      plines_win(curwin, curwin->w_cursor.lnum, 0) <= curwin->w_virtcol_max) {
    reset_skipcol();
    return;
  }
  validate_virtcol();
  while (curwin->w_skipcol > 0 &&
         curwin->w_virtcol_top < lines + curwin->w_skipcol + 3) {
    if (curwin->w_skipcol >= cols2 + cols1)
      curwin->w_skipcol -= cols2;
    else
      curwin->w_skipcol -= cols1;
    redraw_later(40);
    redraw = 1;
    validate_virtcol();
  }
  if (redraw) return;
  lines1 = curwin->w_virtcol_top + lines - curwin->w_skipcol;
  lines = 0;
  if (lines1 >= cols1) {
    lines1 -= cols1;
    lines++;
  }
  if (lines1 > cols2) lines += lines1 / cols2;
  if (lines >= curwin->w_virtcol_max) {
    if (curwin->w_skipcol == 0) {
      curwin->w_skipcol += cols1;
      lines--;
    }
    if (lines >= curwin->w_virtcol_max)
      curwin->w_skipcol += cols2 * (lines - curwin->w_virtcol_max);
    redraw_later(40);
  }
}
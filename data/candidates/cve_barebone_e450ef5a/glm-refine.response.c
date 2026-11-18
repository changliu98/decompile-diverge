void __cdecl adjust_skipcol()
{
  // Early exit if smooth scrolling is disabled, or cursor is not on the topline
  if (!curwin->w_onebuf_opt.wo_wrap || !curwin->w_onebuf_opt.wo_sms || curwin->w_cursor.lnum != curwin->w_topline)
    return;

  int w_width = curwin->w_width;
  int width1 = w_width - curwin_col_off();
  int width2 = curwin_col_off2() + width1;
  
  long so = get_scrolloff_value();
  int scrolloff_offset = so ? (width2 * (so - 1) + width1) : 0;

  validate_cheight();

  // Check if the line fits entirely within the window height
  if (curwin->w_cline_height == curwin->w_height && plines_win(curwin, curwin->w_cursor.lnum, 0) <= curwin->w_height)
  {
    reset_skipcol();
    return;
  }

  validate_virtcol();
  bool scrolled = false;

  // Scroll up loop: if the cursor is too close to the top edge, scroll the window up
  while (curwin->w_skipcol > 0 && curwin->w_virtcol < scrolloff_offset + curwin->w_skipcol + 3)
  {
    if (curwin->w_skipcol < width2 + width1)
      curwin->w_skipcol -= width1;
    else
      curwin->w_skipcol -= width2;

    redraw_later(40);
    scrolled = true;
    validate_virtcol();
  }

  // Scroll down logic: only evaluate if we didn't just scroll up
  if (!scrolled)
  {
    int col = scrolloff_offset + curwin->w_virtcol - curwin->w_skipcol;
    int row = 0;

    if (col >= width1)
    {
      col -= width1;
      row = 1;
    }
    if (col > width2)
      row += col / width2;

    // If the cursor is below the visible window area, scroll down
    if (row >= curwin->w_height)
    {
      if (!curwin->w_skipcol)
      {
        curwin->w_skipcol += width1;
        --row;
      }
      if (row >= curwin->w_height)
        curwin->w_skipcol += width2 * (row - curwin->w_height);

      redraw_later(40);
    }
  }
}
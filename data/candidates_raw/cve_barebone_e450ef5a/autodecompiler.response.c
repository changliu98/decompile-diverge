void
validate_cursor_moved()
{
    int		col_off;
    int		col_off2;
    long	n;
    long	soff;
    long	scol;
    int		row;
    int		col;
    int		scrolled = 0;

    if (!curwin->w_p_wrap
	    || !curwin->w_valid
	    || curwin->w_cursor.lnum != curwin->w_valid_cursor.lnum)
	return;

    col_off = curwin->w_width - curwin_col_off();
    col_off2 = col_off + curwin_col_off2();

    /* Use the maximum scroll offset for scrolling up to the cursor line. */
    soff = get_scrolloff_value();
    if (soff == 0)
	n = 0;
    else
	n = col_off + (soff - 1) * col_off2;

    scol = n;
# ifdef FEAT_DIFF
    if (curwin->w_topline == curwin->w_topdiff
	    && diff_check(curwin, curwin->w_cursor.lnum, NULL, NULL))
    {
	/* Show the cursor on a diff line. */
	reset_skipcol();
    }
    else
# endif
    {
	validate_cheight();
	if (curwin->w_botline == curwin->w_height
		&& plines_win(curwin, curwin->w_cursor.lnum, NULL) <=
						 curwin->w_height)
	{
	    /* Don't show the cursor on a scrolled line. */
	    reset_skipcol();
	    return;
	}

	validate_virtcol();
	while (1
		&& curwin->w_leftcol > 0
		&& (curwin->w_wcol < scol + (int)curwin->w_width
		    || curwin->w_wcol >= scol + (int)curwin->w_width
						+ (int)curwin_col_off2()))
	{
	    if (curwin->w_leftcol >= (int)curwin->w_width + col_off2)
		curwin->w_leftcol -= col_off2;
	    else
		curwin->w_leftcol -= col_off;
	    redraw_later(0x0008 | 0x0020);
	    scrolled = 1;
	    validate_virtcol();
	}
	if (!scrolled)
	{
	    col = curwin->w_wcol - curwin->w_leftcol + scol;
	    row = 0;
	    if (col >= col_off)
	    {
		col -= col_off;
		row++;
	    }
	    if (col > col_off2)
	    {
		row += col / col_off2;
		col %= col_off2;
	    }
	    if (row >= (int)curwin->w_height)
	    {
		if (curwin->w_leftcol == 0)
		{
		    curwin->w_leftcol += col_off;
		    row--;
		}
		if (row >= (int)curwin->w_height)
		{
		    curwin->w_leftcol +=
			(row - (int)curwin->w_height + 1) * col_off2;
		}
		redraw_later(0x0008 | 0x0020);
	    }
	}
    }
}
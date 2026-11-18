void
adjust_skipcol()
{
    int		width;
    int		width2;
    int		scrolloff_cols;
    int		extra_cols;
    int		ncols;
    int		nrows;
    int		n;
    int		adjusted;

    /* Only do this when 'wrap' is on and 'sms' is off. */
    if (!curwin->w_onebuf_opt.wo_wrap || !curwin->w_onebuf_opt.wo_sms)
	return;

    /* Only do this when the cursor is in the first line. */
    if (curwin->w_cursor.lnum != curwin->w_topline)
	return;

    /* Use the width of the first line for the calculations. */
    width = curwin->w_width - curwin_col_off();
    width2 = width + curwin_col_off2();

    /* Use the scrolloff value for the calculations. */
    scrolloff_cols = 0;
    n = get_scrolloff_value();
    if (n != 0)
	scrolloff_cols = (n - 1) * width2 + width;

    /* If the line is not displayed with the default height, the skipcol
     * may need to be adjusted.
     * If the line is not displayed at all, reset skipcol.
     */
    validate_cheight();
    if (curwin->w_cline_height != curwin->w_height
	    || plines_win(curwin, curwin->w_cursor.lnum, NULL) > curwin->w_height)
    {
	/* Use the virtual column for the calculations. */
	validate_virtcol();

	/* If the skipcol is too big, reduce it. */
	adjusted = 0;
	while (curwin->w_skipcol > 0
		&& curwin->w_virtcol < curwin->w_skipcol + 3 + scrolloff_cols)
	{
	    if (curwin->w_skipcol >= width + width2)
		curwin->w_skipcol -= width2;
	    else
		curwin->w_skipcol -= width;
	    redraw_later(40);
	    adjusted = 1;
	    validate_virtcol();
	}

	/* If skipcol was not too big, check if it's too small. */
	if (!adjusted)
	{
	    /* Compute the number of columns the cursor is from the start of
	     * the line. */
	    ncols = curwin->w_virtcol - curwin->w_skipcol + scrolloff_cols;

	    /* Compute the number of extra columns the cursor is from the start
	     * of the line. */
	    extra_cols = 0;
	    if (ncols >= width)
	    {
		extra_cols = 1;
		ncols -= width;
	    }

	    /* Compute the number of rows the cursor is below the first row. */
	    nrows = 0;
	    if (ncols > width2)
		nrows += ncols / width2;

	    /* If the cursor is below the first row, increase skipcol. */
	    if (nrows + extra_cols >= curwin->w_height)
	    {
		/* If skipcol is zero, make it non-zero. */
		if (curwin->w_skipcol == 0)
		{
		    curwin->w_skipcol += width;
		    nrows--;
		}

		/* If the cursor is below the last row, increase skipcol. */
		if (nrows >= curwin->w_height)
		    curwin->w_skipcol += (nrows - curwin->w_height) * width2;

		redraw_later(40);
	    }
	}
    }
    else
	reset_skipcol();
}
int
adjust_plines_for_skipcol(win_T *wp)
{
    int	    width;
    int	    ncols;
    int	    nskip;

    if (wp->w_skipcol == 0)
	return 0;

    width = wp->w_width - win_col_off(wp);
    if (wp->w_skipcol >= width)
    {
	ncols = width + win_col_off2(wp);
	nskip = (wp->w_skipcol - width) / ncols + 1;
	return nskip;
    }
    return 0;
}
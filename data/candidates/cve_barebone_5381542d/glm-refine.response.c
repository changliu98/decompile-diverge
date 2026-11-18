int __cdecl adjust_plines_for_skipcol(win_T *wp)
{
  int w_width;
  int width;

  if (!wp->w_skipcol)
    return 0;

  w_width = wp->w_width;
  width = w_width - win_col_off(wp);

  if (wp->w_skipcol < width)
    return 0;

  return (wp->w_skipcol - width) / (win_col_off2(wp) + width) + 1;
}
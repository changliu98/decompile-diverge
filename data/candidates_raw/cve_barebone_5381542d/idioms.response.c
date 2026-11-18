int w_getskipline(struct win_T *wp)
{
  int w_width; int w_width2; int w_skipcol; int w_skipline;
  if (wp->w_skipcol == 0)
    return (0);
  w_width = wp->w_width;
  w_width2 = w_width - w_getborder(wp);
  if (wp->w_skipcol < w_width)
    return (0);
  w_skipcol = wp->w_skipcol - w_width;
  w_skipline = w_skipcol / (w_width2 + w_getwspace(wp));
  return (w_skipline + 1);
}
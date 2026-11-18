int __cdecl adjust_plines_for_skipcol(win_T *wp)
{
  int v2; // [rsp+4h] [rbp-1Ch]
  int w_width; // [rsp+8h] [rbp-18h]
  int width; // [rsp+Ch] [rbp-14h]

  if ( !wp->w_skipcol )
    return 0;
  w_width = wp->w_width;
  width = w_width - win_col_off(wp);
  if ( wp->w_skipcol < width )
    return 0;
  v2 = wp->w_skipcol - width;
  return v2 / (win_col_off2(wp) + width) + 1;
}
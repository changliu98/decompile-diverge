int adjust_plines_for_skipcol(Window *wp) {
  int cols, cols_to_skip;
  if (wp->w_plines == 0) return 0;
  cols = wp->w_cols;
  cols_to_skip = cols - win_col_off(wp);
  if (wp->w_plines < cols_to_skip) return 0;
  return 1 + (wp->w_plines - cols_to_skip) / (cols_to_skip + win_col_off2(wp));
}
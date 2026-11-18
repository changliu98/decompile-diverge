int adjust_plines_for_skipcol(win_T *wp)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int width;
  win_T *wp_local;
  int local_c;
  
  if (wp->w_skipcol == 0) {
    local_c = 0;
  }
  else {
    iVar2 = wp->w_width;
    iVar1 = win_col_off(wp);
    iVar2 = iVar2 - iVar1;
    if (wp->w_skipcol < iVar2) {
      local_c = 0;
    }
    else {
      iVar1 = wp->w_skipcol;
      iVar3 = win_col_off2(wp);
      local_c = (iVar1 - iVar2) / (iVar2 + iVar3) + 1;
    }
  }
  return local_c;
}
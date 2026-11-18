/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void adjust_skipcol(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  int local_38;
  int row;
  int col;
  int scrolled;
  int scrolloff_cols;
  long so;
  int width2;
  int width1;
  
  if ((((curwin->w_onebuf_opt).wo_wrap != 0) && ((curwin->w_onebuf_opt).wo_sms != 0)) &&
     ((curwin->w_cursor).lnum == curwin->w_topline)) {
    iVar4 = curwin->w_width;
    iVar3 = curwin_col_off();
    iVar4 = iVar4 - iVar3;
    iVar3 = curwin_col_off2();
    iVar3 = iVar4 + iVar3;
    lVar6 = get_scrolloff_value();
    if (lVar6 == 0) {
      local_38 = 0;
    }
    else {
      local_38 = iVar4 + ((int)lVar6 + -1) * iVar3;
    }
    bVar2 = false;
    validate_cheight();
    if ((curwin->w_cline_height == curwin->w_height) &&
       (iVar5 = plines_win(curwin,(curwin->w_cursor).lnum,0), iVar5 <= curwin->w_height)) {
      reset_skipcol();
    }
    else {
      validate_virtcol();
      while( true ) {
        bVar1 = false;
        if (0 < curwin->w_skipcol) {
          bVar1 = curwin->w_virtcol < curwin->w_skipcol + 3 + local_38;
        }
        if (!bVar1) break;
        if (curwin->w_skipcol < iVar4 + iVar3) {
          curwin->w_skipcol = curwin->w_skipcol - iVar4;
        }
        else {
          curwin->w_skipcol = curwin->w_skipcol - iVar3;
        }
        redraw_later(0x28);
        bVar2 = true;
        validate_virtcol();
      }
      if (!bVar2) {
        col = (curwin->w_virtcol - curwin->w_skipcol) + local_38;
        bVar2 = iVar4 <= col;
        if (bVar2) {
          col = col - iVar4;
        }
        row = (int)bVar2;
        if (iVar3 < col) {
          row = col / iVar3 + row;
        }
        if (curwin->w_height <= row) {
          if (curwin->w_skipcol == 0) {
            curwin->w_skipcol = iVar4 + curwin->w_skipcol;
            row = row + -1;
          }
          if (curwin->w_height <= row) {
            curwin->w_skipcol = (row - curwin->w_height) * iVar3 + curwin->w_skipcol;
          }
          redraw_later(0x28);
        }
      }
    }
  }
  return;
}
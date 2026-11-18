void __cdecl adjust_skipcol()
{
  bool v0; // [rsp+Fh] [rbp-31h]
  int v1; // [rsp+10h] [rbp-30h]
  int w_width; // [rsp+18h] [rbp-28h]
  int row; // [rsp+20h] [rbp-20h]
  int col; // [rsp+24h] [rbp-1Ch]
  int scrolled; // [rsp+28h] [rbp-18h]
  long so; // [rsp+30h] [rbp-10h]
  int width2; // [rsp+38h] [rbp-8h]
  int width1; // [rsp+3Ch] [rbp-4h]

  if ( curwin->w_onebuf_opt.wo_wrap && curwin->w_onebuf_opt.wo_sms && curwin->w_cursor.lnum == curwin->w_topline )
  {
    w_width = curwin->w_width;
    width1 = w_width - curwin_col_off();
    width2 = curwin_col_off2() + width1;
    so = get_scrolloff_value();
    if ( so )
      v1 = width2 * (so - 1) + width1;
    else
      v1 = 0;
    scrolled = 0;
    validate_cheight();
    if ( curwin->w_cline_height == curwin->w_height && plines_win(curwin, curwin->w_cursor.lnum, 0) <= curwin->w_height )
    {
      reset_skipcol();
    }
    else
    {
      validate_virtcol();
      while ( 1 )
      {
        v0 = 0;
        if ( curwin->w_skipcol > 0 )
          v0 = curwin->w_virtcol < v1 + curwin->w_skipcol + 3;
        if ( !v0 )
          break;
        if ( curwin->w_skipcol < width2 + width1 )
          curwin->w_skipcol -= width1;
        else
          curwin->w_skipcol -= width2;
        redraw_later(40);
        scrolled = 1;
        validate_virtcol();
      }
      if ( !scrolled )
      {
        col = v1 + curwin->w_virtcol - curwin->w_skipcol;
        row = 0;
        if ( col >= width1 )
        {
          col -= width1;
          row = 1;
        }
        if ( col > width2 )
          row += col / width2;
        if ( row >= curwin->w_height )
        {
          if ( !curwin->w_skipcol )
          {
            curwin->w_skipcol += width1;
            --row;
          }
          if ( row >= curwin->w_height )
            curwin->w_skipcol += width2 * (row - curwin->w_height);
          redraw_later(40);
        }
      }
    }
  }
}
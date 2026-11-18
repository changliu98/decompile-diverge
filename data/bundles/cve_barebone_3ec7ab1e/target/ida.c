void __cdecl SaltTextAway(XtermWidget xw, int which, CELL *cellc, CELL *cell)
{
  Char *v4; // rax
  Char *v5; // rax
  int tmp; // [rsp+Ch] [rbp-64h]
  CELL last; // [rsp+10h] [rbp-60h]
  CELL first; // [rsp+18h] [rbp-58h]
  Char *lp; // [rsp+20h] [rbp-50h]
  Char *line; // [rsp+28h] [rbp-48h]
  int need; // [rsp+34h] [rbp-3Ch]
  int eol; // [rsp+38h] [rbp-38h] BYREF
  int i; // [rsp+3Ch] [rbp-34h]
  SelectedCells *scp; // [rsp+40h] [rbp-30h]
  TScreen *screen; // [rsp+48h] [rbp-28h]
  CELL *cella; // [rsp+50h] [rbp-20h]
  CELL *cellca; // [rsp+58h] [rbp-18h]
  int whicha; // [rsp+64h] [rbp-Ch]
  XtermWidget xwa; // [rsp+68h] [rbp-8h]

  xwa = xw;
  whicha = which;
  cellca = cellc;
  cella = cell;
  screen = &xw->screen;
  first = *cellc;
  last = *cell;
  if ( which >= 0 && whicha < 11 )
  {
    scp = &screen->selected_cells[whicha];
    if ( first.row == last.row && first.col > last.col )
    {
      tmp = first.col;
      first.col = last.col;
      last.col = tmp;
    }
    --last.col;
    if ( last.row == first.row )
    {
      need = Length(screen, first.row, first.col, last.col);
    }
    else
    {
      need = Length(screen, first.row, first.col, screen->max_col) + 1;
      for ( i = first.row + 1; i < last.row; ++i )
        need += Length(screen, i, 0, screen->max_col) + 1;
      if ( last.col >= 0 )
        need += Length(screen, last.row, 0, last.col);
    }
    if ( screen->wide_chars )
      need *= 4;
    if ( need >= 0 )
    {
      if ( scp->data_limit > (unsigned int)need )
      {
        line = scp->data_buffer;
      }
      else
      {
        line = (Char *)malloc(need + 1LL);
        if ( !line )
          SysError(71);
        free(scp->data_buffer);
        scp->data_buffer = line;
        scp->data_limit = need + 1;
      }
      if ( line )
      {
        line[need] = 0;
        if ( last.row == first.row )
        {
          lp = SaveText(screen, last.row, first.col, last.col, line, &eol);
        }
        else
        {
          lp = SaveText(screen, first.row, first.col, screen->max_col, line, &eol);
          if ( eol )
          {
            v4 = lp++;
            *v4 = 10;
          }
          for ( i = first.row + 1; i < last.row; ++i )
          {
            lp = SaveText(screen, i, 0, screen->max_col, lp, &eol);
            if ( eol )
            {
              v5 = lp++;
              *v5 = 10;
            }
          }
          if ( last.col >= 0 )
            lp = SaveText(screen, last.row, 0, last.col, lp, &eol);
        }
        *lp = 0;
        scp->data_length = lp - line;
      }
    }
  }
}
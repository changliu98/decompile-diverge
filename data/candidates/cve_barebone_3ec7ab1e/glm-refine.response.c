void __cdecl SaltTextAway(XtermWidget xw, int which, CELL *cellc, CELL *cell)
{
  int tmp;
  CELL last;
  CELL first;
  Char *lp;
  Char *line;
  int need;
  int eol;
  int i;
  SelectedCells *scp;
  TScreen *screen;

  screen = &xw->screen;
  first = *cellc;
  last = *cell;
  
  if ( which >= 0 && which < 11 )
  {
    scp = &screen->selected_cells[which];
    
    // Swap columns if they are out of order on the same row
    if ( first.row == last.row && first.col > last.col )
    {
      tmp = first.col;
      first.col = last.col;
      last.col = tmp;
    }
    
    --last.col;
    
    // Calculate required buffer size
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
    
    // Account for wide characters
    if ( screen->wide_chars )
      need *= 4;
      
    if ( need >= 0 )
    {
      // Allocate or reuse buffer
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
        
        // Save text into the buffer
        if ( last.row == first.row )
        {
          lp = SaveText(screen, last.row, first.col, last.col, line, &eol);
        }
        else
        {
          lp = SaveText(screen, first.row, first.col, screen->max_col, line, &eol);
          if ( eol )
            *lp++ = '\n'; // 10 == newline
          
          for ( i = first.row + 1; i < last.row; ++i )
          {
            lp = SaveText(screen, i, 0, screen->max_col, lp, &eol);
            if ( eol )
              *lp++ = '\n';
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
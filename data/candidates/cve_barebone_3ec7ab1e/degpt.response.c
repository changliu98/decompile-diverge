void SaltTextAway(XtermWidget xw,int which,CELL *cellc,CELL *cell)

{
  int iVar1;
  int iVar2;
  Char *pCVar3;
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
  CELL *cell_local;
  CELL *cellc_local;
  int which_local;
  XtermWidget xw_local;
  
  first = *cellc;
  last = *cell;
  if ((-1 < which) && (which < 0xb)) {
    scp = (xw->screen).selected_cells + which;
    if (first.row == last.row) {
      iVar1 = first.col;
      if (last.col < first.col) {
        first.col = last.col;
        last.col = iVar1;
      }
    }
    iVar1 = last.col + -1;
    screen = &xw->screen;
    cell_local = cell;
    cellc_local = cellc;
    which_local = which;
    xw_local = xw;
    if (last.row == first.row) {
      need = Length(&xw->screen,first.row,first.col,iVar1);
    }
    else {
      iVar2 = Length(&xw->screen,first.row,first.col,(xw->screen).max_col);
      need = iVar2 + 1;
      i = first.row;
      while (i = i + 1, i < last.row) {
        iVar2 = Length(screen,i,0,screen->max_col);
        need = iVar2 + 1 + need;
      }
      if (-1 < iVar1) {
        iVar2 = Length(screen,last.row,0,iVar1);
        need = iVar2 + need;
      }
    }
    if (screen->wide_chars != '\0') {
      need = need << 2;
    }
    if (-1 < need) {
      if ((ulong)(uint)need < scp->data_limit) {
        line = scp->data_buffer;
      }
      else {
        line = malloc((long)need + 1);
        if (line == (Char *)0x0) {
          SysError(0x47);
        }
        free(scp->data_buffer);
        scp->data_buffer = line;
        scp->data_limit = (long)(need + 1);
      }
      if (line != (Char *)0x0) {
        line[need] = '\0';
        if (last.row == first.row) {
          lp = SaveText(screen,last.row,first.col,iVar1,line,&eol);
        }
        else {
          lp = SaveText(screen,first.row,first.col,screen->max_col,line,&eol);
          if (eol != 0) {
            *lp = '\n';
            lp = lp + 1;
          }
          while (i = first.row + 1, i < last.row) {
            pCVar3 = SaveText(screen,i,0,screen->max_col,lp,&eol);
            lp = pCVar3;
            first.row = i;
            if (eol != 0) {
              lp = pCVar3 + 1;
              *pCVar3 = '\n';
            }
          }
          if (-1 < iVar1) {
            lp = SaveText(screen,last.row,0,iVar1,lp,&eol);
          }
        }
        *lp = '\0';
        scp->data_length = (long)lp - (long)line;
      }
    }
  }
  return;
}
void SaltTextAway(XtermWidget xw, int which, CELL *cellc, CELL *cell)
{
    CELL first = *cellc;
    CELL last = *cell;
    int need;
    int eol;
    Char *line;
    Char *lp;
    int i;
    SelectedCells *scp;
    TScreen *screen;

    if (which < 0 || which >= 11) return;
    scp = &xw->screen.selected_cells[which];

    if (first.row == last.row && first.col > last.col) {
 i = first.col;
 first.col = last.col;
 last.col = i;
    }
    last.col--;
    screen = &xw->screen;
    if (first.row == last.row)
      need = Length(screen, first.row, first.col, last.col);
    else {
 need = Length(screen, first.row, first.col, screen->max_col) + 1;
 for (i = first.row + 1; i < last.row; i++)
   need += Length(screen, i, 0, screen->max_col) + 1;
 if (last.col >= 0)
   need += Length(screen, last.row, 0, last.col);
    }
    if (screen->wide_chars) need *= 4;
    if (need < 0) return;
    if (need >= scp->data_limit) {
 line = (Char *) malloc((size_t) (need + 1));
 if (!line) SysError(71);
 free(scp->data_buffer);
 scp->data_buffer = line;
 scp->data_limit = (size_t) (need + 1);
    } else
      line = scp->data_buffer;
    if (!line) return;
    line[need] = '\0';
    lp = line;
    if (first.row == last.row)
      lp = SaveText(screen, last.row, first.col, last.col, lp, &eol);
    else {
 lp = SaveText(screen, first.row, first.col, screen->max_col, lp, &eol);
 if (eol) *lp++ = '\n';
 for (i = first.row + 1; i < last.row; i++) {
     lp = SaveText(screen, i, 0, screen->max_col, lp, &eol);
     if (eol) *lp++ = '\n';
 }
 if (last.col >= 0)
   lp = SaveText(screen, last.row, 0, last.col, lp, &eol);
    }
    *lp = '\0';
    scp->data_length = (size_t) (lp - line);
}
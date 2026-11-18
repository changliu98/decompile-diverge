static void SaveSelection(SCREEN *Screen, int w, CELL *StartCell, CELL *EndCell)
{
  int i, len = 0;
  SCREEN_WIN *Win;
  char *p, *q, *r;
  CELL c1, c2;
  int eol;

  Win = &Screen->Win[w];

  c1 = *StartCell;
  c2 = *EndCell;

  switch (w) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
    break;
  default:
    return;
  }

  if ((c1.row == c2.row) && (c1.col > c2.col)) {
    i = c1.col;
    c1.col = c2.col;
    c2.col = i;
  }

  c2.col--;

  if (c2.row == c1.row) {
    len = Length(Screen, c1.row, c1.col, c2.col);
  } else {
    len += Length(Screen, c1.row, c1.col, Screen->Cols) + 1;
    for (i = c1.row + 1; ; i++) {
      if (i >= c2.row) break;
      len += Length(Screen, i, 0, Screen->Cols) + 1;
    }
    if (c2.col >= 0) {
      len += Length(Screen, c2.row, 0, c2.col);
    }
  }

  if (Screen->Flags & 0x00000020) len *= 4;

  if (len < 0) return;

  if (len >= Win->SelAlloc) {
    p = (char *) malloc(len + 1);
    if (!p) SysError(71);
    free(Win->SelText);
    Win->SelText = p;
    Win->SelAlloc = len + 1;
  } else {
    p = Win->SelText;
  }

  if (!p) return;

  p[len] = '\0';

  q = p;

  if (c2.row == c1.row) {
    q = SaveText(Screen, c2.row, c1.col, c2.col, q, &eol);
  } else {
    q = SaveText(Screen, c1.row, c1.col, Screen->Cols, q, &eol);
    if (eol) *q++ = '\n';
    for (i = c1.row + 1; ; i++) {
      if (i >= c2.row) break;
      q = SaveText(Screen, i, 0, Screen->Cols, q, &eol);
      if (eol) *q++ = '\n';
    }
    if (c2.col >= 0) {
      q = SaveText(Screen, c2.row, 0, c2.col, q, &eol);
    }
  }

  *q = '\0';
  Win->SelSize = q - p;
}
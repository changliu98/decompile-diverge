static void SaltTextAway(SciPlatistique sci, int n, SciPoint *p1,
                         SciPoint *p2) {
  SciPtr s = &sci->s;
  SciPoint pt1 = *p1;
  SciPoint pt2 = *p2;
  Char *newtext;
  Char *p;
  int len;
  int tmp;
  int i;
  Salt *salt;
  if (n < 0 || n >= 11) return;
  salt = &s->salt[n];
  if (pt1.y == pt2.y && pt1.x > pt2.x) {
    tmp = pt1.x;
    pt1.x = pt2.x;
    pt2.x = tmp;
  }
  pt2.x--;
  if (pt2.y == pt1.y) {
    len = Length(s, pt1.y, pt1.x, pt2.x);
  } else {
    len = Length(s, pt1.y, pt1.x, s->xsize) + 1;
    for (i = pt1.y + 1; i < pt2.y; i++) len += Length(s, i, 0, s->xsize) + 1;
    if (pt2.x >= 0) len += Length(s, pt2.y, 0, pt2.x);
  }
  if (s->bigfont) len *= 4;
  if (len < 0) return;
  if ((unsigned)len >= salt->textsize) {
    newtext = (Char *)malloc((unsigned)len + 1);
    if (newtext == NULL) SysError(71);
    free(salt->text);
    salt->text = newtext;
    salt->textsize = len + 1;
  } else
    newtext = salt->text;
  if (newtext != NULL) {
    newtext[len] = '\0';
    if (pt2.y == pt1.y) {
      p = SaveText(s, pt2.y, pt1.x, pt2.x, newtext, &i);
    } else {
      p = SaveText(s, pt1.y, pt1.x, s->xsize, newtext, &i);
      if (i) *p++ = '\n';
      for (i = pt1.y + 1; i < pt2.y; i++) {
        p = SaveText(s, i, 0, s->xsize, p, &i);
        if (i) *p++ = '\n';
      }
      if (pt2.x >= 0) p = SaveText(s, pt2.y, 0, pt2.x, p, &i);
    }
    *p = '\0';
    salt->textlen = p - newtext;
  }
}
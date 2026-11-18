void reverse(char *s) {
  char *p, *q, c;
  p = s;
  for (q = s; *q; q++)
    ;
  q--;
  while (p < q) {
    c = *p;
    *p = *q;
    *q = c;
    p++;
    q--;
  }
}
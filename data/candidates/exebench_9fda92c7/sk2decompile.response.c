void reverse(char *s) {
  char *p = s;
  char *q = s;
  char *r;
  char c;
  while (*p++)
    ;
  p--;
  r = p - 1;
  while (q < r) {
    c = *q;
    *q = *r;
    *r = c;
    q++;
    r--;
  }
}
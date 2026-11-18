void string_reverse(char *str)
{
  char *p = str;
  char *q = str;
  while (1) {
    _Bool is_end = (q == ((void *)0)) ? 0 : (q[0] == '\0') ? 0 : 1;
    if (!is_end)
      break;
    q++;
  }
  q--;
  while (p < q) {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
    p++;
    q--;
  }
}
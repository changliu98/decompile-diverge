int sdsull2str(char *s, unsigned long long v) {
  char *p1, *p2, aux;
  int l;
  p1 = p2 = s;
  do {
    *p2++ = '0' + v % 10;
    v /= 10;
  } while (v);
  l = p2 - p1;
  *p2 = '\0';
  p2--;
  while (p1 < p2) {
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
    p1++;
    p2--;
  }
  return l;
}
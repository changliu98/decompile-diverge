void reverse( char s[ ] ) {
  char *p, *q;
  p = q = s;
  while ( *q != '\0' ) {
    q++;
  }
  q--;
  while ( p < q ) {
    *p ^= *q ^= *p ^= *q;
    p++, q--;
  }
}
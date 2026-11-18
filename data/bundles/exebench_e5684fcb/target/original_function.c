int reverse( char s[ ] ) {
  char *p, *q;
  q = p = s;
  while ( *q++ )
    ;
  q--;
  q--;
  while ( p < q ) {
    { *p ^= *q ^= *p ^= *q; };
    p++, q--;
  }
  return 0;
}
char * string_to_slong(char *s,long *number)

{
  bool bVar1;
  int c;
  int sign;
  long *number_local;
  char *s_local;
  
  c = (int)*s;
  if (c == 0x2d) {
    bVar1 = true;
    s_local = s + 1;
    c = (int)s[1];
  }
  else {
    s_local = s;
    if (c == 0x2b) {
      s_local = s + 1;
      c = (int)s[1];
    }
    bVar1 = false;
  }
  *number = 0;
  while (c - 0x30U < 10) {
    *number = *number * 2 + *number * 8 + (long)(c + -0x30);
    c = (int)s_local[1];
    s_local = s_local + 1;
  }
  if (bVar1) {
    *number = -*number;
  }
  return s_local;
}
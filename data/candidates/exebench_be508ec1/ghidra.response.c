void string_reverse(char *p)

{
  bool bVar1;
  char *q;
  char *p_local;
  
  q = p;
  while( true ) {
    bVar1 = false;
    if (q != (char *)0x0) {
      bVar1 = *q != '\0';
    }
    p_local = p;
    if (!bVar1) break;
    q = q + 1;
  }
  for (; q = q + -1, p_local < q; p_local = p_local + 1) {
    *p_local = *p_local ^ *q;
    *q = *q ^ *p_local;
    *p_local = *p_local ^ *q;
  }
  return;
}
void reverse(char *s)

{
  byte bVar1;
  byte bVar2;
  char *q;
  char *p;
  char *s_local;
  
  for (q = s; p = s, *q != '\0'; q = q + 1) {
  }
  for (; q = q + -1, p < q; p = p + 1) {
    bVar2 = *q;
    bVar1 = *p;
    *p = bVar1 ^ bVar2;
    bVar2 = *q ^ bVar1 ^ bVar2;
    *q = bVar2;
    *p = *p ^ bVar2;
  }
  return;
}
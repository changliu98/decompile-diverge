int reverse(char *s)

{
  byte bVar1;
  char *pcVar2;
  byte bVar3;
  char *q;
  char *p;
  char *s_local;
  
  pcVar2 = s;
  do {
    q = pcVar2;
    pcVar2 = q + 1;
    p = s;
  } while (*q != '\0');
  for (; q = q + -1, p < q; p = p + 1) {
    bVar3 = *q;
    bVar1 = *p;
    *p = bVar1 ^ bVar3;
    bVar3 = *q ^ bVar1 ^ bVar3;
    *q = bVar3;
    *p = *p ^ bVar3;
  }
  return 0;
}
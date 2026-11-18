int sdsll2str(char *s,longlong value)

{
  char cVar1;
  undefined1 auVar2 [16];
  int iVar3;
  char *pcVar4;
  size_t l;
  unsigned_long_long v;
  char aux;
  char *p;
  longlong value_local;
  char *s_local;
  
  v = value;
  pcVar4 = s;
  if (value < 0) {
    if (value == -0x8000000000000000) {
      v = 0x8000000000000000;
      pcVar4 = s;
    }
    else {
      v = -value;
      pcVar4 = s;
    }
  }
  do {
    p = pcVar4;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = v;
    pcVar4 = p + 1;
    *p = SUB161(auVar2 % ZEXT816(10),0) + '0';
    v = v / 10;
  } while (v != 0);
  if (value < 0) {
    *pcVar4 = '-';
    pcVar4 = p + 2;
  }
  p = pcVar4;
  iVar3 = (int)p;
  *p = '\0';
  for (s_local = s; p = p + -1, s_local < p; s_local = s_local + 1) {
    cVar1 = *s_local;
    *s_local = *p;
    *p = cVar1;
  }
  return iVar3 - (int)s;
}
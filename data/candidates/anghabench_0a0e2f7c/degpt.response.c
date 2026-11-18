int sdsull2str(char *s,unsigned_long_long v)

{
  char cVar1;
  undefined1 auVar2 [16];
  char *pcVar3;
  size_t l;
  char aux;
  char *p;
  unsigned_long_long v_local;
  char *s_local;
  
  pcVar3 = s;
  v_local = v;
  do {
    p = pcVar3;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = v_local;
    pcVar3 = p + 1;
    *p = SUB161(auVar2 % ZEXT816(10),0) + '0';
    v_local = v_local / 10;
  } while (v_local != 0);
  *pcVar3 = '\0';
  for (s_local = s; s_local < p; s_local = s_local + 1) {
    cVar1 = *s_local;
    *s_local = *p;
    *p = cVar1;
    p = p + -1;
  }
  return (int)pcVar3 - (int)s;
}
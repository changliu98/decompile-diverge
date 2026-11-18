int ltos(char *s,long num)

{
  undefined1 auVar1 [16];
  unsigned_long local_50;
  unsigned_long anum;
  char *p;
  char buf [20];
  long num_local;
  char *s_local;
  
  local_50 = num;
  if (num < 0) {
    local_50 = -num;
  }
  p = buf;
  for (anum = local_50; 9 < anum; anum = anum / 10) {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = anum;
    *p = SUB161(auVar1 % ZEXT816(10),0) + '0';
    p = p + 1;
  }
  s_local = s;
  if (num < 0) {
    s_local = s + 1;
    *s = '-';
  }
  *s_local = (char)anum + '0';
  while( true ) {
    s_local = s_local + 1;
    if (p <= buf) break;
    *s_local = p[-1];
    p = p + -1;
  }
  *s_local = '\0';
  return 0;
}
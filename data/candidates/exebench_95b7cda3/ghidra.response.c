void itoa(char *buf,int base,long d)

{
  char *pcVar1;
  char cVar2;
  char tmp;
  int remainder;
  int divisor;
  unsigned_long ud;
  char *p2;
  char *p1;
  char *p;
  long d_local;
  int base_local;
  char *buf_local;
  
  divisor = 10;
  if ((base == 100) && (d < 0)) {
    *buf = '-';
    buf_local = buf + 1;
    ud = -d;
    pcVar1 = buf_local;
  }
  else {
    ud = d;
    pcVar1 = buf;
    buf_local = buf;
    if (base == 0x78) {
      divisor = 0x10;
      pcVar1 = buf;
    }
  }
  do {
    p = pcVar1;
    cVar2 = 'W';
    if ((uint)(ud % (ulong)(long)divisor) < 10) {
      cVar2 = '0';
    }
    *p = cVar2 + (char)(ud % (ulong)(long)divisor);
    ud = ud / (ulong)(long)divisor;
    pcVar1 = p + 1;
  } while (ud != 0);
  p[1] = '\0';
  p2 = p;
  for (p1 = buf_local; p1 < p2; p1 = p1 + 1) {
    cVar2 = *p1;
    *p1 = *p2;
    *p2 = cVar2;
    p2 = p2 + -1;
  }
  return;
}
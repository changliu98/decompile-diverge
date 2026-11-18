char * int2str(int val,char *str,int base)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  uint uval;
  char *p2;
  char *p;
  char buf [33];
  int base_local;
  char *str_local;
  int val_local;
  
  memset(buf,0,0x21);
  if ((base < 2) || (0x24 < base)) {
    *str = '\0';
  }
  else {
    uval = val;
    pcVar2 = buf;
    if ((val < 0) && (base == 10)) {
      uval = -val;
    }
    do {
      p = pcVar2;
      pcVar2 = p + 1;
      *p = int2str::tab[(ulong)uval % (ulong)(uint)base];
      uval = uval / (uint)base;
    } while (uval != 0);
    p2 = str;
    if ((val < 0) && (base == 10)) {
      *pcVar2 = '-';
      pcVar2 = p + 2;
    }
    do {
      p = pcVar2 + -1;
      bVar3 = false;
      if (buf <= p) {
        cVar1 = *p;
        *p2 = cVar1;
        bVar3 = cVar1 != '\0';
        p2 = p2 + 1;
      }
      pcVar2 = p;
    } while (bVar3);
    *p2 = '\0';
  }
  return str;
}
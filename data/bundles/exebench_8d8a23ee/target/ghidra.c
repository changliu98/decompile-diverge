int utoa(char *str,uint u,int spec)

{
  char *hex;
  char hexupper [17];
  char hexlower [17];
  int base;
  char *s;
  char *p;
  char *end;
  char tmp [128];
  char local_28 [8];
  int spec_local;
  uint u_local;
  char *str_local;
  
  p = tmp + 0x7f;
  u_local = u;
  switch(spec) {
  case 0x58:
    base = 0x10;
    hex = hexupper;
    break;
  default:
    return -1;
  case 100:
  case 0x69:
  case 0x75:
    base = 10;
    break;
  case 0x6f:
    base = 8;
    break;
  case 0x78:
    base = 0x10;
    hex = hexlower;
  }
  do {
    if (base == 8) {
      *p = ((byte)u_local & 7) + 0x30;
      p = p + -1;
    }
    else if (base == 10) {
      *p = (char)((ulong)u_local % 10) + '0';
      p = p + -1;
    }
    else if (base == 0x10) {
      *p = hex[u_local & 0xf];
      p = p + -1;
    }
    u_local = u_local / (uint)base;
    s = str;
  } while (u_local != 0);
  while (p = p + 1, p < local_28) {
    *s = *p;
    s = s + 1;
  }
  *s = '\0';
  return (int)s - (int)str;
}
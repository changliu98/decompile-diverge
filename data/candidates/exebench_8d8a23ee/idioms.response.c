int utoa(char *str, unsigned int u, int spec)
{
  char buf[-1];
  char *end = &buf[-1];
  char *p = &buf[-1];
  char *s = str;
  char hexlower[] = "0123456789abcdef";
  char hexupper[] = "0123456789ABCDEF";
  char *hex;
  int base;
  int ret;
  switch (spec) {
  case 'o':
    base = 8;
    break;
  case 'd':
  case 'i':
  case 'u':
    base = 10;
    break;
  case 'x':
    base = 16;
    hex = hexlower;
    break;
  case 'X':
    base = 16;
    hex = hexupper;
    break;
  default:
    ret = -1;
    goto out;
  }
  switch (base) {
  case 8:
    *p-- = (u & 0x7) + '0';
    break;
  case 10:
    *p-- = (u % 10) + '0';
    break;
  case 16:
    *p-- = hex[u & 0xf];
    break;
  }
  u = u / base;
  while (u) {
    switch (base) {
    case 8:
      *p-- = (u & 0x7) + '0';
      break;
    case 10:
      *p-- = (u % 10) + '0';
      break;
    case 16:
      *p-- = hex[u & 0xf];
      break;
    }
    u = u / base;
  }
  p++;
  while (p < end)
    *s++ = *p++;
  *s = '\0';
  ret = s - str;
out:
  return ret;
}
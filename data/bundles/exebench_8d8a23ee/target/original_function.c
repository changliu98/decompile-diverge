int utoa(char *str, unsigned int u, int spec)
{
 char tmp[128];
 char *end = tmp + sizeof(tmp);
 char *p = end - 1;
 char *s = str;
 int base;

 char hexlower[] = "0123456789abcdef";
 char hexupper[] = "0123456789ABCDEF";
 char *hex;

 switch (spec) {
 case 'd':
 case 'i':
 case 'u':
  base = 10;
  break;
 case 'o':
  base = 8;
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
  return -1;
 }

 do {
  switch (base) {
  case 8:
   *p-- = '0' + (u & (base - 1));
   break;
  case 10:
   *p-- = '0' + (u % 10);
   break;
  case 16:
   *p-- = hex[u & (base - 1)];
   break;
  }

  u /= base;
 } while (u != 0);

 for (++p; p < end; p++)
  *s++ = *p;

 *s = 0;

 return (int)(s - str);
}
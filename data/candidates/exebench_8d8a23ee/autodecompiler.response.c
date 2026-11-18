int utoa(char *buf, unsigned int i, int fmt)
{
 char c, b[16];
 char *p = b + sizeof(b) - 1;
 char *s = buf;
 int n;
 int w;
 int base;
 char *hex_lower = "0123456789abcdef";
 char *hex_upper = "0123456789ABCDEF";
 char *hex;

 switch(fmt) {
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
  hex = hex_lower;
  break;
 case 'X':
  base = 16;
  hex = hex_upper;
  break;
 default:
  return -1;
 }

 do {
  w = base;
  switch(w) {
  case 8:
   p--;
   *p = (char)((i & (w-1)) + '0');
   break;
  case 10:
   p--;
   *p = (char)((i % w) + '0');
   break;
  case 16:
   p--;
   *p = hex[i & (w-1)];
   break;
  }
  i = i / w;
 } while(i != 0);
 p++;
 while(p < b + sizeof(b)) {
  *s++ = *p++;
 }
 *s = '\0';
 n = s - buf;
 return n;
}
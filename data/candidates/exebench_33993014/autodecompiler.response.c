int LI_ltostr(char *buf, long l)
{
 char *p, c;
 int n = 1;

 if (l < 0) {
  *buf++ = '-';
  ++n;
  l = -l;
 }

 p = buf;
 while (1) {
  if (l >= 10) {
   *p++ = '0' + (l % 10);
   l /= 10;
  } else {
   *p = '0' + l;
   *++p = '\0';
   n += p - buf;
   break;
  }
 }


 while (buf < p) {
  c = *p;
  *p = *buf;
  *buf = c;
  ++buf;
  --p;
 }

 return n;
}
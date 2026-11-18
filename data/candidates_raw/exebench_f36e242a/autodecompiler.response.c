int ltoa(char *buf, long n)
{
 char *p;
 unsigned long nn;
 char tmp[32];

 p = tmp;

 if (n < 0) {
  nn = -n;
 } else {
  nn = n;
 }

 while (nn > 9) {
  *p++ = '0' + (nn % 10);
  nn /= 10;
 }

 if (n < 0) {
  *buf++ = '-';
 }
 *buf++ = '0' + (char)nn;
 while (p-- > tmp) {
  *buf++ = *p;
 }
 *buf = '\0';
 return 0;
}
static int getint(char *s, int *pn)
{
 long int acc;
 int c, sign, n;
 int ret;

 sign = 0;
 n = 0;
 *pn = 0;

 if (*s == '-') {
  sign = 1;
  s++;
  n++;
 }

 for (acc = 0; ; n++) {
  if (*s == '\0')
   break;

  c = *s - '0';
  if (c < 0 || c > 9)
   break;

  acc *= 10;
  acc += c;
  if (acc > 2147483647)
   break;

  s++;
  *pn = acc;
 }

 if (sign) {
  if (n == 1)
   ret = 0;
  else
   *pn = 0 - *pn;
 } else
  ret = n;

 return ret;
}
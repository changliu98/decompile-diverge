char *itoa(long n, char *str, long radix)
{
 char digit[37];
 char *p1, *p2;
 char c;

 memcpy(digit, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 37);

 if (str == NULL || radix < 2 || radix > 36)
  return str;

 if (radix != 10 && n < 0)
  return str;

 if (n == 0) {
  *str = '0';
  *(str + 1) = '\0';
  return str;
 }

 p1 = str;
 if (radix == 10 && n < 0) {
  *p1 = '-';
  p1++;
  n = -n;
 }

 while (n != 0) {
  *p1 = digit[n % radix];
  p1++;
  n /= radix;
 }

 *p1 = '\0';
 p2 = str;

 while (p1 > p2) {
  c = *p2;
  *p2 = *--p1;
  *p1 = c;
  p2++;
 }

 return str;
}
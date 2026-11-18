void itoa(unsigned long n, char *s)
{
 char *p = s;
 unsigned long m = n;
 do {
  p++;
  m /= 10;
 } while (m);
 *p = '\0';
 do {
  *(--p) = '0' + (char)(n % 10);
  n /= 10;
 } while (n);
}
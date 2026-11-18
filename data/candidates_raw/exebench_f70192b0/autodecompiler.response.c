static int itoa(int n, char *buf)
{
 char *p = buf;
 if (n < 0) {
  *buf++ = '-';
  n = 0 - n;
 }
 char *q = buf;
 while (1) {
  int m = n / 10;
  int r = n - m * 10;
  *q++ = '0' + r;
  if (m == 0) break;
  n = m;
 }
 *q = '\0';
 int len = q - buf;
 int i = 0;
 while (1) {
  if (i >= len / 2) break;
  char t = buf[i];
  buf[i] = buf[len - 1 - i];
  buf[len - 1 - i] = t;
  i++;
 }
 return q - p;
}
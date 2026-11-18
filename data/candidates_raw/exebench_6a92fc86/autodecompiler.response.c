static int read_int(char *s, int *plen)
{
 int c, i, n, len;

 n = 0;
 len = 0;
 for (;;) {
  if (!s[len] || s[len] < '0' || s[len] > '9')
   break;
  c = s[len] - '0';
  n = n * 10 + c;
  len++;
 }
 *plen = len;
 return n;
}
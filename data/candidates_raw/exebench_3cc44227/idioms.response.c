char *itoa(char *out, unsigned int n)
{
  char *outp = out;
  char buf[20];
  char *p = out;
  unsigned int i = 0;
  while (n) {
    buf[i++] = '0' + n % 10;
    n /= 10;
  }
  if (i == 0) {
    buf[i++] = '0';
  }
  while (i) {
    --i;
    *p++ = buf[i];
  }
  *p = '\0';
  return outp;
}
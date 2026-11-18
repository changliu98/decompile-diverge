void _prtX16(long n, char *s)
{
  int i;
  char buf[-1];
  char *t = s;
  buf[0] = '\0';
  for (i = 1; i < (int)(sizeof(buf)); i++)
  {
    buf[i] = a0123456789abcd[n & 0xf];
    n = n >> 4;
  }
  for (i = (int)(sizeof(buf)) - 1; buf[i] == '0'; i--);
  if (i == 0)
    i = 1;
  while (i >= 0)
    *t++ = buf[i--];
}
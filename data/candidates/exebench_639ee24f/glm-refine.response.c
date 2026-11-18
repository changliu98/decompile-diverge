int __cdecl itostr(char *buf, int buflen, int x)
{
  char tmp;
  char *beg;
  int cnt = 0;
  
  if (buflen <= 0)
    return 0;

  char *ptr = buf;
  int remaining = buflen;
  int val = x;

  if (x < 0)
  {
    *buf = '-';
    ptr = buf + 1;
    remaining = buflen - 1;
    cnt = 1;
    val = -x;
  }

  if (remaining <= 0)
    return cnt;

  beg = ptr;
  do
  {
    *ptr++ = val % 10 + '0';
    ++cnt;
    if (--remaining <= 0)
      return cnt;
    val /= 10;
  }
  while (val > 0);

  *ptr = '\0';

  // Reverse the string in-place
  for (char *end = ptr - 1; beg < end; --end)
  {
    tmp = *beg;
    *beg = *end;
    *end = tmp;
    ++beg;
  }

  return cnt;
}
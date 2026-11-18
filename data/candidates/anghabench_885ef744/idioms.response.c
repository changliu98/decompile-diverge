void ui2a(int num, int base, int upper, char *str)
{
  int i = num;
  int n = 0;
  int d = 1;
  while (num / d >= base)
    d *= base;
  while (d)
  {
    int dgt = i / d;
    i %= d;
    d /= base;
    if (n || dgt > 0 || d == 0)
    {
      char c = dgt < 10 ? '0' : (upper ? 'A' : 'a') - 10;
      *str++ = c + dgt;
      ++n;
    }
  }
  *str = '\0';
}
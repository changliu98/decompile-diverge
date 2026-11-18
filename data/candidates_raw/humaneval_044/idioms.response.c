void itoa(int n, int base, char *str)
{
  int i = n;
  int b = base;
  char *s = str;
  char buf[32];
  int index = 0;
  while (i > 0)
  {
    buf[index++] = i % b + '0';
    i /= b;
  }
  int j = 0;
  while (index > 0)
  {
    s[j++] = buf[--index];
  }
  s[j] = '\0';
}
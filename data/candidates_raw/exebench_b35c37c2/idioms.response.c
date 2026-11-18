void int2hex(unsigned int value, char *str)
{
  char tmp[16];
  unsigned int i = value;
  char *s = str;
  unsigned int j = 0;
  unsigned int max;
  if (value == 0)
  {
    s[0] = '0';
    s[1] = '\0';
  }
  else
  {
    while (i > 0)
    {
      unsigned int digit = i % 16;
      tmp[j++] = (digit < 10 ? '0'+digit : 'a'+(digit - 10));
      i = i / 16;
    }
    max = j;
    for (j = j; j > 0; j--)
    {
      s[max - j] = tmp[j - 1];
    }
    s[max] = '\0';
  }
}
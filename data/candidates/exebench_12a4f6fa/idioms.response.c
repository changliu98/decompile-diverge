void putoct(char *str, unsigned short val)
{
  char *p;
  char c;
  str[7] = '\0';
  str[6] = ' ';
  p = str + 5;
  str[5] = (val & 0x07) + '0';
  while (p != str)
    {
      val = val >> 3;
      if (val == 0)
 c = ' ';
      else
 c = (val & 0x07) + '0';
      *(--p) = c;
    }
}
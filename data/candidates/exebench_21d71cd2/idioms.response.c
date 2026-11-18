int obdRevConvert_23(float f, char *str, int precision)
{
  char *p = str;
  int i;
  int sign = (f < 0);
  if (sign)
    f = -f;
  if (f >= 1.0)
    i = f;
  else
    i = 0;
  f -= i;
  do
    {
      if (i >= 10)
 {
   *p++ = (char)((i % 10) + '0');
   i /= 10;
 }
      else
 {
   *p++ = (char)(i + '0');
   i = 0;
 }
    }
  while (i > 0);
  if (sign)
    *p++ = '-';
  if (f > 0.0)
    {
      *p++ = '.';
      f = f * 10.0f;
      i = (int)f;
      do
 {
   *p++ = (char)(i + '0');
   f = f * 10.0f - i;
   i = (int)f;
 }
      while (precision-- > 1);
    }
  *p = '\0';
  return p - str;
}
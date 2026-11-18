char *str_rev(char *str)
{
  char *p1 = str;
  char *p2 = str;
  char tmp;
  while(*p2++)
    ;
  p2 -= 2;
  while(p1 < p2)
  {
    tmp = *p1;
    *p1++ = *p2;
    *p2-- = tmp;
  }
  return str;
}
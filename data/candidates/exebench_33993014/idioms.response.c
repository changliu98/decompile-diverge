int LI_ltostr(char *str, long val)
{
  char *s = str;
  char *e = str;
  char t;
  int len = 1;
  if (val < 0)
  {
    len++;
    *s++ = '-';
    val = -val;
  }
  e = s;
  while (val > 9)
  {
    *e++ = (char)(val % 10 + '0');
    val /= 10;
  }
  *e = (char)(val + '0');
  e++;
  *e = '\0';
  len += e - s;
  for (; s < e; s++)
  {
    t = *e;
    *e = *s;
    *s = t;
    e--;
  }
  return len;
}
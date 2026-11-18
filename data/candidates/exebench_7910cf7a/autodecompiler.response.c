char *strset(char *s, int c)
{
 char *p = s;
 while (*p)
  *p++ = c;
 return s;
}
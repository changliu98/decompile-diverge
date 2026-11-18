int __cdecl endStrider(char *s, int *addend)
{
  *addend = 0;
  return strstr(s, "//") != 0LL;
}
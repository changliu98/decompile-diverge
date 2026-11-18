void __cdecl break_at(char *str, char c)
{
  char *p = strchr(str, c);
  if (p)
    *p = '\0';
}
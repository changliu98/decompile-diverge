void __cdecl stress_chop(char *str, const char ch_0)
{
  char *ptr = strchr(str, ch_0);
  if (ptr)
    *ptr = '\0';
}
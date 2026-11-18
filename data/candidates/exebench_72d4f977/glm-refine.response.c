int __cdecl endGB(char *s, int *addend)
{
  *addend = 0;

  if (strstr(s, "//") != NULL)
    return 1;

  return strstr(s, "LOCUS") == s;
}
void __cdecl numconv(char *numstr)
{
  while (*numstr)
  {
    *numstr++ -= '0';
  }
}
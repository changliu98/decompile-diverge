void __cdecl func0(char *text)
{
  for (char *p = text; *p; ++p)
  {
    if (*p == ' ')
      *p = '_';
  }
}
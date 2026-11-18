void __cdecl strrev(char *p)
{
  char *q = p;
  char *qa;

  // Find the null terminator
  while (*q)
  {
    ++q;
  }

  // Swap characters in-place using XOR
  for (qa = q - 1; p < qa; --qa)
  {
    *p ^= *qa;
    *qa ^= *p;
    *p++ ^= *qa;
  }
}
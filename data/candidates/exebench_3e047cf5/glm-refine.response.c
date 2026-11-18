void __cdecl ToRNA(char *seq)
{
  while (*seq)
  {
    if (*seq == 'T')
    {
      *seq = 'U';
    }
    else if (*seq == 't')
    {
      *seq = 'u';
    }
    ++seq;
  }
}
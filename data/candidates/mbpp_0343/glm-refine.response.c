void __cdecl func0(const char *s, int *letters, int *digits)
{
  int l = 0;
  int d = 0;

  while (*s)
  {
    unsigned char c = (unsigned char)*s;
    
    // 0x800 corresponds to the _ISdigit flag in glibc's ctype masks
    if (isdigit(c))
    {
      ++d;
    }
    // 0x400 corresponds to the _ISalpha flag in glibc's ctype masks
    else if (isalpha(c))
    {
      ++l;
    }
    ++s;
  }
  
  *letters = l;
  *digits = d;
}
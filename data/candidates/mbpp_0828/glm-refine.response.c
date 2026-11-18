void __cdecl func0(const char *str, int *alphabets, int *digits, int *special)
{
  *alphabets = 0;
  *digits = 0;
  *special = 0;

  for (int i = 0; str[i]; ++i)
  {
    unsigned char c = str[i];
    
    if (isalpha(c))
    {
      ++*alphabets;
    }
    else if (isdigit(c))
    {
      ++*digits;
    }
    else
    {
      ++*special;
    }
  }
}
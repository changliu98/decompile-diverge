void __cdecl func0(const char *string, int *alphabets, int *digits, int *special)
{
  int i; // [rsp+Ch] [rbp-24h]

  *special = 0;
  *digits = 0;
  *alphabets = 0;
  for ( i = 0; string[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[string[i]] & 0x400) != 0 )
    {
      ++*alphabets;
    }
    else if ( ((*__ctype_b_loc())[string[i]] & 0x800) != 0 )
    {
      ++*digits;
    }
    else
    {
      ++*special;
    }
  }
}
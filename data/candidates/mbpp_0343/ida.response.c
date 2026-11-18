void __cdecl func0(const char *s, int *letters, int *digits)
{
  int d; // [rsp+0h] [rbp-20h]
  int l; // [rsp+4h] [rbp-1Ch]

  l = 0;
  d = 0;
  while ( *s )
  {
    if ( ((*__ctype_b_loc())[*(unsigned __int8 *)s] & 0x800) != 0 )
    {
      ++d;
    }
    else if ( ((*__ctype_b_loc())[*(unsigned __int8 *)s] & 0x400) != 0 )
    {
      ++l;
    }
    ++s;
  }
  *letters = l;
  *digits = d;
}
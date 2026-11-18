int __cdecl hex_to_int(char *s, int *x)
{
  int i; // [rsp+0h] [rbp-1Ch]

  *x = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( s[i] < 48 || s[i] > 57 )
    {
      if ( s[i] < 97 || s[i] > 102 )
        return 0;
      *x = s[i] + 16 * *x - 97 + 10;
    }
    else
    {
      *x = s[i] + 16 * *x - 48;
    }
  }
  return 1;
}
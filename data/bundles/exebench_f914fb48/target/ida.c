void __cdecl strupper(char *s)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; s[i]; ++i )
  {
    if ( s[i] >= 97 && s[i] <= 122 )
      s[i] -= 32;
  }
}
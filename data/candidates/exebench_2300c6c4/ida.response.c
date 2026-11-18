char *__cdecl strtoupper(char *s)
{
  char v2; // [rsp+0h] [rbp-14h]
  int i; // [rsp+8h] [rbp-Ch]

  for ( i = 0; i < 8; ++i )
  {
    if ( s[i] < 97 || s[i] > 122 )
      v2 = s[i];
    else
      v2 = s[i] - 32;
    s[i] = v2;
  }
  return s;
}
char *__cdecl upcase(char *orig)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; orig[i]; ++i )
  {
    if ( orig[i] >= 97 && orig[i] <= 122 )
      orig[i] = orig[i] - 97 + 65;
  }
  return orig;
}
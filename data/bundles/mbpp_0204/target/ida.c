int __cdecl func0(char *s, char c)
{
  int i; // [rsp+Ch] [rbp-14h]
  int res; // [rsp+10h] [rbp-10h]

  res = 0;
  for ( i = 0; i < strlen(s); ++i )
  {
    if ( s[i] == c )
      ++res;
  }
  return res;
}
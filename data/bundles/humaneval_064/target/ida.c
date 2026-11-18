int __cdecl func0(const char *s)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int length; // [rsp+8h] [rbp-18h]
  int count; // [rsp+Ch] [rbp-14h]

  count = 0;
  length = strlen(s);
  for ( i = 0; i < length; ++i )
  {
    if ( strchr("aeiouAEIOU", s[i]) )
      ++count;
  }
  if ( length > 0 && (s[length - 1] == 121 || s[length - 1] == 89) )
    ++count;
  return count;
}
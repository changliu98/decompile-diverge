int __cdecl func0(const char *s)
{
  int i; // [rsp+0h] [rbp-10h]
  int sum; // [rsp+4h] [rbp-Ch]

  sum = 0;
  for ( i = 0; s[i]; ++i )
  {
    if ( s[i] >= 65 && s[i] <= 90 )
      sum += s[i];
  }
  return sum;
}
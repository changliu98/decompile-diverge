int __cdecl func0(const char *str)
{
  int i; // [rsp+10h] [rbp-10h]
  int lower_ctr; // [rsp+14h] [rbp-Ch]

  lower_ctr = 0;
  for ( i = 0; i < strlen(str); ++i )
  {
    if ( str[i] >= 97 && str[i] <= 122 )
      ++lower_ctr;
  }
  return lower_ctr;
}
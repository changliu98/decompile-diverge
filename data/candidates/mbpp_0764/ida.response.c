int __cdecl func0(char *str)
{
  int i; // [rsp+10h] [rbp-10h]
  int number_ctr; // [rsp+14h] [rbp-Ch]

  number_ctr = 0;
  for ( i = 0; i < strlen(str); ++i )
  {
    if ( str[i] >= 48 && str[i] <= 57 )
      ++number_ctr;
  }
  return number_ctr;
}
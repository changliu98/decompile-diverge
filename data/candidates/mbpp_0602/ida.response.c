char __cdecl func0(char *str1)
{
  int j; // [rsp+Ch] [rbp-24h]
  int count; // [rsp+10h] [rbp-20h]
  int i; // [rsp+18h] [rbp-18h]
  int length; // [rsp+1Ch] [rbp-14h]

  length = strlen(str1);
  for ( i = 0; i < length; ++i )
  {
    count = 0;
    for ( j = 0; j <= i; ++j )
    {
      if ( str1[j] == str1[i] )
        ++count;
    }
    if ( count > 1 )
      return str1[i];
  }
  return 48;
}
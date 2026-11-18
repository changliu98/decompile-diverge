bool __cdecl func0(const char *str)
{
  int j; // [rsp+18h] [rbp-18h]
  int i; // [rsp+1Ch] [rbp-14h]

  for ( i = 0; i < strlen(str); ++i )
  {
    for ( j = i + 1; j < strlen(str); ++j )
    {
      if ( str[i] == str[j] )
        return 0;
    }
  }
  return 1;
}
void __cdecl sort(char *str)
{
  bool v1; // [rsp+0h] [rbp-12h]
  char t; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]

  for ( j = 1; j < 10; ++j )
  {
    for ( i = 0; ; ++i )
    {
      v1 = 0;
      if ( i < 10 - j )
        v1 = str[i] != 0;
      if ( !v1 )
        break;
      if ( str[i] > str[i + 1] )
      {
        t = str[i];
        str[i] = str[i + 1];
        str[i + 1] = t;
      }
    }
  }
}
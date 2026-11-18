void __cdecl strip(char *str)
{
  int v1; // ecx
  int v2; // ecx
  int common; // [rsp+0h] [rbp-20h]
  int redun; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]
  int ia; // [rsp+14h] [rbp-Ch]

  if ( str )
  {
    for ( i = 1; str[i]; ++i )
    {
      for ( j = 0; j < i; ++j )
      {
        if ( str[j] == str[i] )
        {
          str[i] = -1;
          break;
        }
      }
    }
    redun = 0;
    common = 0;
    for ( ia = 1; str[ia]; ++ia )
    {
      if ( str[ia] == -1 )
      {
        redun = ia;
        while ( str[ia] == -1 )
          ++ia;
        common = ia;
        break;
      }
    }
    if ( redun )
    {
      while ( str[common] )
      {
        if ( str[common] == -1 )
        {
          ++common;
        }
        else
        {
          v1 = redun++;
          str[v1] = str[common];
          v2 = common++;
          str[v2] = -1;
        }
      }
      str[redun] = 0;
    }
  }
}
void __cdecl intToString(int n, char *str)
{
  int t_0; // [rsp+0h] [rbp-1Ch]
  int t; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]
  int ia; // [rsp+8h] [rbp-14h]

  if ( n )
  {
    i = 0;
    for ( t = n; t; t /= 10 )
      ++i;
    str[i] = 0;
    ia = i - 1;
    t_0 = n;
    while ( ia >= 0 )
    {
      str[ia--] = t_0 % 10 + 48;
      t_0 /= 10;
    }
  }
  else
  {
    *str = 48;
    str[1] = 0;
  }
}
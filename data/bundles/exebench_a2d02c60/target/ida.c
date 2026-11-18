int __cdecl ft_pn(const char *str, int *p_n, int i)
{
  bool v4; // [rsp+0h] [rbp-16h]
  char v5; // [rsp+1h] [rbp-15h]

  while ( 1 )
  {
    v5 = 1;
    if ( str[i] != 32 )
    {
      v4 = 0;
      if ( str[i] >= 9 )
        v4 = str[i] <= 13;
      v5 = v4;
    }
    if ( (v5 & 1) == 0 )
      break;
    ++i;
  }
  if ( !str[i] )
    *p_n = -3;
  if ( str[i] == 45 )
    *p_n = -2;
  return i;
}
int __cdecl HPCC_factor235(int n, int *ip_0)
{
  char v3; // [rsp+1h] [rbp-13h]
  char v4; // [rsp+2h] [rbp-12h]
  char v5; // [rsp+3h] [rbp-11h]
  int na; // [rsp+Ch] [rbp-8h]

  na = n;
  ip_0[2] = 0;
  ip_0[1] = 0;
  *ip_0 = 0;
  if ( n % 2 && n % 3 && n % 5 )
    return 1;
  if ( n <= 1 )
    return 1;
  while ( 1 )
  {
    v5 = 0;
    if ( na > 1 )
      v5 = ~((na & 1) != 0);
    if ( (v5 & 1) == 0 )
      break;
    ++*ip_0;
    na >>= 1;
  }
  while ( 1 )
  {
    v4 = 0;
    if ( na > 1 )
      v4 = ~(na % 3 != 0);
    if ( (v4 & 1) == 0 )
      break;
    ++ip_0[1];
    na /= 3;
  }
  while ( 1 )
  {
    v3 = 0;
    if ( na > 1 )
      v3 = ~(na % 5 != 0);
    if ( (v3 & 1) == 0 )
      break;
    ++ip_0[2];
    na /= 5;
  }
  return na != 1;
}
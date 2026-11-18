int __cdecl itoa(char *a, const int i)
{
  int v3; // [rsp+4h] [rbp-28h]
  int j; // [rsp+8h] [rbp-24h]
  int temp; // [rsp+10h] [rbp-1Ch]
  int tempa; // [rsp+10h] [rbp-1Ch]
  int charc; // [rsp+14h] [rbp-18h]

  if ( i )
  {
    charc = 0;
    temp = 1;
    if ( i >= 0 )
      v3 = i;
    else
      v3 = -i;
    while ( v3 % temp != v3 )
    {
      ++charc;
      temp *= 10;
    }
    if ( i < 0 )
      ++charc;
    tempa = 1;
    for ( j = charc - 1; j >= 0; --j )
    {
      a[j] = (v3 - v3 % tempa) / tempa % 10 + 48;
      tempa *= 10;
    }
    if ( i < 0 )
      *a = 45;
    a[charc] = 0;
    return charc;
  }
  else
  {
    *a = 48;
    a[1] = 0;
    return 2;
  }
}
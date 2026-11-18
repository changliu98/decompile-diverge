unsigned int __cdecl parse_int(char *str, int *num)
{
  int t; // [rsp+2h] [rbp-2Ch]
  int length; // [rsp+6h] [rbp-28h]
  int digit; // [rsp+Ah] [rbp-24h]
  int minus_fl; // [rsp+Eh] [rbp-20h]
  int i; // [rsp+12h] [rbp-1Ch]

  t = 1;
  *num = 0;
  minus_fl = *str == 45;
  i = minus_fl;
  for ( length = 1; str[length]; ++length )
    t *= 10;
  while ( str[i] )
  {
    digit = str[i] - 48;
    if ( digit > 9 || digit < 0 )
      return 0;
    if ( i > 0 )
      t /= 10;
    *num += digit * t;
    ++i;
  }
  if ( minus_fl )
    *num = -*num;
  return 1;
}
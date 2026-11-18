int __cdecl func0(int n)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int temp; // [rsp+4h] [rbp-18h]
  int total; // [rsp+8h] [rbp-14h]
  int i; // [rsp+Ch] [rbp-10h]
  int count; // [rsp+10h] [rbp-Ch]
  int na; // [rsp+18h] [rbp-4h]

  na = n;
  count = 0;
  for ( i = 2; i * i <= n; ++i )
  {
    total = 0;
    while ( !(na % i) )
    {
      na /= i;
      ++total;
    }
    temp = 0;
    for ( j = 1; j + temp <= total; ++j )
    {
      temp += j;
      ++count;
    }
  }
  if ( na != 1 )
    ++count;
  return count;
}
int __cdecl func0(int n)
{
  int curr_term; // [rsp+4h] [rbp-1Ch]
  int curr_sum; // [rsp+8h] [rbp-18h]
  int count; // [rsp+Ch] [rbp-14h]
  int i; // [rsp+10h] [rbp-10h]
  int res; // [rsp+14h] [rbp-Ch]
  int na; // [rsp+18h] [rbp-8h]

  na = n;
  if ( n % 2 )
    return 0;
  res = 1;
  for ( i = 2; i <= (int)sqrt((double)na) + 1; ++i )
  {
    count = 0;
    curr_sum = 1;
    curr_term = 1;
    while ( !(na % i) )
    {
      ++count;
      na /= i;
      if ( i == 2 && count == 1 )
        curr_sum = 0;
      curr_term *= i;
      curr_sum += curr_term;
    }
    res *= curr_sum;
  }
  if ( na >= 2 )
    res *= na + 1;
  return res;
}
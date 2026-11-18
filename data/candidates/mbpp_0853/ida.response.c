int __cdecl func0(int n)
{
  int curr_term; // [rsp+8h] [rbp-18h]
  int curr_sum; // [rsp+Ch] [rbp-14h]
  int count; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]
  int res; // [rsp+18h] [rbp-8h]

  res = 1;
  while ( !(n % 2) )
    n /= 2;
  for ( i = 3; sqrt((double)n) + 1.0 >= (double)i; i += 2 )
  {
    count = 0;
    curr_sum = 1;
    curr_term = 1;
    while ( !(n % i) )
    {
      ++count;
      n /= i;
      curr_term *= i;
      curr_sum += curr_term;
    }
    res *= curr_sum;
  }
  if ( n >= 2 )
    res *= n + 1;
  return res;
}
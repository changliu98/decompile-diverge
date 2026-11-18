int __cdecl gcd(int a, int b)
{
  int min_val = (a < b) ? a : b;
  int max_val = (a > b) ? a : b;

  if ( !min_val )
    return max_val;
  if ( min_val == 1 )
    return 1;
  return gcd(min_val, max_val % min_val);
}
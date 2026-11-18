int __cdecl func0(int *nums, int length)
{
  int n; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  int sum; // [rsp+8h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < length; ++i )
  {
    n = nums[i];
    if ( n < 0 )
      n = -n;
    while ( n > 0 )
    {
      sum += n % 10;
      n /= 10;
    }
  }
  return sum;
}
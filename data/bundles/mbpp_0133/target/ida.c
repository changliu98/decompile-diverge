int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] < 0 )
      sum += nums[i];
  }
  return sum;
}
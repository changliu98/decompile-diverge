int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-18h]
  int min_val; // [rsp+4h] [rbp-14h]
  int max_val; // [rsp+8h] [rbp-10h]

  max_val = 0x80000000;
  min_val = 0x7FFFFFFF;
  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] > max_val )
      max_val = nums[i];
    if ( nums[i] < min_val )
      min_val = nums[i];
  }
  return max_val - min_val;
}
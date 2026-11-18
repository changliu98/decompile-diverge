int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-18h]
  int min_num; // [rsp+4h] [rbp-14h]
  int max_num; // [rsp+8h] [rbp-10h]

  max_num = 0x80000000;
  min_num = 0x7FFFFFFF;
  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] > max_num )
      max_num = nums[i];
    if ( nums[i] < min_num )
      min_num = nums[i];
  }
  return min_num + max_num;
}
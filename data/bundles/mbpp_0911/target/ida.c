int __cdecl func0(int *nums, int size)
{
  int temp; // [rsp+20h] [rbp-20h]
  int j; // [rsp+24h] [rbp-1Ch]
  int i; // [rsp+28h] [rbp-18h]

  if ( size < 3 )
    return -1;
  for ( i = 0; i < size - 1; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      if ( nums[i] < nums[j] )
      {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }
  if ( nums[2] * nums[1] * *nums <= nums[size - 2] * nums[size - 1] * *nums )
    return nums[size - 2] * nums[size - 1] * *nums;
  else
    return nums[2] * nums[1] * *nums;
}
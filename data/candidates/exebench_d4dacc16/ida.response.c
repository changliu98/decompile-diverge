void __cdecl findMinMax(long *nums, long *min, long *max)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 1; i < 5; ++i )
  {
    if ( nums[i] < *min )
      *min = nums[i];
    if ( nums[i] > *max )
      *max = nums[i];
  }
}
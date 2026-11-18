int __cdecl removeElement(int *nums, int numsSize, int val)
{
  int i; // [rsp+0h] [rbp-14h]

  i = 0;
  while ( i < numsSize )
  {
    if ( nums[i] == val )
      nums[i] = nums[--numsSize];
    else
      ++i;
  }
  return numsSize;
}
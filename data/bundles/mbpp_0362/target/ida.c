int __cdecl func0(int *nums, int size)
{
  int j; // [rsp+0h] [rbp-20h]
  int occu; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]
  int result; // [rsp+Ch] [rbp-14h]
  int max_val; // [rsp+10h] [rbp-10h]

  max_val = 0;
  result = *nums;
  for ( i = 0; i < size; ++i )
  {
    occu = 0;
    for ( j = 0; j < size; ++j )
    {
      if ( nums[j] == nums[i] )
        ++occu;
    }
    if ( occu > max_val )
    {
      max_val = occu;
      result = nums[i];
    }
  }
  return result;
}
__int64 __cdecl func0(__int64 *nums, int size)
{
  __int64 v3; // [rsp+0h] [rbp-30h]
  int i; // [rsp+Ch] [rbp-24h]
  __int64 min; // [rsp+10h] [rbp-20h]
  __int64 current; // [rsp+18h] [rbp-18h]

  current = *nums;
  min = *nums;
  for ( i = 1; i < size; ++i )
  {
    if ( current >= 0 )
      v3 = nums[i];
    else
      v3 = nums[i] + current;
    current = v3;
    if ( v3 < min )
      min = v3;
  }
  return min;
}
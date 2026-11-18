int __cdecl func0(int *nums, int size)
{
  int n; // [rsp+0h] [rbp-20h]
  int i; // [rsp+Ch] [rbp-14h]
  int num; // [rsp+10h] [rbp-10h]

  num = 0;
  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] > 10 )
    {
      for ( n = nums[i]; n >= 10; n /= 10 )
        ;
      if ( n % 2 == 1 && nums[i] % 10 % 2 == 1 )
        ++num;
    }
  }
  return num;
}
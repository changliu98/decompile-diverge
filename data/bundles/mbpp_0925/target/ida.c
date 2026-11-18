int __cdecl func0(int *nums, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int product; // [rsp+4h] [rbp-10h]

  product = 1;
  for ( i = 0; i < size; ++i )
    product *= nums[i];
  return product;
}
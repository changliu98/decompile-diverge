int __cdecl func0(int *list_nums, size_t list_length)
{
  size_t i; // [rsp+4h] [rbp-20h]
  int max_product; // [rsp+10h] [rbp-14h]

  max_product = list_nums[1] * *list_nums;
  for ( i = 1LL; i < list_length - 1; ++i )
  {
    if ( list_nums[i + 1] * list_nums[i] > max_product )
      max_product = list_nums[i + 1] * list_nums[i];
  }
  return max_product;
}
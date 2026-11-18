int func0(int *list_nums,size_t list_length)

{
  int product;
  size_t i;
  int max_product;
  size_t list_length_local;
  int *list_nums_local;
  
  max_product = *list_nums * list_nums[1];
  for (i = 1; i < list_length - 1; i = i + 1) {
    if (max_product < list_nums[i] * list_nums[i + 1]) {
      max_product = list_nums[i] * list_nums[i + 1];
    }
  }
  return max_product;
}
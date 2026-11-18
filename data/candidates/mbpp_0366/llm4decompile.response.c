int func0(int *list_nums, size_t list_length) {
 int max_product = list_nums[0] * list_nums[1];
 for (int i = 1; i < list_length - 1; i++) {
  if (list_nums[i] * list_nums[i + 1] > max_product) {
   max_product = list_nums[i] * list_nums[i + 1];
  }
 }
 return max_product;
}
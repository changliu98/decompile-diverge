int func0(int list_nums[], size_t list_length) {
  int max_product = list_nums[0] * list_nums[1];
  for (size_t i = 1; i < list_length - 1; i++) {
    int product = list_nums[i] * list_nums[i + 1];
    if (product > max_product) {
      max_product = product;
    }
  }
  return max_product;
}
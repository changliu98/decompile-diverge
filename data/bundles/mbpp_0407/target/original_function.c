int func0(int n) {
  char nums[11];
  sprintf(nums, "%d", n);
  size_t length = strlen(nums);
  for (int i = length - 2; i >= 0; --i) {
    if (nums[i] < nums[i + 1]) {
      char z[11];
      strcpy(z, nums + i);
      size_t z_len = strlen(z);
      char y = z[1];
      for (size_t j = 1; j < z_len; ++j) {
        if (z[j] > z[0] && z[j] < y) {
          y = z[j];
        }
      }
      for (size_t j = 0; j < z_len; ++j) {
        if (z[j] == y) {
          for (size_t k = j; k < z_len - 1; ++k) {
            z[k] = z[k + 1];
          }
          z[z_len - 1] = '\0';
          break;
        }
      }
      qsort(z, strlen(z), sizeof(char),
            (int (*)(const void *, const void *))strcmp);
      nums[i] = y;
      strcpy(nums + i + 1, z);
      return atoi(nums);
    }
  }
  return 0;
}
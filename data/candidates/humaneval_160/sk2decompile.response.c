int _calculate(char **ops, int *nums, int ops_size, int nums_size) {
  int *nums_copy = malloc(nums_size * sizeof(int));
  int *nums_index = malloc(nums_size * sizeof(int));
  int i;
  for (i = 0; i < nums_size; i++) {
    nums_copy[i] = nums[i];
    nums_index[i] = i;
  }
  for (i = 0; i < ops_size; i++) {
    if (!strcmp(ops[i], "**")) {
      while (nums_index[nums_index[i]] != nums_index[i]) {
        nums_index[i] = nums_index[nums_index[i]];
      }
      while (nums_index[nums_index[i + 1]] != nums_index[i + 1]) {
        nums_index[i + 1] = nums_index[nums_index[i + 1]];
      }
      nums_copy[nums_index[i]] =
          pow(nums_copy[nums_index[i]], nums_copy[nums_index[i + 1]]);
      nums_index[i + 1] = nums_index[i];
    }
  }
  for (i = 0; i < ops_size; i++) {
    if (!strcmp(ops[i], "*") || !strcmp(ops[i], "//")) {
      while (nums_index[nums_index[i]] != nums_index[i]) {
        nums_index[i] = nums_index[nums_index[i]];
      }
      while (nums_index[nums_index[i + 1]] != nums_index[i + 1]) {
        nums_index[i + 1] = nums_index[nums_index[i + 1]];
      }
      if (!strcmp(ops[i], "*")) {
        nums_copy[nums_index[i]] =
            nums_copy[nums_index[i]] * nums_copy[nums_index[i + 1]];
      } else {
        nums_copy[nums_index[i]] =
            nums_copy[nums_index[i]] / nums_copy[nums_index[i + 1]];
      }
      nums_index[i + 1] = nums_index[i];
    }
  }
  for (i = 0; i < ops_size; i++) {
    if (!strcmp(ops[i], "+") || !strcmp(ops[i], "-")) {
      while (nums_index[nums_index[i]] != nums_index[i]) {
        nums_index[i] = nums_index[nums_index[i]];
      }
      while (nums_index[nums_index[i + 1]] != nums_index[i + 1]) {
        nums_index[i + 1] = nums_index[nums_index[i + 1]];
      }
      if (!strcmp(ops[i], "+")) {
        nums_copy[nums_index[i]] =
            nums_copy[nums_index[i]] + nums_copy[nums_index[i + 1]];
      } else {
        nums_copy[nums_index[i]] =
            nums_copy[nums_index[i]] - nums_copy[nums_index[i + 1]];
      }
      nums_index[i + 1] = nums_index[i];
    }
  }
  int result = nums_copy[0];
  free(nums_copy);
  free(nums_index);
  return result;
}
void func0(int *arr, int n, int **res, int *res_size) {
  *res = malloc(n * sizeof(int));
  *res_size = 0;
  for (int i = 0; i < n; i++) {
    int num = arr[i];
    bool has_even_digit = num == 0;
    while (num > 0 && !has_even_digit) {
      if (num % 2 == 0) {
        has_even_digit = true;
      }
      num /= 10;
    }
    if (!has_even_digit) {
      (*res)[*res_size] = arr[i];
      (*res_size)++;
    }
  }
  for (int i = 0; i < *res_size - 1; i++) {
    for (int j = 0; j < *res_size - i - 1; j++) {
      if ((*res)[j] > (*res)[j + 1]) {
        int temp = (*res)[j];
        (*res)[j] = (*res)[j + 1];
        (*res)[j + 1] = temp;
      }
    }
  }
}
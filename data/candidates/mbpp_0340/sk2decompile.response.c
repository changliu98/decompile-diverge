int func0(int* arr, int arrSize) {
  int positive[arrSize];
  int positiveSize = 0;
  for (int i = 0; i < arrSize; i++) {
    if (arr[i] > 0) {
      positive[positiveSize++] = arr[i];
    }
  }
  qsort(positive, positiveSize, sizeof(int), cmp);
  int sum = 0;
  for (int i = 0; i < 3 && i < positiveSize; i++) {
    sum += positive[i];
  }
  return sum;
}
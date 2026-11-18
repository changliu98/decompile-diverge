int func0(int lst[], int size) {
  int positive_numbers[size];
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (lst[i] > 0) {
      positive_numbers[count++] = lst[i];
    }
  }
  qsort(positive_numbers, count, sizeof(int), compare);
  int sum = 0;
  for (int i = 0; i < 3 && i < count; i++) {
    sum += positive_numbers[i];
  }
  return sum;
}
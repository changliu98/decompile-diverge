int* func0(int n) {
  int* arr = malloc(n * sizeof(int));
  int i, sum = 0, fact = 1;
  for (i = 1; i <= n; i++) {
    sum += i;
    fact *= i;
    if (i % 2 == 0)
      arr[i - 1] = fact;
    else
      arr[i - 1] = sum;
  }
  return arr;
}
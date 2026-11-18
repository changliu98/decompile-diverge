char *func0(int *array, int n, int p) {
  int sum = 0;
  int i;
  for (i = 0; i < n; i++)
    sum += array[i];
  if (p == 1) {
    if (sum % 2 == 0)
      return "ODD";
    else
      return "EVEN";
  }
  return "EVEN";
}
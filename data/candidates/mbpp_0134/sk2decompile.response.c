char* func0(int* a, int a_size, int k) {
  int sum = 0;
  for (int i = 0; i < a_size; i++) {
    sum += a[i];
  }
  if (k == 1) {
    if (sum % 2 == 0) {
      return "EVEN";
    }
  }
  return "EVEN";
}
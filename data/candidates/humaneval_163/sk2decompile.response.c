void func0(int a, int b, int *arr, int *size) {
  int i;
  *size = 0;
  if (b < a) {
    int temp = a;
    a = b;
    b = temp;
  }
  for (i = a; i <= b; i++) {
    if (i < 10 && i % 2 == 0) {
      arr[(*size)++] = i;
    }
  }
}
int func0(int n) {
  int m = n;
  if (n <= 2) return m;
  int k = 2 * m;
  int arr[100];
  int size = 0;
  for (int i = m; i > 1; i--) {
    if (2 * i > m) {
      arr[size++] = i;
    }
  }
  for (int j = 0; j < size; j++) {
    if (k % arr[j] == 0) {
      if (j == size - 1 && k % arr[j] == 0) {
        return k;
      }
    } else {
      k += m;
      j = -1;
    }
  }
}
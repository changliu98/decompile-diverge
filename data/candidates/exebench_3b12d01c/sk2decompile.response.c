int int2arr(int *arr, int n) {
  int i = 0;
  while (n) {
    arr[i] = n % 10;
    n /= 10;
    i++;
  }
  return i;
}
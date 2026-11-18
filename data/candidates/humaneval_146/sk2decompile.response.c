int func0(int* arr, int n) {
  int temp, i, count = 0;
  for (i = 0; i < n; i++) {
    if (arr[i] > 10) {
      temp = arr[i];
      while (temp >= 10) {
        temp /= 10;
      }
      if (temp % 2 == 1 && arr[i] % 10 % 2 == 1) {
        count++;
      }
    }
  }
  return count;
}
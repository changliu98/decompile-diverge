int _abs(int *arr, int len) {
  if (len == 0) {
    return -32768;
  }
  int sum = 0;
  int sign = 1;
  for (int i = 0; i < len; i++) {
    sum += abs(arr[i]);
    if (arr[i] == 0) {
      sign = 0;
    }
    if (arr[i] < 0) {
      sign = -sign;
    }
  }
  return sum * sign;
}
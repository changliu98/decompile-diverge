int _second_smallest(int* arr, int len) {
  if (len < 2) {
    return -1;
  }
  int first = 0x7fffffff;
  int second = 0x7fffffff;
  for (int i = 0; i < len; i++) {
    if (arr[i] < first) {
      second = first;
      first = arr[i];
    } else if (arr[i] < second && arr[i] != first) {
      second = arr[i];
    }
  }
  if (second == 0x7fffffff) {
    return -1;
  }
  return second;
}
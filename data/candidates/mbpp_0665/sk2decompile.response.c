void func0(int *arr, int n, int *arr2) {
  int first = arr[0];
  int count = 0;
  int index = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] == first) {
      count++;
    }
  }
  for (int i = 0; i < n; i++) {
    if (arr[i] != first) {
      arr2[index++] = arr[i];
    }
  }
  for (int i = 0; i < count; i++) {
    arr2[index++] = first;
  }
}
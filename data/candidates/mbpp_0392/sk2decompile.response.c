int func0(int n) {
  int arr[n + 1];
  arr[0] = 0;
  arr[1] = 1;
  for (int i = 2; i < n + 1; i++) {
    arr[i] = i;
    int temp = arr[i / 2] + arr[i / 3] + arr[i / 4];
    if (temp > arr[i]) {
      arr[i] = temp;
    }
  }
  return arr[n];
}
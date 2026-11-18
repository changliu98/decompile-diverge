int func0(int n) {
  int i;
  int temp;
  int *p = &temp;
  int arr[n + 1];
  arr[0] = 0;
  arr[1] = 1;
  for (i = 2; i <= n; i++) {
    temp = arr[i / 2];
    temp += arr[i / 3];
    temp += arr[i / 4];
    arr[i] = temp;
    if (arr[i] < i) arr[i] = i;
  }
  return arr[n];
}
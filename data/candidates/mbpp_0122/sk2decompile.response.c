int func0(int n) {
  int arr[3000];
  int arr2[3000];
  int num = n;
  int i, j, k;
  memset(arr2, 0, sizeof(arr2));
  k = 0;
  for (j = 2; j < 3000; j++) {
    if (arr2[j] == 0) {
      arr2[j] = 1;
      for (i = j + j; i < 3000; i += j) {
        arr2[i]--;
        if (arr2[i] == -3) {
          arr[k++] = i;
        }
      }
    }
  }
  int a, b;
  for (a = 0; a < k - 1; a++) {
    for (b = 0; b < k - a - 1; b++) {
      if (arr[b] > arr[b + 1]) {
        int temp = arr[b];
        arr[b] = arr[b + 1];
        arr[b + 1] = temp;
      }
    }
  }
  return arr[num - 1];
}
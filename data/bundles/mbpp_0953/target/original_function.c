int func0(int ar[], int n) {
  int res = 0;
  int i, count;
  for (int step = 0; step < n - 1; ++step) {
    for (int i = 0; i < n - step - 1; ++i) {
      if (ar[i] > ar[i + 1]) {
        int temp = ar[i];
        ar[i] = ar[i + 1];
        ar[i + 1] = temp;
      }
    }
  }
  i = 0;
  while (i < n) {
    count = 1;
    while (i + 1 < n && ar[i] == ar[i + 1]) {
      count++;
      i++;
    }
    if (res < count) {
      res = count;
    }
    i++;
  }
  return res;
}
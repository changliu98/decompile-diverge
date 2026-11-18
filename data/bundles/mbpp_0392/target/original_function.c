int func0(int n) {
  int res[n + 1];
  res[0] = 0;
  res[1] = 1;
  int i = 2;
  while (i < n + 1) {
    res[i] = i;
    int temp = res[i / 2] + res[i / 3] + res[i / 4] + res[i / 5];
    if (temp > res[i]) res[i] = temp;
    i++;
  }
  return res[n];
}
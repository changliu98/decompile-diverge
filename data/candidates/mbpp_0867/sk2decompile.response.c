int func0(int *a, int n) {
  int i, c = 0;
  for (i = 0; i < n; i++) {
    if (a[i] % 2) c++;
  }
  if (c % 2)
    return 1;
  else
    return 2;
}
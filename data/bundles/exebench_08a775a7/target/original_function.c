int next(int mask[], int n) {
  int i;
  for (i = 0; (i < n) && mask[i]; ++i)
    mask[i] = 0;

  if (i < n) {
    mask[i] = 1;
    return 1;
  }
  return 0;
}
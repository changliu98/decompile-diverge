int func0(int *li, int size, int min, int max) {
  int i, ctr;
  ctr = 0;
  for (i = 0; i < size; i++) {
    if (li[i] >= min && li[i] <= max)
      ctr++;
  }
  return ctr;
}
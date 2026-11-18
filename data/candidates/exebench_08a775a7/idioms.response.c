int next(int *mask, int n)
{
  int i;
  for (i = 0; ; i++) {
    int found = 0;
    if (i < n)
      found = mask[i] != 0;
    if (!found)
      break;
    mask[i] = 0;
  }
  if (i < n) {
    mask[i] = 1;
    return 1;
  }
  return 0;
}
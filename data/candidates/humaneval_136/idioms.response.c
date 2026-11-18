void func0(int *list, int size, int *minandmax)
{
  int maxneg = 0;
  int minpos = 0;
  int i;
  for (i = 0; i < size; i++) {
    if (list[i] < 0) {
      if (maxneg == 0 || list[i] > maxneg)
        maxneg = list[i];
    }
    if (list[i] > 0) {
      if (minpos == 0 || list[i] < minpos)
        minpos = list[i];
    }
  }
  minandmax[0] = maxneg;
  minandmax[1] = minpos;
  return;
}
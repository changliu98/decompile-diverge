int get_min(int *list, int *val)
{
  int i; int count = 0;
  for (i = 0; i < 9; i++) {
    if (list[i]) {
      count++;
      *val = list[i];
    }
  }
  return count;
}
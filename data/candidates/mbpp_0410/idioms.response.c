int func0(char **list, int size)
{
  int i;
  int current;
  int min = 0x7fffffff;
  for (i = 0; i < size; i++) {
    if (sscanf(list[i], "%d", &current) == 1) {
      if (current < min) {
        min = current;
      }
    }
  }
  return min;
}
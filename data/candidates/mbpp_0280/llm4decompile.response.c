int func0(int *dlist, int size, int item, int *pos)
{
  int found;
  *pos = 0;
  found = 0;
  while (*pos < size && !found) {
    if (dlist[*pos] == item) {
      found = 1;
    } else {
      *pos = *pos + 1;
    }
  }
  return found;
}
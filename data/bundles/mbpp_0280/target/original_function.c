bool func0(int dlist[], int size, int item, int *pos) {
  *pos = 0;
  bool found = false;
  while (*pos < size && !found) {
    if (dlist[*pos] == item) {
      found = true;
    } else {
      (*pos)++;
    }
  }
  return found;
}
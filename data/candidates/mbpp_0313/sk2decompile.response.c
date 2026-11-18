int _find_first_free_slot(int *slots, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (slots[i] >= 0) {
      return slots[i];
    }
  }
  return -1;
}
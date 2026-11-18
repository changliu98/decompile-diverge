int func0(int list[], int list_size) {
  int neg_count = 0;
  for (int i = 0; i < list_size; i++) {
    if (list[i] <= 0) {
      neg_count += 1;
    }
  }
  return neg_count;
}
int _get_index(int n) {
  int index = (n + 1) * n / 2;
  index = index * (index - 1);
  return index;
}
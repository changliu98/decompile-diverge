int func0(int xs[], int size) {
  int min_val = INT_MAX;
  for (int i = 0; i < size; i++) {
    if (xs[i] < min_val) {
      min_val = xs[i];
    }
  }
  return min_val;
}
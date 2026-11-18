int getMax(int a, int b, int c, int *max) {
  int max_index = 1;
  int max_value = a;
  if (b > max_value) {
    max_value = b;
    max_index = 2;
  }
  if (c > max_value) {
    max_value = c;
    max_index = 3;
  }
  *max = max_value;
  return max_index;
}
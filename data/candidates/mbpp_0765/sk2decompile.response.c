int _get_size(int n) {
  double size;
  size = log2((double)(n + 1));
  size += log2((double)(n + 1));
  return (int)size + n + 1;
}
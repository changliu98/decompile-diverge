void sum(int a, int *b) {
  if (b == NULL) {
    return;
  }
  *b += a;
  return;
}
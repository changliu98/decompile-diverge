void swap(int *a, int *b) {
  int temp;
  if (a == NULL || b == NULL) {
    return;
  }
  temp = *a;
  *a = *b;
  *b = temp;
}
void func0(int *a, int n) {
  int i;
  int tmp;
  heapify(a, n);
  for (i = n - 1; i > 0; i--) {
    tmp = a[i];
    a[i] = a[0];
    a[0] = tmp;
    shift_down(a, 0, i);
  }
}
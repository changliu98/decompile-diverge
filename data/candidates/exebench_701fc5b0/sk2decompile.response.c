int foo(int *a) {
  int i = 0;
  int j;
  for (j = 0; j < 10; j++) {
    a[j] = i++;
  }
  return i + j;
}
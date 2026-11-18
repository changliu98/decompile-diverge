void test1(int *a) {
  int i = 0;
  do {
    a[i] = i;
    i++;
  } while (i < 17);
}
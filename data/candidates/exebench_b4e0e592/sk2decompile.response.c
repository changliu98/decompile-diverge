void foo(int *p) {
  int x;
  x = *p;
  x++;
  *p = x;
}
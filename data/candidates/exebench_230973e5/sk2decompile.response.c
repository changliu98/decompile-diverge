void a_store(volatile int *p, int x) {
  int y;
  y = *p;
  *p = x;
}
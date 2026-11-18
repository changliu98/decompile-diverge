void release(volatile int *lock) {
  int tmp;
  tmp = *lock;
  tmp = 0;
  *lock = tmp;
}
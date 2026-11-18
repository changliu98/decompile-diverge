int test_and_set(int *lock) {
  int temp;
  temp = *lock;
  *lock = 1;
  return temp;
}
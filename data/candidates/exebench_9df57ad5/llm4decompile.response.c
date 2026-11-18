void a_store(int *p, int x) {
  *p = x;
  LOCK();
  UNLOCK();
}
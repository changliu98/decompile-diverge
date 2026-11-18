void a_store(int *p, int x) {
  int y;
  *p = x;
  __atomic_thread_fence(&y, 0);
  return;
}
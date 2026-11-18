void sync_unlock(int *lock) {
  int l;
  l = *lock;
  l = 0;
  *lock = l;
}
void UNLOCK(int *lock) {
  if (__sync_val_compare_and_swap(lock, -1, 2) == 2) {
    __sync_lock_release(lock, 0);
    syscall(202, lock, 1);
  }
}
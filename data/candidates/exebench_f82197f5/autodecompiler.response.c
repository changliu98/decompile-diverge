void UNLOCK(int *m) {
 int old, new;
 old = __sync_fetch_and_add(m, -1);
 if (old-1 != 0) goto cont;
cont:
 new = old - 1;
 if (new == 0) {
  old = __sync_lock_test_and_set(m, 0);
  syscall(202, m, ((unsigned long)(1) << 0));
 }
}
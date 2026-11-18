void futex_unblock(struct futex *f)
{
  int v = __sync_sub_and_fetch(&f->count, -1);
  if (v == 2) {
    __sync_lock_test_and_set(&f->count, 0);
    syscall(202, &f->count, 1);
  }
}
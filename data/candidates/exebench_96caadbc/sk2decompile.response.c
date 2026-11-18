long ihk_atomic_add_long_return(long inc, long *target) {
  long old;
  long ret;
  old = __sync_fetch_and_add((long *)target, inc);
  ret = old + inc;
  return ret;
}
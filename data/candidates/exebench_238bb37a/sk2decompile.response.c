long incr(long *p, long n) {
  long old;
  old = *p;
  *p += n;
  return old;
}
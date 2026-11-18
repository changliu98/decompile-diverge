int nrt_testing_atomic_inc(int *p) {
  int v;
  v = *p;
  v++;
  *p = v;
  return v;
}
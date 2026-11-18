void load_and_store(unsigned long *p, unsigned long v) {
  unsigned long l;
  l = *p;
  l += v;
  *p = l;
}
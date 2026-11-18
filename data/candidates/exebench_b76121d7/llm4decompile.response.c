void atomic_or_long(AtomicLong *v, long delta) {
  v->value |= delta;
}
static inline int mt76_incr(int idx, int size) {
  idx++;
  idx &= (size - 1);
  return idx;
}
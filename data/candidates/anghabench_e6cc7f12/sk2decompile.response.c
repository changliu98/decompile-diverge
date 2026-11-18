static inline int aligned(int size) {
  size = (size + 63) >> 6;
  size <<= 6;
  return size;
}
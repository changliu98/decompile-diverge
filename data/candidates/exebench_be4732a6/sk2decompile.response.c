static inline void bitfield_set(unsigned long *field, int bit) {
  unsigned long word = bit / (sizeof(unsigned long) * 8);
  unsigned long offset = bit % (sizeof(unsigned long) * 8);
  field[word] |= (1UL << offset);
}
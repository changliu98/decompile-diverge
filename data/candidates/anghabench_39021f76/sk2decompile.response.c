static inline int all_bits_clear(unsigned int val, unsigned int mask) {
  if ((val & mask) == 0)
    return 1;
  else
    return 0;
}
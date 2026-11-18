static inline void set_bit(unsigned char *bitmap, unsigned int bit) {
  unsigned int byte = bit / 8;
  unsigned int offset = 7 - (bit % 8);
  bitmap[byte] |= 1 << offset;
}
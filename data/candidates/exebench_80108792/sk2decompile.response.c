void bitmap_free(unsigned int *bitmap, int bit) {
  int index = bit / 32;
  int offset = bit % 32;
  bitmap[index] &= ~(1 << (31 - offset));
}
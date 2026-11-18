void clearbit32(unsigned int *bits, int bit) {
   unsigned int mask = ~(0x80000000 >> (bit % 32));
   unsigned int *ptr = bits + (bit / 32);
   *ptr &= mask;
}
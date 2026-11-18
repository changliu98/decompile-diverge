void bitmap_free(unsigned int *bitmap, int bit) {
    int index = bit / 32;
    unsigned int mask = ~(0x80000000 >> (bit % 32));
    bitmap[index] &= mask;
}
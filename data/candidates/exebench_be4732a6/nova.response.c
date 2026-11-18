void bitfield_set(unsigned long *bitmap, int pos) {
        bitmap[pos / 8] |= (1UL << (pos % 8));
}
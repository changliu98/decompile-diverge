void set_bit(unsigned char *bitmap, unsigned long long bit_index) {
    unsigned char bit_position = bit_index & 0x7;
    unsigned char mask = 1 << (7 - bit_position);
    unsigned long long byte_index = bit_index >> 3;
    bitmap[byte_index] |= mask;
}
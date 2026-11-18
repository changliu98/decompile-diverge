void wordstore(unsigned char *ptr, int value) {
    ptr[0] = value & 0xFF;
    ptr[1] = (value >> 8) & 0xFF;
}
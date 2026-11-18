void swap_long(unsigned char *p) {
    unsigned char temp;
    unsigned char *ptr = p;

    // Swap byte 0 and byte 3
    temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;

    // Swap byte 1 and byte 2
    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}
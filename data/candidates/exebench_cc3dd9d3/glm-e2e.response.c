void AssignBit(unsigned long *arr, int bit_index, int value) {
    unsigned long mask = 1UL << (bit_index & 0x3F);
    
    if (value != 0) {
        arr[bit_index >> 6] |= mask;
    } else {
        arr[bit_index >> 6] &= ~mask;
    }
}
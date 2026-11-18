void BinaryFiles__swap_bytes32(unsigned int *ptr) {
    unsigned int val = *ptr;
    unsigned int swapped_val = ((val & 0x000000FF) << 24) |
                               ((val & 0x0000FF00) << 8) |
                               ((val & 0x00FF0000) >> 8) |
                               ((val & 0xFF000000) >> 24);
    *ptr = swapped_val;
}
void bit_write_UMC(void *out, uint64_t val) {
    uint8_t bytes[5];
    uint64_t mask = 0x7f;
    int i = 4;
    int shift = 0;

    // First loop: split the 64-bit integer into 7-bit chunks
    // and set the high bit (0x80) for all 5 chunks.
    while (i >= 0) {
        bytes[i] = (uint8_t)((val & mask) >> shift) | 0x80;
        mask <<= 7;
        i--;
        shift += 7;
    }

    i = 0;

    // Second loop: find the first byte that has any of the lower 7 bits set.
    while (i < 4) {
        if ((bytes[i] & 0x7f) != 0) {
            break;
        }
        i++;
    }

    // If the current byte has the 6th bit (0x40) set, step back one byte.
    // This ensures we don't strip the continuation bit from a byte that 
    // actually contains meaningful data in its 6th bit.
    if ((bytes[i] & 0x40) != 0) {
        i--;
    }

    // Clear the high bit (0x80) of the starting byte to mark the beginning of the sequence.
    bytes[i] &= 0x7f;

    // Third loop: write the bytes from the starting index down to 0.
    for (int j = 4; j >= i; j--) {
        bit_write_RC(out, bytes[j]);
    }
}
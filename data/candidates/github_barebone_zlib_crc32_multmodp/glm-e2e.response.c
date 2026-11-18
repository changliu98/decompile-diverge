uint64_t multmodp(uint64_t a, uint64_t b) {
    uint64_t mask = 0x80000000;
    uint64_t result = 0;

    while (1) {
        // If the current bit of 'a' is set, XOR 'b' into the result
        if ((a & mask) != 0) {
            result ^= b;
        }

        // If the remaining bits of 'a' are all zero, we are done
        if ((a & (mask - 1)) == 0) {
            break;
        }

        // Shift the mask to the right to process the next bit
        mask >>= 1;

        // Multiply 'b' by x (shift right by 1)
        // If the lowest bit was 1, subtract the polynomial P(x) 
        // (which in GF(2) is equivalent to XORing with 0xEDB88320)
        if ((b & 1) != 0) {
            b = (b >> 1) ^ 0xedb88320;
        } else {
            b = b >> 1;
        }
    }

    return result;
}
uLong multmodp(uLong operand_a, uLong operand_b) {
    uLong product = 0;
    uLong bit_mask = 0x80000000;
    // Iterate through bits of 'a' from most significant to least significant.
    // 'm' tracks the current bit position being processed.
    // The loop continues as long as the current bit of 'a' is 0 or there are more bits to process.
    // In each iteration, if the current bit of 'a' is 1, XOR 'p' with 'b'.
    // 'b' is updated using a precomputed polynomial (CRC32 style) to handle modular arithmetic efficiently.
    while ((operand_a & bit_mask) == 0 || (product ^= operand_b, (operand_a & (bit_mask - 1)) != 0)) {
        bit_mask >>= 1;
        operand_b = (operand_b & 1) ? (operand_b >> 1 ^ 0xedb88320) : (operand_b >> 1);
    }
    return product;
}
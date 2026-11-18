uint gf32_mod(unsigned_long_long result, int degree)
{
    // Iterate from high_bit down to 31 (0x1f) to process bits above the 32-bit range
    for (int current_bit = degree; 0x1f < current_bit; current_bit--) {
        // Check if the j-th bit is set in r
        if ((1L << ((byte)current_bit & 0x3f) & result) != 0) {
            // XOR r with the irreducible polynomial 0x1edc6f41 shifted appropriately
            // This reduces the degree of the polynomial represented by r
            result = 0x1edc6f41L << ((byte)current_bit - 0x20 & 0x3f) ^ result;
        }
    }
    // Return the lower 32 bits of the result as a uint
    return (uint)result;
}
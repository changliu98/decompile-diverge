void unpackFloat(float f, int *exp, int *sig) {
    // Type-pun the float to a 32-bit integer to extract its bits
    uint32_t bits = *(uint32_t *)&f;
    
    // Extract the 8-bit exponent (bits 30-23), shift it down, and unbias it (subtract 127)
    *exp = (int)((bits & 0x7f800000) >> 23) - 127;
    
    // Extract the 23-bit mantissa (bits 22-0) and add the implicit leading 1
    *sig = (bits & 0x7fffff) + 0x800000;
    
    // If the sign bit (bit 31) is set, negate the significand
    if (bits & 0x80000000) {
        *sig = -*sig;
    }
}
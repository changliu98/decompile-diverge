unsigned char *emit_literal(unsigned char *op, const char *literal, int len, char allow_fast_path) {
    int n = len - 1;
    
    if (n < 60) {
        // Fit length in the tag byte
        *op++ = (char)((n << 2) | 0);
        
        if (allow_fast_path & 1) {
            if (len <= 16) {
                // Fast path for small literals using unaligned 64-bit copies
                unaligned_copy64(literal, op);
                unaligned_copy64(literal + 8, op + 8);
                return op + len;
            }
        }
    } else {
        // Multi-byte encoding for lengths >= 60
        unsigned char *tag_op = op;
        op++;
        
        int count = 0;
        while (n > 0) {
            *op++ = n & 0xff;
            n >>= 8;
            count++;
        }
        
        // Assertions to ensure the varint length is within expected bounds
        if (count < 1) {
            __assert_fail("count >= 1", "file", 0x247, "emit_literal");
        }
        if (count > 4) {
            __assert_fail("count <= 4", "file", 0x248, "emit_literal");
        }
        
        // Write the tag byte with the encoded length indicator
        *tag_op = (char)((count + 60 - 1) << 2 | 0);
    }
    
    // Fallback for larger literals or when fast path is disabled
    unaligned_copy64(literal, op);
    return op + len;
}
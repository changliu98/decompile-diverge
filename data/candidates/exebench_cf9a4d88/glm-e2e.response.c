int FABSQ(uint64_t *out, const uint64_t *in) {
    // Mask out the sign bit of the first 64-bit chunk (lower 8 bytes)
    out[0] = in[0] & 0x7fffffffffffffffULL;
    
    // Copy the second 64-bit chunk (upper 8 bytes) unchanged
    out[1] = in[1];
    
    return 1;
}
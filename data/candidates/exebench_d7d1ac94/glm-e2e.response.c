int imul_dbl(int64_t *val) {
    int64_t a = val[0];
    int64_t b = val[1];
    int overflow = 0;
    
    // The compiler optimized the 128-bit multiplication and overflow check 
    // into a single `imul` instruction with `seto`.
    // In standard C, this behavior can be represented using __builtin_mul_overflow
    int64_t result_low;
    overflow = __builtin_mul_overflow(a, b, &result_low);
    
    val[0] = result_low;
    val[1] = b; // The high 64 bits of the result are discarded, original b is kept
    
    return overflow;
}
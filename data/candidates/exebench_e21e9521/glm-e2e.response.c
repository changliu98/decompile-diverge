float avg12(const float *a, const float *b, uint64_t n) {
    float sum = 0.0f;
    for (uint64_t i = 0; i < n; i++) {
        sum += a[i] * b[i] * a[i];
    }
    
    // The following logic accurately reflects the assembly's 
    // handling of integer-to-float conversion for large 64-bit values.
    float count;
    if (n < 0) {
        // This branch is technically unreachable since n is unsigned,
        // but it corresponds to the `js` instruction in the assembly.
        count = (float)((n >> 1) | (n & 1)) * 2.0f;
    } else {
        count = (float)n;
    }
    
    return sum / count;
}
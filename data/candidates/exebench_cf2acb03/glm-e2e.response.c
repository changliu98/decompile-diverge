float MP_Rand(int64_t *state) {
    // Step 1: XOR the state with a magic number
    *state ^= 0x75bd924;
    
    // Step 2: Compute the new state using a Linear Congruential Generator (LCG)
    // This specific algorithm is a 64-bit implementation of the classic MINSTD generator.
    int64_t k = *state / 0x1f31d;
    *state = 0x41a7 * (*state - k * 0x1f31d) - 0xb14 * k;
    
    // Step 3: Ensure the state is non-negative
    if (*state < 0) {
        *state += 0x7fffffff;
    }
    
    // Step 4: Convert the integer state to a float in the range [0.0, 1.0)
    float result = (float)((double)*state * (1.0 / 2147483647.0));
    
    // Step 5: XOR the state with the magic number again before returning
    *state ^= 0x75bd924;
    
    return result;
}
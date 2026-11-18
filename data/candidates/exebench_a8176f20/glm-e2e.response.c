bool btcl_reg(unsigned int val, unsigned int bit, unsigned int *out) {
    unsigned int result = val;
    bool carry;
    
    // Inline assembly to perform the bit-test-and-complement (btc)
    // and capture the original bit state in the carry flag (CF)
    __asm__ (
        "btc %2, %1\n\t"
        "setb %0"
        : "=r" (carry), "+r" (result)
        : "r" (bit)
        : "cc"
    );
    
    *out = result;
    return carry;
}
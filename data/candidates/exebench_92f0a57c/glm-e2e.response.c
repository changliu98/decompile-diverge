double HTS_rnd(unsigned int *state) {
    // Update the internal state using a Linear Congruential Generator (LCG)
    // Note: The assembly uses 64-bit multiplication and addition, but only 
    // stores the lower 32 bits back into the state pointer.
    unsigned long long next = (unsigned long long)*state * 0x41c64e6dULL + 0x3039ULL;
    *state = (unsigned int)next;
    
    // Extract the upper 15 bits of the 32-bit state (bits 16-30)
    // Note: The assembly reads a 32-bit value at offset 0x2, which on a 
    // little-endian system corresponds to the upper 16 bits of the 32-bit state.
    // Masking it with 0x7fff extracts the top 15 bits.
    unsigned int val = *(unsigned int *)((char *)state + 2) & 0x7fff;
    
    // Convert to double and divide by 32768.0 (which is 1 << 15)
    return (double)val / 32768.0;
}
double HTS_rnd(unsigned_long *rng_state)
{
    // Update the random number generator state using a linear congruential generator algorithm
    *rng_state = *rng_state * 0x41c64e6d + 0x3039;
    
    // Extract the upper 15 bits of the new state to generate a pseudo-random value
    // Cast 'next' pointer to long, add 2 to access the upper 32 bits (assuming 64-bit unsigned_long)
    // Mask with 0x7fff to get the lower 15 bits of the upper half
    // Divide by a constant (DAT_00102008) to normalize the result to a double in [0, 1)
    return (double)((*(uint *)((long)rng_state + 2) & 0x7fff)) / DAT_00102008;
}
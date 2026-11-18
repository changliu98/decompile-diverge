float __cdecl MP_Rand(long *rand_seed)
{
    // 0x75BD924 is a 32-bit mask. Using unsigned 32-bit math prevents 
    // undefined behavior with signed overflow and matches CPU register operations.
    unsigned int seed = (unsigned int)*rand_seed ^ 0x75BD924u;

    // Park-Miller "Minimal Standard" PRNG constants:
    // a = 16807 (7^5), m = 2147483647 (2^31 - 1)
    // q = m / a = 127773, r = m % a = 2836
    // This specific block is Schrage's method for overflow-safe modulo arithmetic.
    unsigned int div = seed / 127773;
    unsigned int mod = seed % 127773;
    
    // In 32-bit unsigned arithmetic, the subtraction naturally wraps around 
    // correctly, so the explicit `if (seed < 0) seed += 0x7FFFFFFF` from the 
    // decompiler is no longer needed.
    seed = 16807 * mod - 2836 * div;

    // 4.656612875245797e-10 is exactly 1.0f / 2147483648.0f (1 / 2^31).
    // This normalizes the 31-bit positive integer (0 to 2147483647) 
    // to a floating-point range of [0.0, 1.0).
    float result = 4.656612875245797e-10f * (float)(int)seed;

    // Re-apply the XOR mask to the state before returning
    *rand_seed = (long)(seed ^ 0x75BD924u);
    
    return result;
}
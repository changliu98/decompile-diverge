void __cdecl shr(uint64_t *p, int n) 
{
    // Truncate the shift amount to 8 bits (signed char).
    // This preserves the original truncation behavior, even if it causes UB for large n.
    signed char shift = (signed char)n;

    // If the shift amount is >= 64, move the high 64 bits into the low 64 bits,
    // zero out the high bits, and reduce the remaining shift amount by 64.
    if ((unsigned int)n >= 0x40) 
    {
        shift = (signed char)(n - 64);
        p[0] = p[1];
        p[1] = 0ULL;
    }

    // Shift the low bits to the right, and fill the vacated high bits 
    // with the lower bits of the high 64-bit chunk.
    p[0] >>= shift;
    p[0] |= p[1] << (64 - shift);
    
    // Shift the high bits to the right.
    p[1] >>= shift;
}
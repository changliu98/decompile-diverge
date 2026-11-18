define EXP_SHIFT     23

int __cdecl denormal_addf1(unsigned int ix, unsigned int iy)
{
    int exp;          // 8-bit exponent
    int frac;         // 23-bit fraction (mantissa)
    unsigned int iya; // Shifted value of iy

    // If ix is a denormal (or zero), add iy directly to the integer representation.
    // This works because denormals have an exponent of 0, meaning their value 
    // is just their raw integer bits scaled by a constant factor.
    if (ix < HIDDEN_BIT)
        return iy + ix;

    // Extract the 8-bit exponent
    exp = (ix & EXP_MASK) >> EXP_SHIFT;

    // If the exponent is 0 (ix is denormal) or > 32, the shift below would be invalid.
    // (Note: The original decompiled code had a bug where exp=0 caused a negative shift.
    // This check safely handles exp=0 and exp > 32).
    if (exp - 1 < 0 || exp - 1 > 31)
        return ix;

    // Shift iy to align with the fraction part of ix
    iya = iy >> (exp - 1);
    
    // If iy shifted completely to zero, it has no effect on ix
    if (!iya)
        return ix;

    // Extract the fraction, add the implicit leading 1 (hidden bit), and add iy
    frac = (ix & FRAC_MASK | HIDDEN_BIT) + iya;

    // If the fraction overflowed the 24-bit mantissa limit
    if (frac >= (HIDDEN_BIT << 1)) 
    {
        frac >>= 1; // Shift right to fit
        ++exp;      // Increment exponent to compensate
    }

    // Reassemble the float: exponent + fraction (the hidden bit is naturally stripped out)
    return (exp << EXP_SHIFT) | (frac & FRAC_MASK);
}
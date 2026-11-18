int __cdecl ctsxs(unsigned int x, int scale, unsigned int *vscrp)
{
    // Extract the 8-bit exponent and 23-bit mantissa from the 32-bit float
    unsigned int exp = (x >> 23) & 0xFF;
    unsigned int mant = x & 0x7FFFFF;
    
    // If the input is NaN or Infinity, return 0
    if (exp > 255)
        return 0;

    // Calculate the new unbiased exponent (applying scale and removing the 127 bias)
    int new_exp = scale + exp - 127;

    // If the new exponent is negative, the value is too small, return 0
    if (new_exp < 0)
        return 0;

    // If the value fits within a 32-bit signed integer
    if (new_exp < 31)
    {
        // Add the implicit leading 1 to the mantissa, shift left by 7 to align it,
        // then shift right by (30 - new_exp) to apply the exponent.
        int result = (int)(((mant | 0x800000) << 7) >> (30 - new_exp));
        
        // If the sign bit is set, negate the result
        if (x & 0x80000000)
            return -result;
        else
            return result;
    }
    else
    {
        // Saturation / Overflow handling
        
        // If the value isn't exactly -2^31 (-2147483648.0), set the saturation flag
        if (((unsigned int)scale << 23) + x != 0xCF000000)
            *vscrp |= VSCR_SAT;

        // Return the maximum or minimum 32-bit signed integer based on the sign bit
        if (x & 0x80000000)
            return 0x80000000; // -2147483648
        else
            return 0x7FFFFFFF; //  2147483647
    }
}
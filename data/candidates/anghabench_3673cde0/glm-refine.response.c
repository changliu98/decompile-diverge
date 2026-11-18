float __cdecl modff(float x, float *iptr)
{
    union { float f; uint32_t i; } u;
    u.f = x;

    // Extract the exponent (8 bits, biased by 127)
    int e = (int)((u.i >> 23) & 0xFF) - 127;

    if (e < 23)
    {
        if (e >= 0)
        {
            // Check if there are any fractional bits set
            if ((u.i & (0x7FFFFF >> e)) != 0)
            {
                // Mask out the fractional bits to get the integer part
                u.i &= ~(0x7FFFFF >> e);
                *iptr = u.f;
                return x - u.f;
            }
            else
            {
                // x is already an integer
                *iptr = x;
                return 0.0f; // v5 logic replaced with explicit zero
            }
        }
        else
        {
            // |x| < 1.0. Integer part is signed zero.
            *iptr = (u.i & 0x80000000) ? -0.0f : 0.0f;
            return x;
        }
    }
    else
    {
        // |x| is very large (exponent >= 23) or infinity/NaN
        *iptr = x;
        
        // Check for NaN or Infinity (exponent == 255)
        if (((u.i >> 23) & 0xFF) == 255 && (u.i << 9) != 0)
        {
            return x; // Return x if it's NaN
        }
        else
        {
            return 0.0f; // v5 logic replaced with explicit zero
        }
    }
}
int __cdecl SCALE(long val, int mul, int div)
{
    long scaled_val = (long)mul * val;
    int rounding_factor = div / 2;

    // Standard integer division with rounding to the nearest whole number.
    // Positive numbers need the factor added, negative numbers need it subtracted.
    if (val >= 0)
        return (scaled_val + rounding_factor) / div;
    else
        return (scaled_val - rounding_factor) / div;
}
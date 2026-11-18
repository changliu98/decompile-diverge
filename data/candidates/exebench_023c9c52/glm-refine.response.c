int __cdecl i2s_sf_sclkdiv(int div, int *out)
{
    // Special cases for odd divisors 1 and 3
    if (div == 1)
    {
        *out |= 0x800000;
        return 0;
    }
    if (div == 3)
    {
        *out |= 0x900000;
        return 0;
    }

    // Reject all other odd divisors
    if (div % 2 != 0)
    {
        return -1;
    }

    // Reject divisors 18 and 20 (where div / 2 is 9 or 10)
    int half_div = div / 2;
    if (half_div == 9 || half_div == 10)
    {
        return -1;
    }

    // General case: map even divisors to the 20-bit register field
    // (div / 2 - 1) << 20 is equivalent to ((div / 2 - 1) * 0x100000)
    *out |= (half_div - 1) * 0x100000;
    return 0;
}
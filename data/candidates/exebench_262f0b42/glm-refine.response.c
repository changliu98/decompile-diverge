void __cdecl breakup(short *fcs_bit, unsigned __int16 usps_crc)
{
    // Initialize the 13-bit array to 0
    for (int i = 0; i < 13; ++i)
        fcs_bit[i] = 0;

    // Extract bits from most significant (bit 12) to least significant (bit 0)
    for (int i = 12; i >= 0; --i)
    {
        if (usps_crc >= (1u << i))
        {
            fcs_bit[i] = 1;
            usps_crc -= (1u << i);
        }
    }
}
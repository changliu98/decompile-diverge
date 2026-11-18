void __cdecl makeSinTable()
{
    int i;

    // 1. Create the second quadrant (256..511) by mirroring the first quadrant (255..0)
    for (i = 0; i < 256; ++i)
        fullsin_table[i + 256] = fullsin_table[255 - i];

    // 2. Create the third and fourth quadrants (512..1023) by inverting the sign 
    // (setting the most significant bit of the 16-bit integer)
    for (i = 0; i < 512; ++i)
        fullsin_table[i + 512] = fullsin_table[i] | 0x8000;

    // 3. Create a half-sine table for the first half (0..511)
    for (i = 0; i < 512; ++i)
        halfsin_table[i] = fullsin_table[i];

    // 4. Clamp the second half of the half-sine table to maximum amplitude (0x0FFF)
    for (i = 512; i < 1024; ++i)
        halfsin_table[i] = 0x0FFF;
}
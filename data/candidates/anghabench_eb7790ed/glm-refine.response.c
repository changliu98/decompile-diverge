unsigned int __cdecl _sw_hweight32(unsigned int w)
{
    // Step 1: Count bits in each 2-bit chunk
    // Equivalent to: w = w - ((w >> 1) & 0x55555555);
    unsigned int step1 = w - ((w >> 1) & 0x55555555);

    // Step 2: Count bits in each 4-bit chunk (nibble)
    // Equivalent to: w = (w & 0x33333333) + ((w >> 2) & 0x33333333);
    unsigned int step2 = (step1 & 0x33333333) + ((step1 >> 2) & 0x33333333);

    // Step 3: Count bits in each 8-bit chunk (byte)
    // Equivalent to: w = (w + (w >> 4)) & 0x0F0F0F0F;
    unsigned int step3 = (step2 + (step2 >> 4)) & 0x0F0F0F0F;

    // Step 4: Multiply by 0x01010101 to sum all bytes into the highest byte
    // Equivalent to: return (w * 0x01010101) >> 24;
    return (step3 * 0x01010101) >> 24;
}
uint32_t __cdecl par_msquares_argb(const uint8_t *pdata, int bpp)
{
    // Fast path: 32-bit pixels are typically BGRA in memory. 
    // This directly maps them to a 0xAARRGGBB format.
    if (bpp == 4)
        return pdata[2] | (pdata[1] << 8) | (pdata[0] << 16) | (pdata[3] << 24);

    // Fallback: pack bytes into an integer (Big-Endian order)
    uint32_t color = 0;
    for (int j = 0; j < bpp; ++j)
        color = (color << 8) | pdata[j];

    return color;
}
static uint32_t par_msquares_argb(par_byte const* pdata, int bpp)
{
    uint32_t color = 0;
    if (bpp == 4) {
        color |= pdata[2];
        color |= pdata[1] << 8;
        color |= pdata[0] << 16;
        color |= pdata[3] << 24;
        return color;
    }
    for (int j = 0; j < bpp; j++) {
        color <<= 8;
        color |= pdata[j];
    }
    return color;
}
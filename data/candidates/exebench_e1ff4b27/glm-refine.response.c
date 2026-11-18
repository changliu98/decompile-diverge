void __cdecl BMP_getGenBmp16Palette(const unsigned __int16 *genbmp16, unsigned __int16 *pal)
{
    const unsigned __int16 *src = genbmp16 + 2;
    for (unsigned __int16 i = 16; i--; )
    {
        *pal++ = *src++;
    }
}
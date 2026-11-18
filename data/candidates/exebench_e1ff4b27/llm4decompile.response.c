void BMP_getGenBmp16Palette(unsigned char *genbmp16, unsigned short *pal)
{
    unsigned short i;

    for (i = 0; i < 16; i++)
    {
        pal[i] = ((unsigned short)(genbmp16[2 * i + 1] << 8) | genbmp16[2 * i]);
    }
}
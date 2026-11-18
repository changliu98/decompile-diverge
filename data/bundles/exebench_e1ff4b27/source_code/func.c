
void BMP_getGenBmp16Palette(const unsigned short *genbmp16, unsigned short *pal)
{
    unsigned short i;
    const unsigned short *src;
    unsigned short *dst;

    src = (&((genbmp16)[2]));
    dst = pal;
    i = 16;
    while(i--) *dst++ = *src++;
}

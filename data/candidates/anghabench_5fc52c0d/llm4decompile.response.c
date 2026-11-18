void sjis2jis(unsigned char *p1, unsigned char *p2)
{
    unsigned char adjust = *p2 < 159;
    unsigned char row = *p1 < 160 ? 112 : 119;
    unsigned char cell = adjust ? (*p2 < 128 ? 126 : 127) : 126;

    *p1 -= row;
    *p2 -= cell;

    *p1 <<= 1;
    if (adjust) {
        *p1 -= *p2 & 1;
    }
}
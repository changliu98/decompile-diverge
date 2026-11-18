static void
_sjis_shift(unsigned char *ch1, unsigned char *ch2)
{
    int ch1c, ch2c;
    int rowOffset, cellOffset, adjust;

    ch1c = *ch1;
    ch2c = *ch2;

    adjust = ((ch2c >= 0xA0) ? 0 : 1);
    rowOffset = ((ch1c < 0xA0) ? 0x70 : 0xB0);

    if (adjust) {
 cellOffset = ((ch2c >= 0x80) ? 0x20 : 0x1F);
    } else {
 cellOffset = 0x7E;
    }

    *ch1 = ((ch1c - rowOffset) << 1) - adjust;
    *ch2 -= cellOffset;
}
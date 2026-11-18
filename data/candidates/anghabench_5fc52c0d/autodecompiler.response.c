static void
sjis2jis(unsigned char *c1, unsigned char *c2)
{
    int row, shift, cell;
    unsigned char c1_1, c2_1;

    c1_1 = *c1;
    c2_1 = *c2;

    shift = (c2_1 >= 0xa0) ? 0 : 1;
    row = (c1_1 >= 0xa0) ? 0xb0 : 0x70;
    if (shift)
 cell = (c2_1 >= 0x80) ? 0x20 : 0x1f;
    else
 cell = 0x7e;

    *c1 = ((c1_1 - row) << 1) - shift;
    *c2 = c2_1 - cell;
}
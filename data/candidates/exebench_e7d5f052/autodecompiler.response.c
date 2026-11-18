void SJIStoJIS(unsigned char *row, unsigned char *col)
{
    int adjust;
    int rowOffset;
    int cellOffset;
    int jisRow;
    int jisCol;

    unsigned char rowByte = *row;
    unsigned char colByte = *col;

    adjust = ((colByte >= 0xa0) ? 0 : 1);
    rowOffset = ((rowByte >= 0xa0) ? 0xb0 : 0x70);

    if (adjust) {
        jisCol = ((colByte >= 0x80) ? 0x20 : 0x1f) + 1;
    } else {
        jisCol = 0x7e;
    }

    cellOffset = jisCol;

    *row = ((rowByte - rowOffset) << 1) - adjust;
    *col = *col - cellOffset;
}
static void
_jis_shift (int *pRow, int *pCol)
{
    int rowOffset, cellOffset;
    unsigned char c1 = (unsigned char) *pRow;
    unsigned char c2 = (unsigned char) *pCol;

    rowOffset = ((c1 < 96) ? 112 : 176);
    if (c1 % 2)
 cellOffset = ((c2 < 96) ? 31 : 32);
    else
 cellOffset = 126;

    *pRow = (int) (rowOffset + ((c1 + 1) >> 1));
    *pCol += cellOffset;
}
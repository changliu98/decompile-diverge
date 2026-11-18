static int
byte_col_big5(int c)
{
    int u;

    if (c >= 0x40 && c <= 0x7e)
 u = c - 0x40;
    else if (c >= 0xa1 && c <= 0xff)
 u = c - 0x62;
    else
 u = -1;
    return u;
}
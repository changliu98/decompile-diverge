define GBK1_BYTE_MAX 255

int __cdecl byte_row_gbk1(int byte)
{
    if (byte < GBK1_BYTE_MIN || byte >= GBK1_BYTE_MAX)
        return -1;

    return byte - GBK1_BYTE_MIN;
}
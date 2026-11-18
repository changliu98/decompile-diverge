int byte_row_gbk1(int byte)
{
    if (byte >= 129 && byte <= 254)
        return byte - 129;
    else
        return -1;
}
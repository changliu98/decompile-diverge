void find_ibm(int c1, int c2, int *outc1, int *outc2)
{
    int c;

    c = (c1 - 0xa1) * 157 + c2 - 0x40;
    if (c2 > 0x7e)
        c++;
    if (c > 408)
        c += 0x5d;
    c %= 188;
    c += 0x40;
    if (c > 0x7e)
        c++;
    *outc1 = c / 188 + 0x89;
    *outc2 = c % 188 + 0x40;
}
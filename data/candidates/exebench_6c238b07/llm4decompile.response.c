int genx(unsigned char *dst, unsigned char *field)
{
    short index[256];
    int i, flag = 0;

    for (i = 0; i < 256; i++)
        index[i] = -1;
    for (i = 0; i < 256; i++) {
        if (index[field[i]] == -1)
            index[field[i]] = i;
        else
            flag = 1;
    }
    for (i = 0; i < 256; i++)
        dst[i] = index[i];
    if (flag)
        return -1;
    return 0;
}
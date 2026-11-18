static void func0(short *src, short *dst)
{
    int x, y;
    short tmp[4][4];

    for (y = 0; y < 5; y++) {
        for (x = 0; x < 5; x++) {
            tmp[x][y] = src[0] + src[1] + src[4] + src[5];
            src++;
        }
        src += 2;
    }

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            tmp[x][y] -= src[0] + src[1] + src[4] + src[5];
            dst[x] = (tmp[x][y] + 4) >> 3;
            src++;
        }
        src += 2;
        dst += 4;
    }
}
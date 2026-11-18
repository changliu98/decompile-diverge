static void idct_row(int *blk, int *out)
{
    int x0 = blk[0];
    int x1 = blk[8];
    int x2 = blk[16];
    int x3 = blk[24];
    int x4 = blk[32];
    int x5 = blk[40];
    int x6 = blk[48];
    int x7 = blk[56];

    int x0p7 = x0 + x7;
    int x1p6 = x1 + x6;
    int x2p5 = x2 + x5;
    int x3p4 = x3 + x4;

    int x0n7 = x0 - x7;
    int x1n6 = x1 - x6;
    int x2n5 = x2 - x5;
    int x3n4 = x3 - x4;

    int x0p7n3n4 = x0p7 - x3p4;
    int x1p6n2n5 = x1p6 - x2p5;

    int ob0 = (x0p7 + x1p6 + x2p5 + x3p4) * 91;
    int ob4 = (x0p7 - x1p6 - x2p5 + x3p4) * 91;

    int ob2 = x0p7n3n4 * 118 + x1p6n2n5 * 49;
    int ob6 = x0p7n3n4 * 49 - x1p6n2n5 * 118;

    int ob1 = x0n7 * 126 + x1n6 * 106 + x2n5 * 71 + x3n4 * 25;
    int ob3 = x0n7 * 106 - x1n6 * 25 - x2n5 * 126 - x3n4 * 71;
    int ob5 = x0n7 * 71 - x1n6 * 126 + x2n5 * 25 + x3n4 * 106;
    int ob7 = x0n7 * 25 - x1n6 * 71 + x2n5 * 106 - x3n4 * 126;

    out[0] = (ob0 + 32768) >> 16;
    out[8] = (ob1 + 32768) >> 16;
    out[16] = (ob2 + 32768) >> 16;
    out[24] = (ob3 + 32768) >> 16;
    out[32] = (ob4 + 32768) >> 16;
    out[40] = (ob5 + 32768) >> 16;
    out[48] = (ob6 + 32768) >> 16;
    out[56] = (ob7 + 32768) >> 16;
}
void njRowIDCT(int *blk) {
    int x0, x1, x2, x3, x4, x5, x6, x7, x8;
    int s0, s1, s2, s3, s4, s5, s6, s7;

    x1 = blk[4] << 11;
    x2 = blk[6];
    x3 = blk[2];
    x4 = blk[1];
    x5 = blk[7];
    x6 = blk[5];
    x7 = blk[3];

    // Check if all AC coefficients are zero
    if (!(x1 | x2 | x3 | x4 | x5 | x6 | x7)) {
        x0 = blk[0] << 3;
        blk[0] = x0;
        blk[1] = x0;
        blk[2] = x0;
        blk[3] = x0;
        blk[4] = x0;
        blk[5] = x0;
        blk[6] = x0;
        blk[7] = x0;
        return;
    }

    x0 = (blk[0] << 11) + 128;

    // Stage 1
    x8 = (x4 + x5) * 0x235;
    x4 = x8 + x4 * 0x8E4;
    x5 = x8 - x5 * 0xD4E;

    x8 = (x6 + x7) * 0x968;
    x6 = x8 - x6 * 0x31F;
    x7 = x8 - x7 * 0xFB1;

    // Stage 2
    x8 = x0 + x1;
    x0 = x0 - x1;
    x1 = (x3 + x2) * 0x454;
    x2 = x1 - x2 * 0xEC8;
    x3 = x1 + x3 * 0x620;

    x1 = x4 + x6;
    x4 = x4 - x6;
    x6 = x5 + x7;
    x5 = x5 - x7;

    x7 = x8 + x3;
    x8 = x8 - x3;
    x3 = x0 + x2;
    x0 = x0 - x2;

    x2 = (x4 + x5) * 0xB5 + 128 >> 8;
    x4 = (x4 - x5) * 0xB5 + 128 >> 8;

    // Stage 3: Final outputs
    blk[0] = (x7 + x1) >> 8;
    blk[1] = (x3 + x2) >> 8;
    blk[2] = (x0 + x4) >> 8;
    blk[3] = (x8 - x6) >> 8;
    blk[4] = (x8 + x6) >> 8;
    blk[5] = (x0 - x4) >> 8;
    blk[6] = (x3 - x2) >> 8;
    blk[7] = (x7 - x1) >> 8;
}
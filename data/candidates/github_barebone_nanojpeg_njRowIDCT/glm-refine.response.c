void __cdecl njRowIDCT(int *blk)
{
    int x0, x1, x2, x3, x4, x5, x6, x7, x8;

    // Load coefficients and scale
    x1 = blk[4] << 11;
    x2 = blk[6];
    x3 = blk[2];
    x4 = blk[1];
    x5 = blk[7];
    x6 = blk[5];
    x7 = blk[3];

    // Check if AC coefficients are all zero
    if (x7 | x6 | x5 | x4 | x3 | x2 | x1)
    {
        x0 = (*blk << 11) + 128;

        // Stage 1
        x8 = 565 * (x5 + x4);
        x4 = 2276 * x4 + x8;
        x5 = x8 - 3406 * x5;

        x8 = 2408 * (x7 + x6);
        x6 = x8 - 799 * x6;
        x7 = x8 - 4017 * x7;

        x8 = x1 + x0;
        x0 = x0 - x1;

        x1 = 1108 * (x2 + x3);
        x2 = x1 - 3784 * x2;
        x3 = 1568 * x3 + x1;

        // Stage 2
        x1 = x6 + x4;
        x4 = x4 - x6;
        x6 = x7 + x5;
        x5 = x5 - x7;

        x7 = x3 + x8;
        x8 = x8 - x3;
        x3 = x2 + x0;
        x0 = x0 - x2;

        // Stage 3
        x2 = (181 * (x5 + x4) + 128) >> 8;
        x4 = (181 * (x4 - x5) + 128) >> 8;

        // Final outputs
        *blk   = (x1 + x7) >> 8;
        blk[1] = (x2 + x3) >> 8;
        blk[2] = (x4 + x0) >> 8;
        blk[3] = (x6 + x8) >> 8;
        blk[4] = (x8 - x6) >> 8;
        blk[5] = (x0 - x4) >> 8;
        blk[6] = (x3 - x2) >> 8;
        blk[7] = (x7 - x1) >> 8;
    }
    else
    {
        // Fast path: DC coefficient only
        x0 = 8 * *blk;
        blk[7] = x0;
        blk[6] = x0;
        blk[5] = x0;
        blk[4] = x0;
        blk[3] = x0;
        blk[2] = x0;
        blk[1] = x0;
        *blk   = x0;
    }
}
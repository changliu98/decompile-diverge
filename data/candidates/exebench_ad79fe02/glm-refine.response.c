int __cdecl mpeg3video_idctcol(short *blk)
{
    int x0, x1, x2, x3, x4, x5, x6, x7, x8;
    int x0a, x1a, x2a, x3a, x4a, x5a, x6a, x7a;
    int x0b, x1b, x2b, x3b, x4b, x5b, x6b, x7b, x8b, x8c;

    // Load column elements (stride of 8 elements per row)
    x1 = blk[32] << 8;
    x2 = blk[48];
    x3 = blk[16];
    x4 = blk[8];
    x5 = blk[56];
    x6 = blk[40];
    x7 = blk[24];

    // Check if all AC coefficients are zero
    if (x7 | x6 | x5 | x4 | x3 | x2 | x1)
    {
        x0 = (*blk << 8) + 0x2000;

        // Stage 1: Odd half
        x8 = 565 * (x5 + x4) + 4;
        x4a = (2276 * x4 + x8) >> 3;
        x5a = (x8 - 3406 * x5) >> 3;

        x8 = 2408 * (x7 + x6) + 4;
        x6a = (x8 - 799 * x6) >> 3;
        x7a = (x8 - 4017 * x7) >> 3;

        // Stage 1: Even half
        x8b = x1 + x0;
        x0a = x0 - x1;

        x1a = 1108 * (x2 + x3) + 4;
        x2a = (x1a - 3784 * x2) >> 3;
        x3a = (1568 * x3 + x1a) >> 3;

        // Stage 2
        x1b = x6a + x4a;
        x4b = x4a - x6a;
        x6b = x7a + x5a;
        x5b = x5a - x7a;

        x7b = x3a + x8b;
        x8c = x8b - x3a;
        x3b = x2a + x0a;
        x0b = x0a - x2a;

        // Stage 3
        x2b = (181 * (x5b + x4b) + 128) >> 8;
        x4c = (181 * (x4b - x5b) + 128) >> 8;

        // Stage 4: Store scaled and shifted results
        *blk      = (x1b + x7b) >> 14;
        blk[8]    = (x2b + x3b) >> 14;
        blk[16]   = (x4c + x0b) >> 14;
        blk[24]   = (x6b + x8c) >> 14;
        blk[32]   = (x8c - x6b) >> 14;
        blk[40]   = (x0b - x4c) >> 14;
        blk[48]   = (x3b - x2b) >> 14;
        blk[56]   = (x7b - x1b) >> 14;

        return 1;
    }
    else
    {
        // DC-only path
        short v2 = (*blk + 32) >> 6;
        
        blk[56] = v2;
        blk[48] = v2;
        blk[40] = v2;
        blk[32] = v2;
        blk[24] = v2;
        blk[16] = v2;
        blk[8]  = v2;
        *blk    = v2;

        return 0;
    }
}
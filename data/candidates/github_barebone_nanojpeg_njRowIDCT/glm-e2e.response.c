void njRowIDCT(int32_t *block) {
    int32_t x0 = block[0];
    int32_t x1 = block[1];
    int32_t x2 = block[2];
    int32_t x3 = block[3];
    int32_t x4 = block[4];
    int32_t x5 = block[5];
    int32_t x6 = block[6];
    int32_t x7 = block[7];

    // Fast path: if all AC coefficients are zero
    if (!((x4 << 11) | x5 | x6 | x7 | x1 | x2 | x3)) {
        x0 <<= 3;
        block[0] = block[1] = block[2] = block[3] = 
        block[4] = block[5] = block[6] = block[7] = x0;
        return;
    }

    int32_t t0 = (x0 << 11) + 128;
    int32_t t1 = x0 << 11;
    
    // First stage
    int32_t s1 = (x2 + x3) * 0x235;
    x2 = s1 + x2 * 0x8e4;
    x3 = s1 - x3 * 0xd4e;

    int32_t s2 = (x6 + x7) * 0x968;
    x6 = s2 - x6 * 0x31f;
    x7 = s2 - x7 * 0xfb1;

    int32_t s3 = (x1 + x4) * 0x454;
    x1 = s3 + x1 * 0x620;
    x4 = s3 - x4 * 0xec8;

    // Second stage
    int32_t u0 = t0 + t1;
    t0 -= t1;

    int32_t u1 = x2 + x6;
    x2 -= x6;

    int32_t u2 = x3 + x7;
    x3 -= x7;

    int32_t u3 = x1 + x5;
    x1 -= x5;

    int32_t u4 = u0 + x1;
    u0 -= x1;

    int32_t u5 = t0 + x4;
    t0 -= x4;

    int32_t u6 = u1 + u2;
    u1 -= u2;

    int32_t u7 = u3 + s3; // s3 is the original x1+x4 scaled value
    u3 -= s3;

    // Third stage
    x4 = ((x2 + x3) * 0xb5 + 128) >> 8;
    x2 = ((x2 - x3) * 0xb5 + 128) >> 8;

    // Final outputs
    block[0] = (u4 + u6) >> 8;
    block[1] = (u7 + x4) >> 8;
    block[2] = (u5 + x2) >> 8;
    block[3] = (t0 + x3) >> 8;
    block[4] = (t0 - x3) >> 8;
    block[5] = (u5 - x2) >> 8;
    block[6] = (u7 - x4) >> 8;
    block[7] = (u4 - u6) >> 8;
}
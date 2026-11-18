int mpeg3video_idctcol(int16_t *block) {
    int32_t v0, v1, v2, v3, v4, v5, v6, v7;
    int32_t tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    int32_t val;
    int16_t result;

    // Load the 8 elements from the column (stride is 16 bytes)
    v0 = block[0];
    v1 = block[8];
    v2 = block[16];
    v3 = block[24];
    v4 = block[32];
    v5 = block[40];
    v6 = block[48];
    v7 = block[56];

    // Check if all AC coefficients are zero (DC-only fast path)
    if (((v4 << 8) | v6 | v2 | v1 | v7 | v5 | v3) == 0) {
        result = (int16_t)((v0 + 32) >> 6);
        block[0]  = result;
        block[8]  = result;
        block[16] = result;
        block[24] = result;
        block[32] = result;
        block[40] = result;
        block[48] = result;
        block[56] = result;
        return 0;
    }

    // Standard IDCT path
    v0 = (v0 << 8) + 8192; // 0x2000

    // Even part
    tmp = v4 + v6;
    tmp = (tmp * 565 + 4) >> 3; // 0x235
    v4 = (tmp + v4 * 2276) >> 3; // 0x8e4
    v6 = (tmp - v6 * 3406) >> 3; // 0xd4e

    tmp = v5 + v3;
    tmp = (tmp * 2408 + 4) >> 3; // 0x968
    v5 = (tmp - v5 * 799) >> 3;  // 0x31f
    v3 = (tmp - v3 * 4017) >> 3; // 0xfb1

    tmp = v0 + v4;
    v4 = v0 - v4;

    tmp1 = v2 + v6;
    tmp1 = (tmp1 * 1108 + 4) >> 3; // 0x454
    v6 = (tmp1 - v6 * 3784) >> 3;  // 0xec8
    v2 = (tmp1 + v2 * 1568) >> 3;  // 0x620

    tmp1 = v4 + v5;
    v5 = v4 - v5;

    tmp2 = v6 + v3;
    v3 = v6 - v3;

    tmp3 = tmp + v2;
    v2 = tmp - v2;

    tmp4 = v4 + v7;
    v7 = v4 - v7;

    tmp5 = v2 + v5;
    v5 = v2 - v5;

    tmp6 = (v5 + v7) * 181 + 128; // 0xb5
    v5 = tmp6 >> 8;
    tmp7 = (v5 - v7) * 181 + 128;
    v7 = tmp7 >> 8;

    // Odd part
    tmp8 = tmp3 + tmp2;
    tmp2 = tmp3 - tmp2;

    tmp9 = tmp4 + v3;
    v3 = tmp4 - v3;

    tmp10 = tmp + v6;
    v6 = tmp - v6;

    tmp11 = v4 + v5;
    v5 = v4 - v5;

    tmp12 = tmp2 + v7;
    v7 = tmp2 - v7;

    // Store results back to the block (shifted right by 14 bits)
    block[0]  = (int16_t)((tmp8 + tmp9) >> 14);
    block[8]  = (int16_t)((tmp10 + tmp11) >> 14);
    block[16] = (int16_t)((v4 + v5) >> 14);
    block[24] = (int16_t)((tmp3 + v3) >> 14);
    block[32] = (int16_t)((tmp3 - v3) >> 14);
    block[40] = (int16_t)((v4 - v5) >> 14);
    block[48] = (int16_t)((tmp10 - tmp11) >> 14);
    block[56] = (int16_t)((tmp8 - tmp9) >> 14);

    return 1;
}
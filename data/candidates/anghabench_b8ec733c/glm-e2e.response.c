void vc1_inv_trans_8x8_c(int16_t *block) {
    int16_t temp[64];
    int i;

    // 1st pass: horizontal 1D inverse transform
    for (i = 0; i < 8; i++) {
        int32_t t0 = (block[0] + block[4]) * 12 + 4;
        int32_t t1 = (block[0] - block[4]) * 12 + 4;
        int32_t t2 = block[2] * 16 + block[6] * 6;
        int32_t t3 = block[2] * 6  - block[6] * 16;

        int32_t s0 = t0 + t2;
        int32_t s1 = t1 + t3;
        int32_t s2 = t1 - t3;
        int32_t s3 = t0 - t2;

        int32_t u0 = block[1] * 16 + block[3] * 15 + block[5] * 9 + block[7] * 4;
        int32_t u1 = block[1] * 15 - block[3] * 4  - block[5] * 16 - block[7] * 9;
        int32_t u2 = block[1] * 9  - block[3] * 16 + block[5] * 4  + block[7] * 15;
        int32_t u3 = block[1] * 4  - block[3] * 9  + block[5] * 15 - block[7] * 16;

        temp[0] = (s0 + u0) >> 3;
        temp[1] = (s1 + u1) >> 3;
        temp[2] = (s2 + u2) >> 3;
        temp[3] = (s3 + u3) >> 3;
        temp[4] = (s3 - u3) >> 3;
        temp[5] = (s2 - u2) >> 3;
        temp[6] = (s1 - u1) >> 3;
        temp[7] = (s0 - u0) >> 3;

        block += 8;
    }

    // Reset pointers for the 2nd pass
    int16_t *src = temp;
    int16_t *dst = block - 64; // Point back to the original block start

    // 2nd pass: vertical 1D inverse transform
    for (i = 0; i < 8; i++) {
        int32_t t0 = (src[0] + src[8]) * 12 + 64;
        int32_t t1 = (src[0] - src[8]) * 12 + 64;
        int32_t t2 = src[2] * 16 + src[8*6] * 6;
        int32_t t3 = src[2] * 6  - src[8*6] * 16;

        int32_t s0 = t0 + t2;
        int32_t s1 = t1 + t3;
        int32_t s2 = t1 - t3;
        int32_t s3 = t0 - t2;

        int32_t u0 = src[1] * 16 + src[3] * 15 + src[5] * 9 + src[7] * 4;
        int32_t u1 = src[1] * 15 - src[3] * 4  - src[5] * 16 - src[7] * 9;
        int32_t u2 = src[1] * 9  - src[3] * 16 + src[5] * 4  + src[7] * 15;
        int32_t u3 = src[1] * 4  - src[3] * 9  + src[5] * 15 - src[7] * 16;

        dst[8*0] = (s0 + u0) >> 7;
        dst[8*1] = (s1 + u1) >> 7;
        dst[8*2] = (s2 + u2) >> 7;
        dst[8*3] = (s3 + u3) >> 7;
        dst[8*4] = ((s3 - u3) + 1) >> 7;
        dst[8*5] = ((s2 - u2) + 1) >> 7;
        dst[8*6] = ((s1 - u1) + 1) >> 7;
        dst[8*7] = ((s0 - u0) + 1) >> 7;

        src++;
        dst++;
    }
}
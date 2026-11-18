void plm_video_idct(int32_t *block) {
    int i;
    int v0, v1, v2, v3, v4, v5, v6, v7, v8;
    int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

    // 1D IDCT on Rows
    for (i = 0; i < 8; i++) {
        v0 = block[i + 8];
        v1 = block[i + 16] + block[i + 48];
        v2 = block[i + 40] - block[i + 24];
        v3 = block[i + 8] + block[i + 56];
        v4 = block[i + 24] + block[i + 40];
        v5 = block[i + 8] - block[i + 56];
        v6 = v3 + v4;
        v7 = block[i];

        t0 = (v5 * 0x1d9 - v2 * 0xc4 + 0x80) >> 8 - v6;
        t1 = t0 - ((v3 - v4) * 0x16a + 0x80) >> 8;
        t2 = v7 - v0;
        t3 = ((block[i + 16] - block[i + 48]) * 0x16a + 0x80) >> 8 - v1;
        t4 = v7 + v0;
        t5 = t2 + t3;
        t6 = t4 + v1;
        t7 = t2 - t3;
        t8 = t4 - v1;
        t9 = (-t1 + v2 * 0x1d9 + v5 * 0xc4 + 0x80) >> 8;

        block[i]      = v6 + t6;
        block[i + 8]  = t0 + t5;
        block[i + 16] = t7 - t1;
        block[i + 24] = t8 - t9;
        block[i + 32] = t8 + t9;
        block[i + 40] = t1 + t7;
        block[i + 48] = t5 - t0;
        block[i + 56] = t6 - v6;
    }

    // 1D IDCT on Columns
    for (i = 0; i < 64; i += 8) {
        v0 = block[i + 4];
        v1 = block[i + 2] + block[i + 6];
        v2 = block[i + 5] - block[i + 3];
        v3 = block[i + 1] + block[i + 7];
        v4 = block[i + 3] + block[i + 5];
        v5 = block[i + 1] - block[i + 7];
        v6 = v3 + v4;
        v7 = block[i];

        t0 = (v5 * 0x1d9 - v2 * 0xc4 + 0x80) >> 8 - v6;
        t1 = t0 - ((v3 - v4) * 0x16a + 0x80) >> 8;
        t2 = v7 - v0;
        t3 = ((block[i + 2] - block[i + 6]) * 0x16a + 0x80) >> 8 - v1;
        t4 = v7 + v0;
        t5 = t2 + t3;
        t6 = t4 + v1;
        t7 = t2 - t3;
        t8 = t4 - v1;
        t9 = (-t1 + v2 * 0x1d9 + v5 * 0xc4 + 0x80) >> 8;

        block[i]     = (v6 + t6 + 0x80) >> 8;
        block[i + 1] = (t0 + t5 + 0x80) >> 8;
        block[i + 2] = (t7 - t1 + 0x80) >> 8;
        block[i + 3] = (t8 - t9 + 0x80) >> 8;
        block[i + 4] = (t8 + t9 + 0x80) >> 8;
        block[i + 5] = (t1 + t7 + 0x80) >> 8;
        block[i + 6] = (t5 - t0 + 0x80) >> 8;
        block[i + 7] = (t6 - v6 + 0x80) >> 8;
    }
}
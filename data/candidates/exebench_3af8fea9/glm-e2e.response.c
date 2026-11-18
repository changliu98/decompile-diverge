int mpeg3video_idctrow(int16_t *block) {
    int32_t tmp0 = (int32_t)block[4] << 11;
    int32_t tmp1 = (int32_t)block[6];
    int32_t tmp2 = (int32_t)block[2];
    int32_t tmp3 = (int32_t)block[7];
    int32_t tmp4 = (int32_t)block[5];
    int32_t tmp5 = (int32_t)block[3];

    // Fast path: if all AC coefficients are zero, only DC is used
    if ((tmp0 | tmp1 | tmp2 | tmp3 | tmp4 | tmp5) == 0) {
        int16_t dc_val = (int16_t)((int32_t)block[0] << 3);
        for (int i = 0; i < 8; i++) {
            block[i] = dc_val;
        }
        return 0;
    } else {
        // Full IDCT calculation
        int32_t tmp6 = ((int32_t)block[0] << 11) + 128;

        int32_t temp = (tmp2 + tmp3) * 0x235;
        tmp2 = temp + tmp2 * 0x8e4;
        tmp3 = temp - tmp3 * 0xd4e;

        temp = (tmp4 + tmp5) * 0x968;
        tmp4 = temp - tmp4 * 0x31f;
        tmp5 = temp - tmp5 * 0xfb1;

        temp = tmp6 + tmp0;
        tmp6 = tmp6 - tmp0;

        tmp0 = (tmp1 + tmp5) * 0x454;
        tmp5 = tmp0 - tmp5 * 0xec8;
        tmp1 = tmp0 + tmp1 * 0x620;

        tmp0 = tmp2 + tmp4;
        tmp2 = tmp2 - tmp4;
        tmp4 = tmp3 + tmp5;
        tmp5 = tmp3 - tmp5;

        tmp3 = temp + tmp1;
        temp = temp - tmp1;
        tmp1 = tmp6 + tmp5;
        tmp6 = tmp6 - tmp5;

        tmp5 = ((tmp2 + tmp4) * 0xb5 + 128) >> 8;
        tmp2 = ((tmp2 - tmp4) * 0xb5 + 128) >> 8;

        block[0] = (int16_t)((tmp3 + tmp0) >> 8);
        block[1] = (int16_t)((tmp1 + tmp5) >> 8);
        block[2] = (int16_t)((tmp6 + tmp2) >> 8);
        block[3] = (int16_t)((temp + tmp4) >> 8);
        block[4] = (int16_t)((temp - tmp4) >> 8);
        block[5] = (int16_t)((tmp6 - tmp2) >> 8);
        block[6] = (int16_t)((tmp1 - tmp5) >> 8);
        block[7] = (int16_t)((tmp3 - tmp0) >> 8);

        return 1;
    }
}
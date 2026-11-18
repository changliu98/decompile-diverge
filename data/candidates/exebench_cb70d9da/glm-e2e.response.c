void BTIC2D_TransDCT_Vert(struct Matrix8x8 *src, struct Matrix8x8 *dst) {
    int32_t x0 = src->data[0][0];
    int32_t x1 = src->data[1][0];
    int32_t x2 = src->data[2][0];
    int32_t x3 = src->data[3][0];
    int32_t x4 = src->data[4][0];
    int32_t x5 = src->data[5][0];
    int32_t x6 = src->data[6][0];
    int32_t x7 = src->data[7][0];

    int32_t s0 = x0 + x7;
    int32_t s1 = x1 + x6;
    int32_t s2 = x2 + x5;
    int32_t s3 = x3 + x4;

    int32_t d0 = x0 - x7;
    int32_t d1 = x1 - x6;
    int32_t d2 = x2 - x5;
    int32_t d3 = x3 - x4;

    int32_t y0 = (s0 + s1 + s2 + s3) * 0x5b;
    int32_t y4 = (s0 - s1 - s2 + s3) * 0x5b;

    int32_t t0 = s0 - s3;
    int32_t t1 = s1 - s2;

    int32_t y2 = t0 * 0x76 + t1 * 0x31;
    int32_t y6 = t0 * 0x31 - t1 * 0x76;

    int32_t y1 = d0 * 0x7e + d1 * 0x6a + d2 * 0x47 + d3 * 0x19;
    int32_t y3 = d0 * 0x6a - d1 * 0x19 - d2 * 0x7e - d3 * 0x47;
    int32_t y5 = d0 * 0x47 - d1 * 0x7e + d2 * 0x19 + d3 * 0x6a;
    int32_t y7 = d0 * 0x19 - d1 * 0x47 + d2 * 0x6a - d3 * 0x7e;

    dst->data[0][0] = (y0 + 0x8000) >> 16;
    dst->data[1][0] = (y1 + 0x8000) >> 16;
    dst->data[2][0] = (y2 + 0x8000) >> 16;
    dst->data[3][0] = (y3 + 0x8000) >> 16;
    dst->data[4][0] = (y4 + 0x8000) >> 16;
    dst->data[5][0] = (y5 + 0x8000) >> 16;
    dst->data[6][0] = (y6 + 0x8000) >> 16;
    dst->data[7][0] = (y7 + 0x8000) >> 16;
}
void wht4x4(int16_t *coef)
{
    int a, b, c, d, e;
    int tmp0, tmp1, tmp2, tmp3;

    for (a = 0; a < 4; a++) {
        tmp0 = coef[a] + coef[a + 4];
        tmp1 = coef[a + 8] - coef[a + 12];
        tmp2 = (tmp0 - tmp1) >> 1;
        tmp3 = tmp2 - coef[a + 4];
        coef[a] = tmp0 - tmp3;
        coef[a + 4] = tmp3;
        coef[a + 8] = tmp2 + tmp1;
        coef[a + 12] = tmp2;
    }

    for (a = 0; a < 4; a++) {
        tmp0 = coef[a * 4] + coef[a * 4 + 1];
        tmp1 = coef[a * 4 + 2] - coef[a * 4 + 3];
        tmp2 = (tmp0 - tmp1) >> 1;
        tmp3 = tmp2 - coef[a * 4 + 1];
        coef[a * 4] = (tmp0 - tmp3) << 1;
        coef[a * 4 + 1] = tmp3 << 1;
        coef[a * 4 + 2] = (tmp2 + tmp1) << 1;
        coef[a * 4 + 3] = tmp2 << 1;
    }
}
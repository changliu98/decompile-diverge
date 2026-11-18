void drmp3_L3_idct3(float *dst, float x0, float x1, float x2)
{
    float t0, t1, t2;

    t0 = x0 + x2;
    t1 = x0 - x2;
    t2 = x1 * 1.4142135623730950488016887242097;

    dst[0] = t1 + t2;
    dst[1] = t0;
    dst[2] = t1 - t2;
}
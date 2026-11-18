void mdct_butterfly_8(float *x)
{
    float t0, t1, t2, t3, t4, t5, t6, t7;

    t0 = x[0] + x[2];
    t1 = x[0] - x[2];
    t2 = x[4] + x[6];
    t3 = x[4] - x[6];
    t4 = x[5] - x[1];
    t5 = x[5] + x[1];
    t6 = x[7] - x[3];
    t7 = x[7] + x[3];

    x[0] = t0 + t2;
    x[2] = t0 - t2;
    x[4] = t1 + t3;
    x[6] = t1 - t3;
    x[5] = t5 + t6;
    x[1] = t5 - t6;
    x[7] = t7 + t4;
    x[3] = t7 - t4;
}
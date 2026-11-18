static void func0(float *m)
{
    float t0 = m[0], t1 = m[1], t2 = m[2], t3 = m[3];
    m[0] = t0 + t2;
    m[1] = t1 + t3;
    m[2] = t0 - t2;
    m[3] = t1 - t3;
}
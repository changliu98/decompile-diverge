float reson(float *p, float x)
{
    p[3] = p[0] * x + p[1] * p[3] - p[2] * p[4];
    p[4] = p[3];
    return p[3];
}
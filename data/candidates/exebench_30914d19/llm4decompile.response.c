void rsVec_cross(float *v, float *a, float *b)
{
    v[0] = a[1] * b[2] - b[1] * a[2];
    v[1] = a[2] * b[0] - b[2] * a[0];
    v[2] = a[0] * b[1] - b[0] * a[1];
}
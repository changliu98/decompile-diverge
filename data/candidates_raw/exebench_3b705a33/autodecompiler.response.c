void vec_cubic(float *v0, float *v1, float *v2, float *v3, float t, float *r)
{
    r[0] = (1 - t) * (1 - t) * (1 - t) * v0[0] + 3 * (1 - t) * (1 - t) * t * v1[0] + 3 * (1 - t) * t * t * v2[0] + t * t * t * v3[0];
    r[1] = (1 - t) * (1 - t) * (1 - t) * v0[1] + 3 * (1 - t) * (1 - t) * t * v1[1] + 3 * (1 - t) * t * t * v2[1] + t * t * t * v3[1];
    r[2] = (1 - t) * (1 - t) * (1 - t) * v0[2] + 3 * (1 - t) * (1 - t) * t * v1[2] + 3 * (1 - t) * t * t * v2[2] + t * t * t * v3[2];
}
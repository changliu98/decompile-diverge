void mul_mat_vec_2(float *m, float *v, float *o)
{
    float x = m[0] * v[0] + m[1] * v[1];
    float y = m[2] * v[0] + m[3] * v[1];
    o[0] = x;
    o[1] = y;
}
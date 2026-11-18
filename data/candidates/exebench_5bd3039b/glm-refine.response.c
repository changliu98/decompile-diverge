void __cdecl mul_mat_vec_2(const float *m, const float *p, float *o)
{
    // Extract vector components
    float x = p[0];
    float y = p[1];

    // Extract matrix elements
    float m00 = m[0];
    float m01 = m[1];
    float m10 = m[2];
    float m11 = m[3];

    // Perform 2x2 matrix * 2x1 vector multiplication
    o[0] = (x * m00) + (y * m01);
    o[1] = (x * m10) + (y * m11);
}
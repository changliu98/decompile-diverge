void Mat4_vec3_mul_T(float *out, const float *m, const float *v) {
    float x = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    float y = m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7];
    float z = m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11];

    out[0] = x;
    out[1] = y;
    out[2] = z;
}
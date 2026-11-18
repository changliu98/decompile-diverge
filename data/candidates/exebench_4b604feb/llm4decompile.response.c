void ml_multiply_mat2_mat2(const float mat_a[4], const float mat_b[4], float out[4])
{
    float temp[4];
    temp[0] = mat_a[0] * mat_b[0] + mat_a[1] * mat_b[2];
    temp[1] = mat_a[0] * mat_b[1] + mat_a[1] * mat_b[3];
    temp[2] = mat_a[2] * mat_b[0] + mat_a[3] * mat_b[2];
    temp[3] = mat_a[2] * mat_b[1] + mat_a[3] * mat_b[3];
    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
}
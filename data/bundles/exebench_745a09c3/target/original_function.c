void ml_multiply_mat4_mat4(float mat_a[16], float mat_b[16], float out[16])
{
    float temp[16];

    temp[0] = mat_a[0] * mat_b[0] + mat_a[1] * mat_b[4] + mat_a[2] * mat_b[8] + mat_a[3] * mat_b[12];
    temp[1] = mat_a[0] * mat_b[1] + mat_a[1] * mat_b[5] + mat_a[2] * mat_b[9] + mat_a[3] * mat_b[13];
    temp[2] = mat_a[0] * mat_b[2] + mat_a[1] * mat_b[6] + mat_a[2] * mat_b[10] + mat_a[3] * mat_b[14];
    temp[3] = mat_a[0] * mat_b[3] + mat_a[1] * mat_b[7] + mat_a[2] * mat_b[11] + mat_a[3] * mat_b[15];
    temp[4] = mat_a[4] * mat_b[0] + mat_a[5] * mat_b[4] + mat_a[6] * mat_b[8] + mat_a[7] * mat_b[12];
    temp[5] = mat_a[4] * mat_b[1] + mat_a[5] * mat_b[5] + mat_a[6] * mat_b[9] + mat_a[7] * mat_b[13];
    temp[6] = mat_a[4] * mat_b[2] + mat_a[5] * mat_b[6] + mat_a[6] * mat_b[10] + mat_a[7] * mat_b[14];
    temp[7] = mat_a[4] * mat_b[3] + mat_a[5] * mat_b[7] + mat_a[6] * mat_b[11] + mat_a[7] * mat_b[15];
    temp[8] = mat_a[8] * mat_b[0] + mat_a[9] * mat_b[4] + mat_a[10] * mat_b[8] + mat_a[11] * mat_b[12];
    temp[9] = mat_a[8] * mat_b[1] + mat_a[9] * mat_b[5] + mat_a[10] * mat_b[9] + mat_a[11] * mat_b[13];
    temp[10] = mat_a[8] * mat_b[2] + mat_a[9] * mat_b[6] + mat_a[10] * mat_b[10] + mat_a[11] * mat_b[14];
    temp[11] = mat_a[8] * mat_b[3] + mat_a[9] * mat_b[7] + mat_a[10] * mat_b[11] + mat_a[11] * mat_b[15];
    temp[12] = mat_a[12] * mat_b[0] + mat_a[13] * mat_b[4] + mat_a[14] * mat_b[8] + mat_a[15] * mat_b[12];
    temp[13] = mat_a[12] * mat_b[1] + mat_a[13] * mat_b[5] + mat_a[14] * mat_b[9] + mat_a[15] * mat_b[13];
    temp[14] = mat_a[12] * mat_b[2] + mat_a[13] * mat_b[6] + mat_a[14] * mat_b[10] + mat_a[15] * mat_b[14];
    temp[15] = mat_a[12] * mat_b[3] + mat_a[13] * mat_b[7] + mat_a[14] * mat_b[11] + mat_a[15] * mat_b[15];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
    out[4] = temp[4];
    out[5] = temp[5];
    out[6] = temp[6];
    out[7] = temp[7];
    out[8] = temp[8];
    out[9] = temp[9];
    out[10] = temp[10];
    out[11] = temp[11];
    out[12] = temp[12];
    out[13] = temp[13];
    out[14] = temp[14];
    out[15] = temp[15];
}
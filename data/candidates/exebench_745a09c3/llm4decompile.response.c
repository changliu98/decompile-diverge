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
 temp[7] = mat_a[4] * mat_b[3] + mat_a[5] * mat_b
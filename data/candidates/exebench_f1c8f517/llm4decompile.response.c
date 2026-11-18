void ml_multiply_mat4_vec4(float mat[16], float vec[4], float out[4])
{
    float x = vec[0], y = vec[1], z = vec[2], w = vec[3];
    out[0] = mat[0] * x + mat[1] * y + mat[2] * z + mat[3] * w;
    out[1] = mat[4] * x + mat[5] * y + mat[6] * z + mat[7] * w;
    out[2] = mat[8] * x + mat[9] * y + mat[10] * z + mat[11] * w;
    out[3] = mat[12] * x + mat[13] * y + mat[14] * z + mat[15] * w;
}
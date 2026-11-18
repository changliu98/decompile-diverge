void Mat4_Translate(float mat[16], const float v[3])
{
    mat[12] += mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2];
    mat[13] += mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2];
    mat[14] += mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2];
}
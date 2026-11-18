void Mat4_affine_inv(float* mat)
{
    float tmp;


    tmp = mat[1];
    mat[1] = mat[4];
    mat[4] = tmp;

    tmp = mat[2];
    mat[2] = mat[8];
    mat[8] = tmp;

    tmp = mat[6];
    mat[6] = mat[9];
    mat[9] = tmp;


    tmp = -(mat[0] * mat[12] + mat[1] * mat[13] + mat[2] * mat[14]);
    mat[12] = tmp;

    tmp = -(mat[4] * mat[12] + mat[5] * mat[13] + mat[6] * mat[14]);
    mat[13] = tmp;

    tmp = -(mat[8] * mat[12] + mat[9] * mat[13] + mat[10] * mat[14]);
    mat[14] = tmp;
}
void Mat4_vec3_mul_inv(float v[3], float mat[16], float src[3])
{
    float ret[3];

    ret[0] = mat[0] * src[0] + mat[1] * src[1] + mat[2] * src[2];
    ret[0] -= mat[0] * mat[12]+ mat[1] * mat[13]+ mat[2] * mat[14];
    ret[1] = mat[4] * src[0] + mat[5] * src[1] + mat[6] * src[2];
    ret[1] -= mat[4] * mat[12]+ mat[5] * mat[13]+ mat[6] * mat[14];
    ret[2] = mat[8] * src[0] + mat[9] * src[1] + mat[10] * src[2];
    ret[2] -= mat[8] * mat[12]+ mat[9] * mat[13]+ mat[10] * mat[14];
    {(v)[0] = (ret)[0]; (v)[1] = (ret)[1]; (v)[2] = (ret)[2];};
}
void Mat4_vec3_mul(float v[3], const float mat[16], const float src[3])
{
    float ret[3];

    ret[0] = mat[0] * src[0] + mat[4] * src[1] + mat[8] * src[2] + mat[12];
    ret[1] = mat[1] * src[0] + mat[5] * src[1] + mat[9] * src[2] + mat[13];
    ret[2] = mat[2] * src[0] + mat[6] * src[1] + mat[10] * src[2] + mat[14];
    {(v)[0] = (ret)[0]; (v)[1] = (ret)[1]; (v)[2] = (ret)[2];};
}
void Mat4_vec3_mul_inv(float *ret, float *mat, float *vec)
{
  float x = (mat[0]*vec[0]) + (mat[1]*vec[1]) + (mat[2]*vec[2]) - (mat[12]*mat[0]) - (mat[13]*mat[1]) - (mat[14]*mat[2]);
  float y = (mat[4]*vec[0]) + (mat[5]*vec[1]) + (mat[6]*vec[2]) - (mat[12]*mat[4]) - (mat[13]*mat[5]) - (mat[14]*mat[6]);
  float z = (mat[8]*vec[0]) + (mat[9]*vec[1]) + (mat[10]*vec[2]) - (mat[12]*mat[8]) - (mat[13]*mat[9]) - (mat[14]*mat[10]);
  ret[0] = (mat[0]*vec[0]) + (mat[1]*vec[1]) + (mat[2]*vec[2]) - (mat[12]*mat[0]) - (mat[13]*mat[1]) - (mat[14]*mat[2]);
  ret[1] = x;
  ret[2] = y;
}
void __cdecl Mat4_vec3_mul_inv(float *v, float *mat, float *src)
{
  float src_x = src[0];
  float src_y = src[1];
  float src_z = src[2];

  float mat_x = mat[12];
  float mat_y = mat[13];
  float mat_z = mat[14];

  // X component
  v[0] = (mat[0] * src_x + mat[1] * src_y + mat[2] * src_z) - 
         (mat[0] * mat_x  + mat[1] * mat_y  + mat[2] * mat_z);
  
  // Y component
  v[1] = (mat[4] * src_x + mat[5] * src_y + mat[6] * src_z) - 
         (mat[4] * mat_x  + mat[5] * mat_y  + mat[6] * mat_z);
  
  // Z component
  v[2] = (mat[8] * src_x + mat[9] * src_y + mat[10] * src_z) - 
         (mat[8] * mat_x  + mat[9] * mat_y  + mat[10] * mat_z);
}
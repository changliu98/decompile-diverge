void __cdecl mult_mat_vec(float *v, const float *M, const float *u)
{
  // The matrix M is stored in a column-major layout (e.g., OpenGL format).
  // This function computes the matrix-vector product: v = M * u
  
  float u0 = u[0];
  float u1 = u[1];
  float u2 = u[2];
  float u3 = u[3];

  // X component
  v[0] = M[0]  * u0 + M[4] * u1 + M[8]  * u2 + M[12] * u3;
  
  // Y component
  v[1] = M[1]  * u0 + M[5] * u1 + M[9]  * u2 + M[13] * u3;
  
  // Z component
  v[2] = M[2]  * u0 + M[6] * u1 + M[10] * u2 + M[14] * u3;
  
  // W component
  v[3] = M[3]  * u0 + M[7] * u1 + M[11] * u2 + M[15] * u3;
}
float vec3f_dot(float *A,float *B)

{
  float *B_local;
  float *A_local;
  
  return A[2] * B[2] + *A * *B + A[1] * B[1];
}
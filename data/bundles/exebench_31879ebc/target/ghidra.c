float vec4f_dot(float *A,float *B)

{
  float *B_local;
  float *A_local;
  
  return A[3] * B[3] + A[2] * B[2] + *A * *B + A[1] * B[1];
}
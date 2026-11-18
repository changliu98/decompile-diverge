float __cdecl vec4f_dot(const float *A, const float *B)
{
  return A[0] * B[0] 
       + A[1] * B[1] 
       + A[2] * B[2] 
       + A[3] * B[3];
}
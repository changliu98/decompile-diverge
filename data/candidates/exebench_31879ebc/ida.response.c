float __cdecl vec4f_dot(const float *A, const float *B)
{
  return (float)(A[3] * B[3]) + (float)((float)(A[2] * B[2]) + (float)((float)(*A * *B) + (float)(A[1] * B[1])));
}
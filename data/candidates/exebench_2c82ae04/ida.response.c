float __cdecl vec3f_dot(const float *A, const float *B)
{
  return (float)(A[2] * B[2]) + (float)((float)(*A * *B) + (float)(A[1] * B[1]));
}
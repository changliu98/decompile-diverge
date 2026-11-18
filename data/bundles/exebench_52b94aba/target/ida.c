float __cdecl qdot(float *a, float *b)
{
  return (float)(a[3] * b[3]) + (float)((float)(a[2] * b[2]) + (float)((float)(*a * *b) + (float)(a[1] * b[1])));
}
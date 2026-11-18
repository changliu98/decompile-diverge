float __cdecl vector3d_dot(float *a, float *b)
{
  return (float)(a[2] * b[2]) + (float)((float)(*a * *b) + (float)(a[1] * b[1]));
}
float __cdecl vector3d_dot(float *a, float *b)
{
  // Computes the dot product of two 3D vectors: (a[0]*b[0]) + (a[1]*b[1]) + (a[2]*b[2])
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
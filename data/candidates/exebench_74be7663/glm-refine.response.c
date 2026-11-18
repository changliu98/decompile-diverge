Optimized for reverse engineering readability
void __cdecl mlPointSub(float *a, const float *b)
{
  // Unrolled loop: subtracts 3D vector b from 3D vector a in-place
  a[0] -= b[0];
  a[1] -= b[1];
  a[2] -= b[2];
}
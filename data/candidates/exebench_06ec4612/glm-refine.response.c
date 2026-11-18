void __cdecl matrix2r(const double *A, double *r)
{
  // Extract the translation vector (assuming row-major 3x4 or 4x4 matrix)
  r[0] = A[3];
  r[1] = A[7];
  r[2] = A[11];
}
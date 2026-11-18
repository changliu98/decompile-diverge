void __cdecl matrix2r(const double *A, double *r)
{
  *r = A[3];
  r[1] = A[7];
  r[2] = A[11];
}
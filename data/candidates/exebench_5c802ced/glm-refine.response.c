void __cdecl mult(double *A, const double *a, double *b)
{
  for (int c = 0; c < 4; ++c)
  {
    int i = c * 4;
    b[c] = A[i]     * a[0]
         + A[i + 1] * a[1]
         + A[i + 2] * a[2]
         + A[i + 3] * a[3];
  }
}
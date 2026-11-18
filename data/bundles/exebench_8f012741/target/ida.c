void __cdecl lin_solve_2(double *x, const double *A, const double *y)
{
  double idet; // [rsp+0h] [rbp-20h]

  idet = 1.0 / (*A * A[3] - A[1] * A[2]);
  *x = idet * (A[3] * *y - A[1] * y[1]);
  x[1] = idet * (*A * y[1] - A[2] * *y);
}
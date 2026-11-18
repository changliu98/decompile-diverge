void __cdecl lin_solve_2(double *x, const double *A, const double *y)
{
  double a11 = A[0];
  double a12 = A[1];
  double a21 = A[2];
  double a22 = A[3];

  double y1 = y[0];
  double y2 = y[1];

  // Calculate the determinant of A
  double det = a11 * a22 - a12 * a21;
  
  // Compute the inverse of the determinant
  double idet = 1.0 / det;

  // Compute the solution vector x using Cramer's rule:
  // x1 = (y1 * a22 - y2 * a12) / det
  // x2 = (y2 * a11 - y1 * a21) / det
  x[0] = idet * (a22 * y1 - a12 * y2);
  x[1] = idet * (a11 * y2 - a21 * y1);
}
void lin_solve_2(double *x, double *A, double *y)
{
  // Calculate the inverse of the determinant of the 2x2 matrix A
  // Matrix A is assumed to be stored as [A[0], A[1], A[2], A[3]]
  // Determinant = A[0]*A[3] - A[1]*A[2]
  double determinant_inv = DAT_00102010 / (*A * A[3] - A[1] * A[2]);
  
  // Compute x[0] using Cramer's rule or matrix inversion
  // x[0] = (A[3]*y[0] - A[1]*y[1]) / determinant
  *x = determinant_inv * (A[3] * *y - A[1] * y[1]);
  
  // Compute x[1] using Cramer's rule or matrix inversion
  // x[1] = (A[0]*y[1] - A[2]*y[0]) / determinant
  x[1] = determinant_inv * (*A * y[1] - A[2] * *y);
}
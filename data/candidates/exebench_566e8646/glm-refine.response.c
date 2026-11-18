void __cdecl lin_solve_3(double *x, const double *A, const double *y)
{
  // Unpack the 3x3 matrix A into named elements for readability
  double a11 = A[0], a12 = A[1], a13 = A[2];
  double a21 = A[3], a22 = A[4], a23 = A[5];
  double a31 = A[6], a32 = A[7], a33 = A[8];

  // Unpack the 3x1 vector y
  double y1 = y[0], y2 = y[1], y3 = y[2];

  // Compute the determinant of A
  double det = a11 * (a22 * a33 - a23 * a32)
             + a12 * (a23 * a31 - a21 * a33)
             + a13 * (a21 * a32 - a22 * a31);

  // Compute the inverse of the determinant
  double idet = 1.0 / det;

  // Compute the elements of the inverse matrix A^(-1) (adjugate of A transposed)
  double inv11 = a22 * a33 - a23 * a32;
  double inv12 = a13 * a32 - a12 * a33;
  double inv13 = a12 * a23 - a13 * a22;
  
  double inv21 = a23 * a31 - a21 * a33;
  double inv22 = a11 * a33 - a13 * a31;
  double inv23 = a13 * a21 - a11 * a23;
  
  double inv31 = a21 * a32 - a22 * a31;
  double inv32 = a12 * a31 - a11 * a32;
  double inv33 = a11 * a22 - a12 * a21;

  // Multiply A^(-1) * y to find x
  x[0] = idet * (inv11 * y1 + inv12 * y2 + inv13 * y3);
  x[1] = idet * (inv21 * y1 + inv22 * y2 + inv23 * y3);
  x[2] = idet * (inv31 * y1 + inv32 * y2 + inv33 * y3);
}
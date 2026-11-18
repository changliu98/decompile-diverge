void __cdecl geom_matinv2d(double *m)
{
  double a = m[0];
  double b = m[1];
  double c = m[2];
  double d = m[3];

  // Calculate the determinant of the 2x2 matrix
  double det = a * d - b * c;
  
  // Precompute the inverse determinant and its negation
  double inv_det = 1.0 / det;
  double neg_inv_det = -inv_det;

  // Compute the inverse matrix components
  m[0] =  inv_det * d;
  m[1] = neg_inv_det * b;
  m[2] = neg_inv_det * c;
  m[3] =  inv_det * a;
}
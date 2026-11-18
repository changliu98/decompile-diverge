void lincomb(double scalar1, double *vector1, double scalar2, double *vector2, double *result)
{
  // Compute the linear combination w = k1*u + k2*v for the first element
  *result = scalar1 * *vector1 + scalar2 * *vector2;
  // Compute the linear combination for the second element
  result[1] = scalar1 * vector1[1] + scalar2 * vector2[1];
  // Compute the linear combination for the third element
  result[2] = scalar1 * vector1[2] + scalar2 * vector2[2];
}
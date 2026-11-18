void ccp4_dcross(double *vec1, double *vec2, double *result)
{
  // Compute the cross product of vectors a and b, storing the result in c
  // c[0] = a[1]*b[2] - a[2]*b[1]
  result[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
  // c[1] = a[2]*b[0] - a[0]*b[2]
  result[1] = vec1[2] * vec2[0] - vec2[2] * vec1[0];
  // c[2] = a[0]*b[1] - a[1]*b[0]
  result[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];
}
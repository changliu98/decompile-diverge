// Computes the cross product of two 3D vectors a and b, storing the result in c.
// c = a x b
void cross3(double *vec_a, double *vec_b, double *result)
{
  // c[0] = a[1]*b[2] - a[2]*b[1]
  result[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
  // c[1] = a[2]*b[0] - a[0]*b[2]
  result[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
  // c[2] = a[0]*b[1] - a[1]*b[0]
  result[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
}
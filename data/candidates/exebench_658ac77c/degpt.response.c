// Adds two 3D vectors a and b, storing the result in out
void vertexAdd(double *vector_a, double *vector_b, double *result)
{
  // Add x-components
  *result = *vector_a + *vector_b;
  // Add y-components
  result[1] = vector_a[1] + vector_b[1];
  // Add z-components
  result[2] = vector_a[2] + vector_b[2];
}
// Computes the dot product of two 3D vectors a and b
// Returns the scalar result of the dot product
float lib3ds_vector_dot(float *vector_a, float *vector_b)
{
  // Calculate dot product: a.x*b.x + a.y*b.y + a.z*b.z
  // Note: The order of terms is non-standard (z, x, y) but mathematically equivalent
  return vector_a[2] * vector_b[2] + *vector_a * *vector_b + vector_a[1] * vector_b[1];
}
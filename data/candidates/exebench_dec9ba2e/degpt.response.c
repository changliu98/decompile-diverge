// Subtracts vector b from vector a and stores the result in result
void mlVectorSubTo(float *vector_a, float *vector_b, float *output_vector)
{
  // Iterate through each component of the 3D vectors
  for (uint index = 0; index < 3; index++) {
    // Perform element-wise subtraction: result[i] = a[i] - b[i]
    output_vector[index] = vector_a[index] - vector_b[index];
  }
}
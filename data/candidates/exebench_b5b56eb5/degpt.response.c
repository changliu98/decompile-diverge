/**
 * @brief Subtracts two 3D points and stores the result.
 *
 * Computes the element-wise difference between two 3D vectors (a - b)
 * and stores the result in the provided result array.
 *
 * @param a       Pointer to the first 3D vector (minuend).
 * @param b       Pointer to the second 3D vector (subtrahend).
 * @param result  Pointer to the array where the resulting 3D vector will be stored.
 */
void mlPointSubTo(float *vector_a, float *vector_b, float *output_vector)
{
  // Iterate through each component (x, y, z) of the 3D vectors
  for (uint index = 0; index < 3; index++) {
    // Subtract corresponding components and store in result
    output_vector[index] = vector_a[index] - vector_b[index];
  }
}
// Scales each element of the 4x4 matrix 'a' by the scalar 'b' and stores the result in 'out'.
void warp_mat4_scale(float *output_matrix, float *input_matrix, float scalar_value) {
  // Iterate through all 16 elements of the 4x4 matrix (4 rows * 4 columns)
  for (int index = 0; index < 0x10; index++) {
    // Multiply the i-th element of matrix 'a' by scalar 'b' and store in 'out'
    output_matrix[index] = input_matrix[index] * scalar_value;
  }
}
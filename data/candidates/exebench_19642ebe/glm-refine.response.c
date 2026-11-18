void __cdecl multiply_naive(const float *A, const float *B, float *result)
{
  // The outer loop steps by 4, representing the row index in B and result
  for (int row = 0; row < 16; row += 4)
  {
    // The inner loop represents the column index in A and result
    for (int col = 0; col < 4; ++col)
    {
      // Standard 4x4 matrix multiplication: dot product of B's row and A's column
      result[row + col] = B[row]     * A[col]      + 
                          B[row + 1] * A[col + 4]  + 
                          B[row + 2] * A[col + 8]  + 
                          B[row + 3] * A[col + 12];
    }
  }
}
void __cdecl warp_mat4_fill_identity(float *matrix)
{
  // The function initializes a 4x4 matrix to the identity matrix.
  // Layout (Row-Major):
  // | 1  0  0  0 |
  // | 0  1  0  0 |
  // | 0  0  1  0 |
  // | 0  0  0  1 |
  
  matrix[0]  = 1.0f;
  matrix[1]  = 0.0f;
  matrix[2]  = 0.0f;
  matrix[3]  = 0.0f;
  
  matrix[4]  = 0.0f;
  matrix[5]  = 1.0f;
  matrix[6]  = 0.0f;
  matrix[7]  = 0.0f;
  
  matrix[8]  = 0.0f;
  matrix[9]  = 0.0f;
  matrix[10] = 1.0f;
  matrix[11] = 0.0f;
  
  matrix[12] = 0.0f;
  matrix[13] = 0.0f;
  matrix[14] = 0.0f;
  matrix[15] = 1.0f;
}
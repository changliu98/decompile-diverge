void __cdecl dot_matrixT_vector_did(double matrix[3][3], long in[3], double out[3])
{
  // Cast the integer vector components to doubles explicitly, 
  // matching the original (double)(int) truncation behavior.
  double in0 = (double)in[0];
  double in1 = (double)in[1];
  double in2 = (double)in[2];

  // The matrix is accessed in row-major order, representing a transposed 
  // matrix multiplication (Matrix^T * Vector).
  out[0] = matrix[0][0] * in0 + matrix[1][0] * in1 + matrix[2][0] * in2;
  out[1] = matrix[0][1] * in0 + matrix[1][1] * in1 + matrix[2][1] * in2;
  out[2] = matrix[0][2] * in0 + matrix[1][2] * in1 + matrix[2][2] * in2;
}
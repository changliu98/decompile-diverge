void __cdecl mlVectorMultMatrixTo(const float *a, const float *b, float *result)
{
  // Vector 'a' components
  float a0 = a[0];
  float a1 = a[1];
  float a2 = a[2];

  // Matrix 'b' elements (Row-major 4x4 matrix)
  // Row 0
  float b0  = b[0];
  float b4  = b[4];
  float b8  = b[8];
  float b12 = b[12];
  // Row 1
  float b1  = b[1];
  float b5  = b[5];
  float b9  = b[9];
  float b13 = b[13];
  // Row 2
  float b2  = b[2];
  float b6  = b[6];
  float b10 = b[10];
  float b14 = b[14];

  // Perform Vector * Matrix multiplication
  // (Assuming implicit a[3] = 1.0 for the translation column)
  result[0] = a0 * b0  + a1 * b4  + a2 * b8  + b12;
  result[1] = a0 * b1  + a1 * b5  + a2 * b9  + b13;
  result[2] = a0 * b2  + a1 * b6  + a2 * b10 + b14;
}
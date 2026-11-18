void __cdecl Mat4_affine_inv(float *mat)
{
  // Cast the pointer to a 4x4 matrix array for cleaner indexing
  float (*m)[4] = (float (*)[4])mat;

  // Transpose the upper 3x3 rotation/scale portion of the matrix
  float tmp;

  tmp = m[0][1]; m[0][1] = m[1][0]; m[1][0] = tmp;
  tmp = m[0][2]; m[0][2] = m[2][0]; m[2][0] = tmp;
  tmp = m[1][2]; m[1][2] = m[2][1]; m[2][1] = tmp;

  // Compute the new translation vector: -R_transposed * t
  float t0 = m[0][0] * m[3][0] + m[0][1] * m[3][1] + m[0][2] * m[3][2];
  float t1 = m[1][0] * m[3][0] + m[1][1] * m[3][1] + m[1][2] * m[3][2];
  float t2 = m[2][0] * m[3][0] + m[2][1] * m[3][1] + m[2][2] * m[3][2];

  // Bitwise XOR with 0x80000000 flips the sign bit of the IEEE 754 float
  m[3][0] = -t0;
  m[3][1] = -t1;
  m[3][2] = -t2;
}
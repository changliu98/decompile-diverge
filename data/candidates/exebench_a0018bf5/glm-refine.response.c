void __cdecl innerdct(const double *a, double *b, const double *c)
{
  // Even-indexed butterflies (sums)
  double b2 = a[0] + a[7];
  double b3 = a[1] + a[6];
  double b4 = a[2] + a[5];
  double b5 = a[3] + a[4];

  // Stage 1 sums
  double b0 = (b2 + b5) * c[4];
  double b1 = (b3 + b4) * c[4];

  // Output 0 and 32 (DC and Nyquist)
  b[0]  = b0 + b1;
  b[32] = b0 - b1;

  // Output 16 and 48
  b[16] = (b2 - b5) * c[2] + (b3 - b4) * c[6];
  b[48] = (b2 - b5) * c[6] + (b4 - b3) * c[2];

  // Odd-indexed butterflies (differences)
  double b0a = a[0] - a[7];
  double b1a = a[1] - a[6];
  double b2a = a[2] - a[5];
  double b3a = a[3] - a[4];

  // Outputs 8, 24, 40, 56
  // Note: The bitwise XOR operations from the IDA decompilation are standard IEEE 754 sign bit flips, 
  // which are equivalent to simple negation in floating-point arithmetic.
  b[8]  = b0a * c[1] + b1a * c[3] + b2a * c[5] + b3a * c[7];
  b[24] = b0a * c[3] - b1a * c[7] - b2a * c[1] - b3a * c[5];
  b[40] = b0a * c[5] - b1a * c[1] + b2a * c[7] + b3a * c[3];
  b[56] = b0a * c[7] - b1a * c[5] + b2a * c[3] - b3a * c[1];
}
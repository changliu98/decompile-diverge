void __cdecl mdct_butterfly_8(float *x)
{
  // Load all inputs into local variables to avoid memory aliasing issues
  float x0 = x[0];
  float x1 = x[1];
  float x2 = x[2];
  float x3 = x[3];
  float x4 = x[4];
  float x5 = x[5];
  float x6 = x[6];
  float x7 = x[7];

  // Stage 1: Butterflies
  float r0 = x6 + x2;
  float r1 = x6 - x2;
  float r2 = x4 + x0;
  float r3 = x4 - x0;

  float r0a = x5 - x1;
  float r2a = x7 - x3;
  float r0b = x5 + x1;
  float r1a = x7 + x3;

  // Stage 2: Cross-additions and subtractions
  x[6] = r0 + r2;
  x[4] = r0 - r2;

  x[0] = r1 + r0a;
  x[2] = r1 - r0a;

  x[3] = r2a + r3;
  x[1] = r2a - r3;

  x[7] = r1a + r0b;
  x[5] = r1a - r0b;
}
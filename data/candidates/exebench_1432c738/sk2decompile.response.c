void OsdGetBoxSplineWeights(float x, float y, float *w) {
  int i;
  float a, a2, a3, x2, x3, y2;
  a = 1.0f - x - y;
  a2 = a * a;
  a3 = a * a2;
  x2 = x * x;
  x3 = x * x2;
  y2 = y * y;
  w[0] = a3 * 2.0f + a2 * x;
  w[1] = a3 * 2.0f + a2 * y;
  w[8] = a3 * 2.0f + a2 * a;
  w[11] = a3 * 2.0f + a2 * x;
  w[9] = a3 * 2.0f + a2 * y;
  w[5] = a3 * 2.0f + a2 * a;
  w[2] = a3 * 6.0f + a2 * 12.0f * x2 + a * 6.0f * x3 + x * 12.0f * y2 +
         y * 6.0f * a2;
  w[4] = a3 * 6.0f + a2 * 12.0f * a + x * 6.0f * x3 + y * 12.0f * x2 +
         y2 * 6.0f * a2;
  w[10] = a3 * 6.0f + a2 * 12.0f * y + a * 6.0f * y2 + x * 12.0f * x3 +
          x2 * 6.0f * a2;
  w[3] = a3 * 12.0f + a2 * 60.0f * x2 + a * 24.0f * x3 + x * 36.0f * y2 +
         y * 24.0f * a2 + x2 * 8.0f * a3 + x3 * 6.0f * a2 + y2 * 6.0f * a;
  w[6] = a3 * 12.0f + a2 * 60.0f * a + x * 24.0f * y2 + y * 36.0f * x2 +
         a * 24.0f * x2 + y2 * 8.0f * a2 + x2 * 6.0f * a + x3 * 6.0f * y;
  w[7] = a3 * 12.0f + a2 * 60.0f * y + a * 24.0f * x3 + x * 36.0f * x2 +
         y * 24.0f * a + x2 * 8.0f * a2 + x3 * 6.0f * x + y2 * 6.0f * a;
  for (i = 0; i < 12; i++) w[i] *= 0.083333336f;
}
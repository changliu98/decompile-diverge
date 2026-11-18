void mlCubicBezier(float *p0, float *p1, float *p2, float *p3, float t,
                   float *result) {
  float mt = 1.0f - t;
  result[0] = p0[0] * mt * mt * mt + p1[0] * 3 * mt * mt * t +
              p2[0] * 3 * mt * t * t + p3[0] * t * t * t;
  result[1] = p0[1] * mt * mt * mt + p1[1] * 3 * mt * mt * t +
              p2[1] * 3 * mt * t * t + p3[1] * t * t * t;
  result[2] = p0[2] * mt * mt * mt + p1[2] * 3 * mt * mt * t +
              p2[2] * 3 * mt * t * t + p3[2] * t * t * t;
}
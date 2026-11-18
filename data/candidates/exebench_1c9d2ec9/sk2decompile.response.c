void OsdGetBSplineWeights(float t, float *w, float *dw, float *ddw) {
  float t2 = t * t;
  float t3 = t2 * t;
  w[0] = (-3 * (t - t2) + 1 + 3 * t3) / 6.0f;
  w[1] = (3 * t2 - 6 * t + 4 + 3 * t3) / 6.0f;
  w[2] = (-3 * (t + t2) + 1 + 3 * t3) / 6.0f;
  w[3] = (t3) / 6.0f;
  if (dw) {
    dw[0] = t - 0.5f * t2 - 0.5f;
    dw[1] = 1.5f * t2 - 2.0f * t;
    dw[2] = -1.5f * t2 + t + 0.5f;
    dw[3] = 0.5f * t2;
  }
  if (ddw) {
    ddw[0] = -t + 1.0f;
    ddw[1] = 3 * t - 2.0f;
    ddw[2] = -3 * t + 1.0f;
    ddw[3] = t;
  }
}
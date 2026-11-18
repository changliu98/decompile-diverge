void OsdGetBezierWeights(float t, float *w, float *dw, float *ddw) {
  float t1 = 1.0f - t;
  float t12 = t1 * t1;
  float t1t = t1 * t;
  float t2 = t * t;
  w[0] = t12 * t1;
  w[1] = 3.0f * t12 * t;
  w[2] = 3.0f * t1t * t;
  w[3] = t2 * t;
  if (dw) {
    dw[0] = -3.0f * t12;
    dw[1] = 9.0f * t12 * t - 12.0f * t + 3.0f;
    dw[2] = -9.0f * t12 + 6.0f * t;
    dw[3] = 3.0f * t12;
  }
  if (ddw) {
    ddw[0] = 6.0f * t1;
    ddw[1] = 18.0f * t - 12.0f;
    ddw[2] = -18.0f * t + 6.0f;
    ddw[3] = 6.0f * t;
  }
}
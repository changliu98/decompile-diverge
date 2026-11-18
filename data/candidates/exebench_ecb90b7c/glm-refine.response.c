void __cdecl OsdGetBezierWeights(float t, float *wP, float *wDP, float *wDP2)
{
  float t2 = t * t;
  float tC2 = (1.0f - t) * (1.0f - t);

  // Cubic Bezier basis functions (Bernstein polynomials)
  wP[0] = tC2 * (1.0f - t);
  wP[1] = tC2 * t * 3.0f;
  wP[2] = t2 * (1.0f - t) * 3.0f;
  wP[3] = t2 * t;

  // First derivatives
  if (wDP)
  {
    wDP[0] = -3.0f * tC2;
    wDP[1] = 9.0f * t2 - 12.0f * t + 3.0f;
    wDP[2] = -9.0f * t2 + 6.0f * t;
    wDP[3] = 3.0f * t2;
  }

  // Second derivatives
  if (wDP2)
  {
    wDP2[0] = 6.0f * (1.0f - t);
    wDP2[1] = 18.0f * t - 12.0f;
    wDP2[2] = -18.0f * t + 6.0f;
    wDP2[3] = 6.0f * t;
  }
}
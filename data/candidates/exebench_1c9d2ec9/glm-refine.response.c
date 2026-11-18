void __cdecl OsdGetBSplineWeights(float t, float *wP, float *wDP, float *wDP2)
{
  float t2 = t * t;
  float t3 = t * t2;

  // Basis functions (B-Spline weights)
  wP[0] = 0.16666667f * (1.0f - t - 3.0f * (t - t2) - t3);
  wP[1] = 0.16666667f * (4.0f - 6.0f * t2 + 3.0f * t3);
  wP[2] = 0.16666667f * (1.0f + 3.0f * (t + t2 - t3));
  wP[3] = 0.16666667f * t3;

  // First derivatives
  if (wDP)
  {
    wDP[0] = t - 0.5f * t2 - 0.5f;
    wDP[1] = 1.5f * t2 - 2.0f * t;
    wDP[2] = t - 1.5f * t2 + 0.5f;
    wDP[3] = 0.5f * t2;
  }

  // Second derivatives
  if (wDP2)
  {
    wDP2[0] = 1.0f - t;
    wDP2[1] = 3.0f * t - 2.0f;
    wDP2[2] = 1.0f - 3.0f * t;
    wDP2[3] = t;
  }
}
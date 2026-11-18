void OsdGetBezierWeights(float t, float *wP, float *wDP, float *wDP2)
{
  float t2 = t * t;
  float t3 = t2 * t;
  float t1m = 1 - t;
  float t1m2 = t1m * t1m;
  wP[0] = t1m2 * (1 - t);
  wP[1] = t1m2 * 3 * t;
  wP[2] = t2 * 3 * (1 - t);
  wP[3] = t3 * t;
  if (wDP)
  {
    wDP[0] = -3 * t1m2;
    wDP[1] = 9 * t2 + 3 * t;
    wDP[2] = -9 * t2 + 6 * t;
    wDP[3] = 3 * t2;
  }
  if (wDP2)
  {
    wDP2[0] = 6 * t1m;
    wDP2[1] = 18 * t - 12;
    wDP2[2] = -18 * t + 6;
    wDP2[3] = 6 * t;
  }
}
float splev(float t, float *tvec, int n, float *cv, float *der)
{
  int i; int k = n - 2;
  float t1; float h; float d1;
  for (i = 0; i < n - 1; i++)
    if (tvec[i + 1] > t) {
      k = i;
      break;
    }
  t1 = t - tvec[k];
  h = tvec[k + 1] - tvec[k];
  d1 = (cv[k + 1] - cv[k]) / h;
  return (cv[k] + t1 * (t1 * (d1 + t1 * (0.5 * der[k + 1] - der[k]) / (6.0 * h))
   - h * (0.5 * der[k + 1] + der[k])
   + (cv[k + 1] - cv[k]) / h));
}
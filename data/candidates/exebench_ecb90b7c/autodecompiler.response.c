void
OsdGetBezierWeights(float t, float *cd0, float *cd1, float *cd2)
{
 float ti, t2, t2i;

 t2 = t*t;
 ti = 1.0f - t;
 t2i = ti*ti;

 cd0[0] = t2i*ti;
 cd0[1] = 3.0f * t2i*t;
 cd0[2] = 3.0f * t2*ti;
 cd0[3] = t2*t;

 if (cd1) {
  cd1[0] = -3.0f * t2i;
  cd1[1] = -6.0f * t2i*t + 9.0f * t2*ti + 3.0f;
  cd1[2] = 3.0f * t2i - 9.0f * t2*ti;
  cd1[3] = 3.0f * t2;
 }

 if (cd2) {
  cd2[0] = 6.0f * ti;
  cd2[1] = -12.0f * t + 6.0f;
  cd2[2] = 6.0f - 12.0f * t;
  cd2[3] = 6.0f * t;
 }
}
void mlQuadBezier(float *p0, float *p1, float *p2, float t, float *v)
{
  float t2 = t*t;
  float t1 = 1.0 - t;
  float t12 = t1*t1;
  float t1t = t1*t;
  float t2t = t*t1;
  v[0] = t12*p0[0] + t1t*p1[0] + t2t*p2[0];
  v[1] = t12*p0[1] + t1t*p1[1] + t2t*p2[1];
  v[2] = t12*p0[2] + t1t*p1[2] + t2t*p2[2];
}
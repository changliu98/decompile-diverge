void bezier(float t, float *p0, float *p1, float *p2, float *p3, float *res)
{
  res[0] = p0[0] * ((1-t)*(1-t)*(1-t))
    + p1[0] * (3*(1-t)*(1-t)*t)
    + p2[0] * (3*(1-t)*t*t)
    + p3[0] * (t*t*t);
  res[1] = p0[1] * ((1-t)*(1-t)*(1-t))
    + p1[1] * (3*(1-t)*(1-t)*t)
    + p2[1] * (3*(1-t)*t*t)
    + p3[1] * (t*t*t);
  res[2] = p0[2] * ((1-t)*(1-t)*(1-t))
    + p1[2] * (3*(1-t)*(1-t)*t)
    + p2[2] * (3*(1-t)*t*t)
    + p3[2] * (t*t*t);
}
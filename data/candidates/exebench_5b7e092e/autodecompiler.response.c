void mlQuadBezier(const float v0[3], const float v1[3], const float v2[3], float t, float result[3])
{
  float ti;

  ti=1.0f-t;
  result[0]=v0[0]*(ti*ti)+v1[0]*(2.0f*ti*t)+v2[0]*(t*t);
  result[1]=v0[1]*(ti*ti)+v1[1]*(2.0f*ti*t)+v2[1]*(t*t);
  result[2]=v0[2]*(ti*ti)+v1[2]*(2.0f*ti*t)+v2[2]*(t*t);
}
void DFT2(float *sincos, float *sintab)
{
  float tmp;
  tmp = sincos[0]+sincos[1];
  sincos[1] = sincos[0]-sincos[1];
  sincos[0] = tmp;
}
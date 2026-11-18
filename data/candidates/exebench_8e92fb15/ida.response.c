void __cdecl cylinder(float r, float h, float *csa, float *tsa, float *vol)
{
  *csa = (float)((float)((float)(2.0 * r) * h) * 22.0) / 7.0;
  *tsa = (float)((float)((float)(2.0 * r) * (float)(h + r)) * 22.0) / 7.0;
  *vol = (float)((float)((float)(r * r) * h) * 22.0) / 7.0;
}
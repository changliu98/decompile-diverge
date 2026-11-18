void cylinder(float r, float h, float *csa, float *tsa, float *vol)
{
  *csa = (float)(2 * r * h * 22.0) / 7.0;
  *tsa = (float)(2 * r * (r + h) * 22.0) / 7.0;
  *vol = (float)(r * r * h * 22.0) / 7.0;
}
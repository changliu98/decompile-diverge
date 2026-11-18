void scale(float *m, float xScale, float yScale, float zScale)
{
  m[0 * 4 + 0] *= xScale;
  m[1 * 4 + 0] *= xScale;
  m[2 * 4 + 0] *= xScale;
  m[3 * 4 + 0] *= xScale;
  m[0 * 4 + 1] *= yScale;
  m[1 * 4 + 1] *= yScale;
  m[2 * 4 + 1] *= yScale;
  m[3 * 4 + 1] *= yScale;
  m[0 * 4 + 2] *= zScale;
  m[1 * 4 + 2] *= zScale;
  m[2 * 4 + 2] *= zScale;
  m[3 * 4 + 2] *= zScale;
}
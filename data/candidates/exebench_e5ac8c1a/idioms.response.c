void rifft1pt(float *io, float scale)
{
  float t0 = io[1];
  float t1 = io[0] - t0;
  io[0] = (io[0] + t0) * scale;
  io[1] = t1 * scale;
}
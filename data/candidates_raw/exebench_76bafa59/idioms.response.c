void scale_vec(float *vec, float scale)
{
  float t0; float t1;
  t0 = vec[1];
  t1 = vec[0] - t0;
  vec[0] = (vec[0] + t0) * scale;
  vec[1] = t1 * scale;
}
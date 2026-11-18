void vec_scale(double *vec1, double scale, double *vec2)
{
  vec2[0] = vec1[0] * scale;
  vec2[1] = vec1[1] * scale;
  vec2[2] = vec1[2] * scale;
}
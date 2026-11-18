void geom_matvec2f(const float *m, const float *v, float *out) {
  out[0] = m[0] * v[0] + m[2] * v[1];
  out[1] = m[1] * v[0] + m[3] * v[1];
}
float vec4f_dot(const float *a, const float *b) {
  float dot;
  dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
  return dot;
}
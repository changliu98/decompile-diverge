float vector3d_dot(float *a, float *b) {
  float dot;
  dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  return dot;
}
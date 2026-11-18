float vec3DotProduct(const float* a, const float* b) {
  float dot = 0;
  dot += a[0] * b[0];
  dot += a[1] * b[1];
  dot += a[2] * b[2];
  return dot;
}
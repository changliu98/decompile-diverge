float vec4DotProduct(const float* a, const float* b) {
  float result = 0;
  result += a[0] * b[0];
  result += a[1] * b[1];
  result += a[2] * b[2];
  result += a[3] * b[3];
  return result;
}
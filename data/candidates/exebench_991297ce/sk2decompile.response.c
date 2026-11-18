void mlVectorDotProductTo(const float *a, const float *b, float *result) {
  float x = a[0] * b[0];
  float y = a[1] * b[1];
  float z = a[2] * b[2];
  *result = x + y + z;
}
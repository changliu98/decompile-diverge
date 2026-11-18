void InvMat22(float *a, float *b) {
  float det;
  det = 1.0f / (b[0] * b[3] - b[1] * b[2]);
  a[0] = b[3] * det;
  a[1] = -b[1] * det;
  a[2] = -b[2] * det;
  a[3] = b[0] * det;
}
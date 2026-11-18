void mtx3x3Transpose(float *dst, const float *src) {
  dst[0] = src[0];
  dst[4] = src[4];
  dst[8] = src[8];
  dst[1] = src[3];
  dst[3] = src[1];
  dst[2] = src[6];
  dst[6] = src[2];
  dst[5] = src[7];
  dst[7] = src[5];
}
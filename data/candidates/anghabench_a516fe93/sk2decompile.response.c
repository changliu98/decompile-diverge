void nvgTransformTranslate(float* dst, float x, float y) {
  dst[0] = 1.0f;
  dst[1] = 0.0f;
  dst[2] = 0.0f;
  dst[3] = 1.0f;
  dst[4] = x;
  dst[5] = y;
}
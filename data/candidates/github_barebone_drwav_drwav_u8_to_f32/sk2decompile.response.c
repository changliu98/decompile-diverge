void drwav_u8_to_f32(float* pOut, const unsigned char* pIn, size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (float)pIn[i] / 255.0f - 1.0f;
  }
}
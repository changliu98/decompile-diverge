void drwav_s16_to_f32(float* pOut, const drwav_int16* pIn, size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (float)pIn[i] / 32768.0f;
  }
}
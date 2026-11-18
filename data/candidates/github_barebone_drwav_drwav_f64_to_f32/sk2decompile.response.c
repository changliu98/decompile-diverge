extern void drwav_f64_to_f32(float* pOut, const double* pIn, size_t sampleCount) {
  size_t i;
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (float)pIn[i];
  }
}
void drwav_f64_to_s32(drwav_int32* pOut, const double* pIn, size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    double x = pIn[i];
    x *= 2147483648.0;
    *pOut++ = (drwav_int32)x;
  }
}
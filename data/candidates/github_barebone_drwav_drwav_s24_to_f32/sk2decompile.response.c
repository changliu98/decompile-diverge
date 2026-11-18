void drwav_s24_to_f32(float* pOut, const unsigned char* pIn, size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    unsigned int u = (unsigned int)(pIn[0]);
    unsigned int v = (unsigned int)(pIn[1]);
    unsigned int w = (unsigned int)(pIn[2]);
    int s = (u << 8) | (v << 16) | (w << 24);
    s >>= 8;
    *pOut++ = (float)(s / 8388608.0);
    pIn += 3;
  }
}
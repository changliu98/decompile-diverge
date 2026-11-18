void drwav_mulaw_to_f32(float* pOut, const unsigned char* pIn, size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    int mulaw = pIn[i];
    *pOut++ = (float)drwav__mulaw_decode_table[mulaw] / 32768.0f;
  }
}
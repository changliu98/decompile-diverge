extern void drwav_alaw_to_f32(float* pOut, const unsigned char* pIn,
                              unsigned int sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  unsigned int i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (float)drwav__g_alaw_decode_table[pIn[i]] / 32768.0f;
  }
}
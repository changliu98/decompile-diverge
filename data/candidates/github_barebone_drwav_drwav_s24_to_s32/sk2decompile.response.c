void drwav_s24_to_s32(drwav_int32* pOut, const unsigned char* pIn,
                      drwav_uint64 sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  drwav_uint64 i;
  for (i = 0; i < sampleCount; ++i) {
    unsigned int s0 = pIn[i * 3 + 0];
    unsigned int s1 = pIn[i * 3 + 1];
    unsigned int s2 = pIn[i * 3 + 2];
    *pOut++ = (s0 << 8) | (s1 << 16) | (s2 << 24);
  }
}
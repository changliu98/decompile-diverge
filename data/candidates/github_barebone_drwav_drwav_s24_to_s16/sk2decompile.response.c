void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t count) {
  size_t i;
  for (i = 0; i < count; ++i) {
    unsigned int s0 = pIn[i * 3 + 0];
    unsigned int s1 = pIn[i * 3 + 1];
    unsigned int s2 = pIn[i * 3 + 2];
    pOut[i] = (s0 << 8) | (s1 << 16) | (s2 << 24);
    pOut[i] >>= 16;
  }
}
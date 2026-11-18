void drwav_alaw_to_s32(drwav_int32* pOut, const unsigned char* pIn,
                       size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = sAlawToS32Table[pIn[i]] << 16;
  }
}
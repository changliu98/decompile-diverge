void drwav_mulaw_to_s32(drwav_int32* pOut, const unsigned char* pIn,
                        size_t sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = gMuLawDecodeTable[pIn[i]] << 16;
  }
}
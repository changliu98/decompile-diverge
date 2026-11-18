void drwav_s16_to_s32(drwav_int32* pOut, const drwav_int16* pIn,
                      size_t totalSampleCount) {
  size_t i;
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  for (i = 0; i < totalSampleCount; ++i) {
    *pOut++ = (drwav_int32)(pIn[i] << 16);
  }
}
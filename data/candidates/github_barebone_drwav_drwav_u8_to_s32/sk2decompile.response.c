void drwav_u8_to_s32(drwav_int32* pOut, const drwav_uint8* pIn,
                     drwav_uint64 sampleCount) {
  drwav_uint64 i;
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (pIn[i] - 128) << 24;
  }
}
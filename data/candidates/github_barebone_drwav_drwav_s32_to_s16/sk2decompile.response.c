void drwav_s32_to_s16(drwav_int16* pOut, const drwav_int32* pIn,
                      size_t totalSampleCount) {
  size_t i;
  for (i = 0; i < totalSampleCount; ++i) {
    drwav_int32 s = pIn[i];
    pOut[i] = (drwav_int16)(s >> 16);
  }
}
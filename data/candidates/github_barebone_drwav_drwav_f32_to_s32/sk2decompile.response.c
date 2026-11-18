void drwav_f32_to_s32(drwav_int32* pOut, const float* pIn,
                      drwav_uint64 sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  drwav_uint64 i;
  for (i = 0; i < sampleCount; ++i) {
    *pOut++ = (drwav_int32)(pIn[i] * 2147483647.0f);
  }
}
void drwav_s32_to_f32(float* pOut, const drwav_int32* pIn,
                      drwav_uint64 sampleCount) {
  if (pOut == NULL || pIn == NULL) {
    return;
  }
  for (drwav_uint64 i = 0; i < sampleCount; ++i) {
    *pOut++ = (float)(pIn[i] / 2147483648.0);
  }
}
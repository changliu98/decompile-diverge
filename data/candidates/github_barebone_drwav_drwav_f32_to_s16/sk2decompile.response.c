void drwav_f32_to_s16(drwav_int16* pOut, const float* pIn, size_t sampleCount) {
  size_t i;
  for (i = 0; i < sampleCount; ++i) {
    float f = pIn[i];
    f = (f < -1.0f) ? -1.0f : (f > 1.0f) ? 1.0f : f;
    f = (f + 1.0f) * 32767.5f;
    pOut[i] = (drwav_int16)((int)f + 32768);
  }
}
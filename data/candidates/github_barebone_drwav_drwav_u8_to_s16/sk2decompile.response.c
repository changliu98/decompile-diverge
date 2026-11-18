void drwav_u8_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t count) {
  size_t i;
  for (i = 0; i < count; ++i) {
    drwav_uint8 u8 = pIn[i];
    pOut[i] = (u8 << 8) + 32768;
  }
}
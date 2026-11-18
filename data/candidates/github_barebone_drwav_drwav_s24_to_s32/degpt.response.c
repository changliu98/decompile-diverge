void drwav_s24_to_s32(drwav_int32 *pOut,drwav_uint8 *pIn,size_t sampleCount)

{
  drwav_int32 sample32;
  uint s2;
  uint s1;
  uint s0;
  size_t i;
  size_t sampleCount_local;
  drwav_uint8 *pIn_local;
  drwav_int32 *pOut_local;
  
  if ((pOut != (drwav_int32 *)0x0) && (pIn != (drwav_uint8 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (uint)pIn[i * 3] << 8 | (uint)pIn[i * 3 + 1] << 0x10 |
                    (uint)pIn[i * 3 + 2] << 0x18;
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
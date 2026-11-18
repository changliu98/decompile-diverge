void drwav_s16_to_s32(drwav_int32 *pOut,drwav_int16 *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  drwav_int16 *pIn_local;
  drwav_int32 *pOut_local;
  
  if ((pOut != (drwav_int32 *)0x0) && (pIn != (drwav_int16 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (int)pIn[i] << 0x10;
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
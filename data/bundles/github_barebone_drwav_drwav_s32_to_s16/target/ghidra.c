void drwav_s32_to_s16(drwav_int16 *pOut,drwav_int32 *pIn,size_t sampleCount)

{
  int x;
  size_t i;
  int r;
  size_t sampleCount_local;
  drwav_int32 *pIn_local;
  drwav_int16 *pOut_local;
  
  for (i = 0; i < sampleCount; i = i + 1) {
    pOut[i] = (drwav_int16)((uint)pIn[i] >> 0x10);
  }
  return;
}
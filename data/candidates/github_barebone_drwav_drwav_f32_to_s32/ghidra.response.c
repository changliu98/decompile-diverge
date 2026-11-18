void drwav_f32_to_s32(drwav_int32 *pOut,float *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  float *pIn_local;
  drwav_int32 *pOut_local;
  
  if ((pOut != (drwav_int32 *)0x0) && (pIn != (float *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (int)(DAT_00114098 * pIn[i]);
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
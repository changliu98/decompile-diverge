void drwav_s32_to_f32(float *pOut,drwav_int32 *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  drwav_int32 *pIn_local;
  float *pOut_local;
  
  if ((pOut != (float *)0x0) && (pIn != (drwav_int32 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (float)((double)pIn[i] / DAT_00114038);
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
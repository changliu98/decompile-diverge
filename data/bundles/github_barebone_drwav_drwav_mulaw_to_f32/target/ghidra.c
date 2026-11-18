void drwav_mulaw_to_f32(float *pOut,drwav_uint8 *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  drwav_uint8 *pIn_local;
  float *pOut_local;
  
  if ((pOut != (float *)0x0) && (pIn != (drwav_uint8 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (float)(int)(short)g_drwavMulawTable[pIn[i]] / DAT_00114094;
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
void drwav_alaw_to_s32(drwav_int32 *pOut,drwav_uint8 *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  drwav_uint8 *pIn_local;
  drwav_int32 *pOut_local;
  
  if ((pOut != (drwav_int32 *)0x0) && (pIn != (drwav_uint8 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (int)(short)g_drwavAlawTable[pIn[i]] << 0x10;
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
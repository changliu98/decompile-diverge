void drwav_s24_to_f32(float *pOut,drwav_uint8 *pIn,size_t sampleCount)

{
  drwav_uint32 c;
  drwav_uint32 b;
  drwav_uint32 a;
  double x;
  size_t i;
  size_t sampleCount_local;
  drwav_uint8 *pIn_local;
  float *pOut_local;
  
  if ((pOut != (float *)0x0) && (pIn != (drwav_uint8 *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (float)(DAT_00114030 *
                           (double)((int)((uint)pIn[i * 3] << 8 | (uint)pIn[i * 3 + 1] << 0x10 |
                                         (uint)pIn[i * 3 + 2] << 0x18) >> 8));
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
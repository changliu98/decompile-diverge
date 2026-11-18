void drwav_s24_to_s16(drwav_int16 *pOut,drwav_uint8 *pIn,size_t sampleCount)

{
  int x;
  size_t i;
  int r;
  size_t sampleCount_local;
  drwav_uint8 *pIn_local;
  drwav_int16 *pOut_local;
  
  for (i = 0; i < sampleCount; i = i + 1) {
    pOut[i] = (ushort)pIn[i * 3 + 1] | (ushort)(((uint)pIn[i * 3 + 2] << 0x18) >> 0x10);
  }
  return;
}
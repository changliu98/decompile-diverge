void drwav_f32_to_s16(drwav_int16 *pOut,float *pIn,size_t sampleCount)

{
  float local_40;
  float local_3c;
  float c;
  float x;
  size_t i;
  int r;
  size_t sampleCount_local;
  float *pIn_local;
  drwav_int16 *pOut_local;
  
  for (i = 0; i < sampleCount; i = i + 1) {
    local_40 = pIn[i];
    if (DAT_00114080 <= local_40) {
      if (DAT_00114084 < local_40) {
        local_40 = DAT_00114084;
      }
      local_3c = local_40;
    }
    else {
      local_3c = DAT_00114080;
    }
    pOut[i] = (short)(int)(DAT_00114088 * (DAT_00114084 + local_3c)) + -0x8000;
  }
  return;
}
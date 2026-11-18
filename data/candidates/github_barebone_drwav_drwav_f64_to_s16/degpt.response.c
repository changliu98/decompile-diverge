void drwav_f64_to_s16(drwav_int16 *pOut,double *pIn,size_t sampleCount)

{
  double local_50;
  double local_48;
  double c;
  double x;
  size_t i;
  int r;
  size_t sampleCount_local;
  double *pIn_local;
  drwav_int16 *pOut_local;
  
  for (i = 0; i < sampleCount; i = i + 1) {
    local_50 = pIn[i];
    if (DAT_00114018 <= local_50) {
      if (DAT_00114020 < local_50) {
        local_50 = DAT_00114020;
      }
      local_48 = local_50;
    }
    else {
      local_48 = DAT_00114018;
    }
    pOut[i] = (short)(int)(DAT_00114028 * (DAT_00114020 + local_48)) + -0x8000;
  }
  return;
}
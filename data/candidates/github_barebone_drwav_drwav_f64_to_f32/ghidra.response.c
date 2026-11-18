void drwav_f64_to_f32(float *pOut,double *pIn,size_t sampleCount)

{
  size_t i;
  size_t sampleCount_local;
  double *pIn_local;
  float *pOut_local;
  
  if ((pOut != (float *)0x0) && (pIn != (double *)0x0)) {
    pOut_local = pOut;
    for (i = 0; i < sampleCount; i = i + 1) {
      *pOut_local = (float)pIn[i];
      pOut_local = pOut_local + 1;
    }
  }
  return;
}
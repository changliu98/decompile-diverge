void drwav_f64_to_s16(drwav_int16* pOut, const double* pIn,
                      unsigned int totalSampleCount) {
  unsigned int i;
  for (i = 0; i < totalSampleCount; ++i) {
    double x = pIn[i];
    x = (x < -1.0) ? -1.0 : (x > 1.0) ? 1.0 : x;
    x = (x + 1.0) * 32767.5;
    pOut[i] = (drwav_int16)((int)x + 32768);
  }
}
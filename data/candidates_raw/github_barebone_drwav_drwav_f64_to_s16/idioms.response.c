void drwav_float_to_int16(short *pOut, float *pIn, unsigned long sampleCount)
{
  for (unsigned long i = 0; i < sampleCount; i++)
  {
    double d = pIn[i];
    double dAbs = d < 0 ? -d : d;
    double dClamped = dAbs > 1 ? 1 : dAbs;
    double dScaled = dClamped * (32767.5);
    double dFinal = dScaled + 32768.0;
    pOut[i] = (short)(dFinal);
  }
}
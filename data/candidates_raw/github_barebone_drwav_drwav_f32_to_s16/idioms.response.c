void drwav_float_to_int16(void *out, void *in, unsigned long sampleCount)
{
  float *pIn = (const drwav_float *)in;
  drwav_int16 *pOut = (drwav_int16 *)out;
  for (unsigned long i = 0; i < sampleCount; i++)
  {
    float f = pIn[i];
    float fAbs;
    if (f < -1.0f)
      fAbs = -1.0f;
    else if (f > 1.0f)
      fAbs = 1.0f;
    else
      fAbs = f;
    float fOut = fAbs + 1.0f;
    pOut[i] = (drwav_int16)(fOut * (float)(0x7FFF + 1)) - 0x8000;
  }
}
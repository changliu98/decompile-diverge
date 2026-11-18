void drwav_convert_int32_to_int16(short *pOut, int *pIn, unsigned long sampleCount)
{
  unsigned long i;
  for (i = 0; i < sampleCount; i++)
    pOut[i] = (short)(pIn[i] >> 16);
}
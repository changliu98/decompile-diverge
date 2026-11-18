void drwav_s32_to_s16(short *pOut, int *pIn, unsigned long sampleCount)
{
  unsigned long i;
  for (i = 0; i < sampleCount; i++)
    pOut[i] = (short)(pIn[i] >> 16);
}
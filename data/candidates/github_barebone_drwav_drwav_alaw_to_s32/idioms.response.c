void drwav_alaw_to_s32(int *pOut, unsigned char *pIn, unsigned long sampleCount)
{
  if (pOut && pIn)
  {
    for (unsigned long i = 0; i < sampleCount; i++)
    {
      *pOut++ = g_drwavAlawTable[pIn[i]] << 16;
    }
  }
}
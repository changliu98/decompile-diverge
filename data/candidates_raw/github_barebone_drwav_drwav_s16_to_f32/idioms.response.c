void drwav_float_to_int16(float *pOut, short *pIn, unsigned long sampleCount)
{
  if (pOut != ((void *)0) && pIn != ((void *)0))
  {
    for (unsigned long i = 0; i < sampleCount; i++)
    {
      *pOut++ = pIn[i] * (1.0f / (float) (0x7fff));
    }
  }
}
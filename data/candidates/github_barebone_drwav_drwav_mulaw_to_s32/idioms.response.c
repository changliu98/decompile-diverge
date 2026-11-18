void drwav_mulaw_to_s32(void *outBuffer, void *inBuffer, unsigned long sampleCount)
{
  int *out = (int *)outBuffer;
  unsigned char *in = (const unsigned char *)inBuffer;
  if (out && in)
  {
    for (unsigned long i = 0; i < sampleCount; i++)
    {
      *out++ = g_drwavMulawTable[in[i]] << 16;
    }
  }
}
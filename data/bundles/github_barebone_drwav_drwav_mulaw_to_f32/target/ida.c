void __cdecl drwav_mulaw_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  float *v3; // rax
  size_t i; // [rsp+0h] [rbp-28h]
  float *pOuta; // [rsp+18h] [rbp-10h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = (float)g_drwavMulawTable[pIn[i]] / 32768.0;
    }
  }
}
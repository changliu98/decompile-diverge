void __cdecl drwav_s16_to_f32(float *pOut, const drwav_int16 *pIn, size_t sampleCount)
{
  float *v3; // rax
  size_t i; // [rsp+0h] [rbp-20h]
  float *pOuta; // [rsp+18h] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = (float)pIn[i] * 0.000030517578;
    }
  }
}
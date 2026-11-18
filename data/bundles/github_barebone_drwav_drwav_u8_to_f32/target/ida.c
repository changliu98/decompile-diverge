void __cdecl drwav_u8_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  float *v3; // rax
  size_t i; // [rsp+4h] [rbp-20h]
  float *pOuta; // [rsp+1Ch] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = (float)(0.0078431377 * (float)pIn[i]) - 1.0;
    }
  }
}
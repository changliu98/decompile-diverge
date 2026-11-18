void __cdecl drwav_s24_to_f32(float *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  float v3; // xmm0_4
  float *v4; // rax
  size_t i; // [rsp+14h] [rbp-20h]
  float *pOuta; // [rsp+2Ch] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = 0.0000001192092895507812
         * (double)(((pIn[3 * i + 2] << 24) | (pIn[3 * i + 1] << 16) | (pIn[3 * i] << 8)) >> 8);
      v4 = pOuta++;
      *v4 = v3;
    }
  }
}
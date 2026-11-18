void __cdecl drwav_f64_to_f32(float *pOut, const double *pIn, size_t sampleCount)
{
  float v3; // xmm0_4
  float *v4; // rax
  size_t i; // [rsp+0h] [rbp-20h]
  float *pOuta; // [rsp+18h] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pIn[i];
      v4 = pOuta++;
      *v4 = v3;
    }
  }
}
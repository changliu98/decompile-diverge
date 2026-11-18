void __cdecl drwav_s16_to_s32(drwav_int32 *pOut, const drwav_int16 *pIn, size_t sampleCount)
{
  drwav_int32 *v3; // rax
  size_t i; // [rsp+0h] [rbp-20h]
  drwav_int32 *pOuta; // [rsp+18h] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = pIn[i] << 16;
    }
  }
}
void __cdecl drwav_s24_to_s32(drwav_int32 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  int *v3; // rax
  size_t i; // [rsp+10h] [rbp-20h]
  drwav_int32 *pOuta; // [rsp+28h] [rbp-8h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = (pIn[3 * i + 2] << 24) | (pIn[3 * i + 1] << 16) | (pIn[3 * i] << 8);
    }
  }
}
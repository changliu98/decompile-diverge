void __cdecl drwav_s32_to_s16(drwav_int16 *pOut, const drwav_int32 *pIn, size_t sampleCount)
{
  size_t i; // [rsp+4h] [rbp-28h]

  for ( i = 0LL; i < sampleCount; ++i )
    pOut[i] = HIWORD(pIn[i]);
}
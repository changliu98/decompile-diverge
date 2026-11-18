void __cdecl drwav_u8_to_s16(drwav_int16 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  size_t i; // [rsp+4h] [rbp-28h]

  for ( i = 0LL; i < sampleCount; ++i )
    pOut[i] = (pIn[i] << 8) + 0x8000;
}
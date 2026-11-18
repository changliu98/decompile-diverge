void __cdecl drwav_s24_to_s16(drwav_int16 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  size_t i; // [rsp+4h] [rbp-28h]

  for ( i = 0LL; i < sampleCount; ++i )
    pOut[i] = (unsigned int)((pIn[3 * i + 2] << 24) | (pIn[3 * i + 1] << 16) | (pIn[3 * i] << 8)) >> 16;
}
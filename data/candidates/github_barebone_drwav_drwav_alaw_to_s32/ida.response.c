void __cdecl drwav_alaw_to_s32(drwav_int32 *pOut, const drwav_uint8 *pIn, size_t sampleCount)
{
  drwav_int32 *v3; // rax
  size_t i; // [rsp+0h] [rbp-28h]
  drwav_int32 *pOuta; // [rsp+18h] [rbp-10h]

  pOuta = pOut;
  if ( pOut && pIn )
  {
    for ( i = 0LL; i < sampleCount; ++i )
    {
      v3 = pOuta++;
      *v3 = g_drwavAlawTable[pIn[i]] << 16;
    }
  }
}
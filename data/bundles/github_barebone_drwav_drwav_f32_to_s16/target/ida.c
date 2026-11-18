void __cdecl drwav_f32_to_s16(drwav_int16 *pOut, const float *pIn, size_t sampleCount)
{
  float v3; // [rsp+0h] [rbp-38h]
  float v4; // [rsp+4h] [rbp-34h]
  float x; // [rsp+Ch] [rbp-2Ch]
  size_t i; // [rsp+10h] [rbp-28h]

  for ( i = 0LL; i < sampleCount; ++i )
  {
    x = pIn[i];
    if ( x >= -1.0 )
    {
      if ( x <= 1.0 )
        v3 = pIn[i];
      else
        v3 = 1.0;
      v4 = v3;
    }
    else
    {
      v4 = -1.0;
    }
    pOut[i] = (int)(float)(32767.5 * (float)(v4 + 1.0)) + 0x8000;
  }
}
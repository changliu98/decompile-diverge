void __cdecl drwav_f64_to_s16(drwav_int16 *pOut, const double *pIn, size_t sampleCount)
{
  double v3; // [rsp+0h] [rbp-48h]
  double v4; // [rsp+8h] [rbp-40h]
  double x; // [rsp+18h] [rbp-30h]
  size_t i; // [rsp+20h] [rbp-28h]

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
    pOut[i] = (int)(32767.5 * (v4 + 1.0)) + 0x8000;
  }
}
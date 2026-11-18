float __cdecl LerpAngle(float from, float to, float frac)
{
  float toa; // [rsp+8h] [rbp-8h]

  toa = to;
  if ( (float)(to - from) > 180.0 )
    toa = to - 360.0;
  if ( (float)(toa - from) < -180.0 )
    toa = toa + 360.0;
  return (float)(frac * (float)(toa - from)) + from;
}
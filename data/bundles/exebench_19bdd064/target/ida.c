void __cdecl ComputeAndOrientation(float heading, float *euler, float *result)
{
  float roll; // [rsp+0h] [rbp-20h]
  float pitch; // [rsp+4h] [rbp-1Ch]

  *result = heading;
  pitch = *euler;
  roll = euler[1];
  if ( *euler < 0.0 )
    pitch = pitch + 360.0;
  if ( roll < 0.0 )
    roll = roll + 360.0;
  if ( roll > 90.0 && roll < 270.0 )
  {
    pitch = pitch - 180.0;
    if ( pitch < 0.0 )
      pitch = pitch + 360.0;
  }
  if ( pitch > 180.0 )
    result[1] = 360.0 - pitch;
  else
    *((_DWORD *)result + 1) = _mm_cvtsi128_si32((__m128i)LODWORD(pitch)) ^ 0x80000000;
  if ( roll < 0.0 || roll > 90.0 )
  {
    if ( roll <= 90.0 || roll >= 270.0 )
      result[2] = roll - 360.0;
    else
      result[2] = 180.0 - roll;
  }
  else
  {
    result[2] = roll;
  }
}
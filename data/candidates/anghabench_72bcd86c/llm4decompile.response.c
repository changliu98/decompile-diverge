float LerpAngle( float from, float to, float frac )
{
  float a;

  if( to - from > 180 )
    to -= 360;
  if( to - from < -180 )
    to += 360;

  a = from + ( to - from ) * frac;

  return a;
}
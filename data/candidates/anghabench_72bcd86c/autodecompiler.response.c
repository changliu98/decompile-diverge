float LerpAngle( float a2, float a1, const float frac ) {
 if ( a1 - a2 > 180 ) {
  a1 -= 360;
 }
 if ( a1 - a2 < -180 ) {
  a1 += 360;
 }
 return a2 + frac * ( a1 - a2 );
}
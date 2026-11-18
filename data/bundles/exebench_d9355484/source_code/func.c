#include <math.h>

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
 float min, max, delta;
 min = ((r<(g<b? g : b)? r : (g<b? g : b)));
 max = ((r>(g>b? g : b)? r : (g>b? g : b)));
 *v = max;
 delta = max - min;
 if( max != 0 )
  *s = delta / max;
 else {

  *s = 0;
  *h = -1;
  return;
 }
 if( r == max )
  *h = ( g - b ) / delta;
 else if( g == max )
  *h = 2 + ( b - r ) / delta;
 else
  *h = 4 + ( r - g ) / delta;
 *h *= 60;
 if( *h < 0 )
  *h += 360;
}

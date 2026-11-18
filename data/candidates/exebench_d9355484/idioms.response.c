void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
  float min; float max; float delta;
  if ( b < g )
    min = b;
  else
    min = g;
  if ( (min < r) )
    min = r;
  if ( b > g )
    max = b;
  else
    max = g;
  if ( r > max )
    max = r;
  if ( r < min )
    min = r;
  *v = max;
  delta = max - min;
  if ( *v != 0 )
    *s = delta / *v;
  else
    *s = 0;
  if ( r == *v )
    *h = (g - b) / delta;
  else if ( g == *v )
    *h = 2.0 + (b - r) / delta;
  else
    *h = 4.0 + (r - g) / delta;
  *h *= 60.0;
  if ( *h < 0 )
    *h += 360.0;
}
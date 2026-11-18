void __cdecl RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
  float min;
  float max;

  // Calculate the minimum component among r, g, b
  if ( b <= g )
    min = b;
  else
    min = g;
  if ( r < min )
    min = r;

  // Calculate the maximum component among r, g, b
  if ( g <= b )
    max = b;
  else
    max = g;
  if ( r > max )
    max = r;

  *v = max;
  float delta = max - min;

  if ( max == 0.0f )
  {
    *s = 0.0f;
    *h = -1.0f;
  }
  else
  {
    *s = delta / max;
    
    if ( r == max )
    {
      *h = (g - b) / delta;
    }
    else if ( g == max )
    {
      *h = (b - r) / delta + 2.0f;
    }
    else
    {
      *h = (r - g) / delta + 4.0f;
    }
    
    *h *= 60.0f;
    if ( *h < 0.0f )
      *h += 360.0f;
  }
}
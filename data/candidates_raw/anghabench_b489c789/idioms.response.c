void set_pixel(unsigned short *pixel, int max, int intensity, int limit)
{
  if ( *pixel > max )
    *pixel = limit;
  else
    *pixel += intensity;
}
double __cdecl func0(int radius, int angle)
{
  if ( angle < 360 )
    return 3.142857142857143 * (double)radius * (double)radius * ((double)angle / 360.0);
  else
    return -1.0;
}
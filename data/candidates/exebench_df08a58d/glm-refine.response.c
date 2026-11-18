float __cdecl abs_sf(float *p)
{
  unsigned int bits = *(unsigned int *)p;
  bits &= 0x7FFFFFFF; // Clear the sign bit to get the absolute value of a float
  return *(float *)&bits;
}
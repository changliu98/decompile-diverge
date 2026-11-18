void __cdecl update16(uint16_t *target, int max, int intensity, int limit)
{
  if ( *target > max )
    *target = limit;
  else
    *target += intensity;
}
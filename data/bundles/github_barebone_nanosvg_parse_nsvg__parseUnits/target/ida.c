int __cdecl nsvg__parseUnits(const char *units)
{
  if ( *units == 112 && units[1] == 120 )
    return 1;
  if ( *units == 112 && units[1] == 116 )
    return 2;
  if ( *units == 112 && units[1] == 99 )
    return 3;
  if ( *units == 109 && units[1] == 109 )
    return 4;
  if ( *units == 99 && units[1] == 109 )
    return 5;
  if ( *units == 105 && units[1] == 110 )
    return 6;
  if ( *units == 37 )
    return 7;
  if ( *units == 101 && units[1] == 109 )
    return 8;
  if ( *units == 101 && units[1] == 120 )
    return 9;
  return 0;
}
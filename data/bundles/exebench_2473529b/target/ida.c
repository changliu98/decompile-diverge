void __cdecl normalize_angle(double *angle)
{
  while ( *angle > 6.2831853 )
    *angle = *angle - 6.2831853;
  while ( *angle < 0.0 )
    *angle = *angle + 6.2831853;
}
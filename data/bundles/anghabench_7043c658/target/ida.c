unsigned __int16 __cdecl calc_speed(unsigned __int16 *spds, int num, unsigned __int16 dflt)
{
  int i; // [rsp+0h] [rbp-14h]
  unsigned __int16 speed; // [rsp+4h] [rbp-10h]

  speed = 0;
  for ( i = 0; i < num; ++i )
  {
    if ( speed < (int)spds[i] )
      speed = spds[i];
  }
  if ( !speed )
    return dflt;
  return speed;
}
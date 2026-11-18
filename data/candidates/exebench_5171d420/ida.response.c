int __cdecl inverse_rot(const int *m, int *o)
{
  if ( !m[1] || !m[2] )
    return 1;
  *o = 0;
  o[1] = 0x100000 / m[2];
  o[2] = 0x100000 / m[1];
  o[3] = 0;
  o[4] = -(o[2] * m[5]) / 1024;
  o[5] = -(o[1] * m[4]) / 1024;
  return 0;
}
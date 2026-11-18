void __cdecl swap_int(int *pi)
{
  unsigned __int8 *p = (unsigned __int8 *)pi;
  unsigned __int8 t;

  // Swap byte 0 and byte 3
  t = p[0];
  p[0] = p[3];
  p[3] = t;

  // Swap byte 1 and byte 2
  t = p[1];
  p[1] = p[2];
  p[2] = t;
}
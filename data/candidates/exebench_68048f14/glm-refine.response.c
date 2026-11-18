void __cdecl vinv(double *v)
{
  // Invert the sign of three contiguous doubles by flipping their sign bits
  v[0] = -v[0];
  v[1] = -v[1];
  v[2] = -v[2];
}
int __cdecl shape_tria3(double *L, double *N)
{
  N[0] = L[0];
  N[1] = L[1];
  N[2] = 1.0 - L[0] - L[1];
  return 0;
}
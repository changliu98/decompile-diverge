void __cdecl GivensApply(double c, double s, double *z_1, double *z_2)
{
  double w = *z_1 * c + *z_2 * s;
  *z_2 = -*z_1 * s + *z_2 * c;
  *z_1 = w;
}
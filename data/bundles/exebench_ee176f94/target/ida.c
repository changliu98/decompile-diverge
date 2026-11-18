int __cdecl exactO(const double z, double *TT, double *Tm, double *qice, double *qbed, double *bmelt)
{
  double v6; // xmm0_8

  *Tm = 26781300.0 * -0.00000007900000000000001 + 273.15;
  *qice = -2.1 * (223.15 - *Tm) / 3000.0;
  *qbed = 0.042;
  *bmelt = (0.042 - *qice) / 303940000.0;
  if ( z <= 3000.0 )
  {
    if ( z < 0.0 )
      v6 = z * -0.014 + *Tm;
    else
      v6 = (223.15 - *Tm) * (z / 3000.0) + *Tm;
    *TT = v6;
  }
  else
  {
    *TT = 223.15;
  }
  return 0;
}
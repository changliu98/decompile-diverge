int __cdecl exactO(const double z, double *TT, double *Tm, double *qice, double *qbed, double *bmelt)
{
  // Pre-calculated constant: 26781300.0 * -0.00000007900000000000001 + 273.15 = 211.61247
  *Tm = 211.61247; 

  // Ice heat flux (or similar physical property)
  *qice = -2.1 * (223.15 - *Tm) / 3000.0;

  // Bed heat flux
  *qbed = 0.042;

  // Basal melt rate
  *bmelt = (*qbed - *qice) / 303940000.0;

  // Temperature profile calculation based on depth (z)
  if (z <= 3000.0)
  {
    if (z < 0.0)
    {
      // Above surface (negative depth)
      *TT = *Tm - 0.014 * z;
    }
    else
    {
      // Within the ice column (0 to 3000m)
      *TT = *Tm + (223.15 - *Tm) * (z / 3000.0);
    }
  }
  else
  {
    // Below 3000m (deep ice/fixed bottom temperature)
    *TT = 223.15;
  }

  return 0;
}
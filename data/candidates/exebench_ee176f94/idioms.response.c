int exactO(double h, double *TT, double *Tm, double *qice, double *qbed, double *bmelt)
{
  *Tm = 273.15 - 7.9e-8 * h * 2.678e12;
  *qice = -2.1 * (223.15 - *Tm)/3e3;
  *qbed = 0.042;
  *bmelt = (*qbed - *qice)/1e-3/3e9;
  if (h > 3e3)
    *TT = 223.15;
  else if (h >= 0)
    *TT = *Tm + h/3e3 * (223.15 - *Tm);
  else
    *TT = *Tm - h/1e2 * 0.014;
  return 0;
}
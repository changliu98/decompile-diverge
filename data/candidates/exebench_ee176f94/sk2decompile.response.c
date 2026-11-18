int exactO(double h, double *T, double *T0, double *dTdh, double *d2Tdh2,
           double *d3Tdh3) {
  *T0 = 26781300.0 * -7.9e-10 + 273.15;
  *dTdh = -2.1 * (223.15 - *T0) / 3000.0;
  *d2Tdh2 = 0.042;
  *d3Tdh3 = (*d2Tdh2 - *dTdh) / 3.0394e8;
  if (h > 3000.0)
    *T = 223.15;
  else if (h < 0.0)
    *T = *T0 - 0.014 * h;
  else
    *T = *T0 + (223.15 - *T0) * (h / 3000.0);
  return (0);
}
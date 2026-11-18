void geom_matvec4d(const double m[16], const double u[4], double v[4])
{
  int i;
  for (i = 0; i < 4; i++) {
    v[i] = m[i] * u[0] + m[4 + i] * u[1] + m[8 + i] * u[2] + m[12 + i] * u[3];
  }
}
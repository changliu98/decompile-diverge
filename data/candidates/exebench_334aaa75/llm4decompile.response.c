void phi2D_lin(double xsi, double eta, double phi[])
{
  phi[0] = (1.0 - xsi) * (1.0 - eta);
  phi[1] = xsi * (1.0 - eta);
  phi[2] = xsi * eta;
  phi[3] = (1.0 - xsi) * eta;
}
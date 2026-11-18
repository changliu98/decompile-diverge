void phi2D_lin(double xsi,double eta,double *phi)

{
  double *phi_local;
  double eta_local;
  double xsi_local;
  
  *phi = (DAT_00102010 - xsi) * (DAT_00102010 - eta);
  phi[1] = xsi * (DAT_00102010 - eta);
  phi[2] = xsi * eta;
  phi[3] = (DAT_00102010 - xsi) * eta;
  return;
}
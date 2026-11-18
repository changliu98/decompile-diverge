void phi2D_lin(double r, double s, double *phi) {
  phi[0] = (1.0 - r) * (1.0 - s);
  phi[1] = r * (1.0 - s);
  phi[2] = r * s;
  phi[3] = (1.0 - r) * s;
}
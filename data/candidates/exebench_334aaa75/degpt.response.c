void phi2D_lin(double xi, double eta, double *phi)
{
  // Compute shape function values for a 2D linear quadrilateral element
  // using natural coordinates (xsi, eta) in the range [-1, 1]
  
  // Shape function for node 0 (bottom-left corner)
  *phi = (DAT_00102010 - xsi) * (DAT_00102010 - eta);
  
  // Shape function for node 1 (bottom-right corner)
  phi[1] = xsi * (DAT_00102010 - eta);
  
  // Shape function for node 2 (top-right corner)
  phi[2] = xsi * eta;
  
  // Shape function for node 3 (top-left corner)
  phi[3] = (DAT_00102010 - xsi) * eta;
}
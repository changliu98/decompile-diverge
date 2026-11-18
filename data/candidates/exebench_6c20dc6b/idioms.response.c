void getTransf(struct s_par *par, double *D, double *N)
{
  D[0] = par->a11;
  D[1] = par->a12;
  D[2] = 0.;
  D[3] = 0.;
  D[4] = par->a22;
  D[5] = 0.;
  D[6] = par->a11 - par->a11 * par->a11;
  D[7] = -par->a12 * par->a11;
  D[8] = 1.;
  N[0] = 1./par->a11;
  N[1] = -1./par->a11 * par->a12 / par->a22;
  N[2] = 0.;
  N[3] = 0.;
  N[4] = 1./par->a22;
  N[5] = 0.;
  N[6] = -par->a12 / par->a11;
  N[7] = (par->a11 * par->a22 - par->a12 * par->a12) / par->a11 / par->a22;
  N[8] = 1.;
}
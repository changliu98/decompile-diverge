int exactC(const double *t, double *H, double *M, double *Rho, double *U, double *V, double *T, double *C, double *E)
{
  double L, B, Hela, Rhoel;
  double dRhoel_dH, dRhoel_dHela, dRhoel_dM, dRhoel_dT, dRhoel_dU, dRhoel_dV;

  *H = 3000.0;
  *M = 1e6;
  *Rho = 0.9*(*M);
  *Rhoel = 1.0e-10;
  *U = (*H)/1.5;
  *V = 9.0*(*U)/((*Rhoel)*(*M)*(*M));

  L = (*Rho)/(*M);
  *T = (*H)*(1.0 + L*L);

  *C = 513.3333333333333*(double) (*T)*(*T);

  return 0;
}
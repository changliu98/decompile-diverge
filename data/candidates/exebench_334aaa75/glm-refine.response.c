void __cdecl phi2D_lin(double xi, double eta, double *phi)
{
    phi[0] = (1.0 -  xi) * (1.0 - eta);
    phi[1] =       xi   * (1.0 - eta);
    phi[2] =       xi   *       eta  ;
    phi[3] = (1.0 -  xi) *       eta  ;
}
int shape_tria6(double par[2], double N[6])
{
    double L,M,O;

    L = par[0];
    M = par[1];
    O = 1.0e0 - L - M;

    N[0] = L*(2.0e0*L - 1.0e0);
    N[1] = 4.0e0*L*M;
    N[2] = M*(2.0e0*M - 1.0e0);
    N[3] = 4.0e0*M*O;
    N[4] = O*(2.0e0*O - 1.0e0);
    N[5] = 4.0e0*L*O;

    return 0;
}
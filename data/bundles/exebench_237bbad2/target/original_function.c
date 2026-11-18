int shape_tria6(double *L, double *N)
{
    double L1, L2, L3;


    L1 = L[0];
    L2 = L[1];
    L3 = 1.0 - L1 - L2;


    N[0] = L1*(2.0*L1 - 1.0);
    N[1] = 4.0*L1*L2;
    N[2] = L2*(2.0*L2 - 1.0);
    N[3] = 4.0*L2*L3;
    N[4] = L3*(2.0*L3 - 1.0);
    N[5] = 4.0*L1*L3;

    return 0;
}
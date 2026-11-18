#include <stdio.h>

#include <stdlib.h>

#include <math.h>

static inline void phi2D_lin(double xsi, double eta, double *phi)
{
    phi[0] = (1-xsi) * (1-eta);
    phi[1] = xsi * (1-eta);
    phi[2] = xsi * eta ;
    phi[3] = (1-xsi) * eta ;
}

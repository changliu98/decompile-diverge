void compute_matrix_T(double *g, double dx, double dy, double dz, double L)
{
 g[0] = dx;
 g[1] = dx*dy;
 g[2] = 3*dx*L;
 g[3] = dx*(3*dy*L + dx*dz);
}
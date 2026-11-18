static void quad_2_grad(double grad[2], const double g[2], const double H[3],
                        const double r[2])
{
  grad[0] = g[0] + (H[0]*r[0]+H[1]*r[1]);
  grad[1] = g[1] + (H[1]*r[0]+H[2]*r[1]);
}
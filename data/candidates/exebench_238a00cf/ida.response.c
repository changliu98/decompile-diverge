void __cdecl quad_2_grad(double *grad, const double *g, const double *H, const double *r)
{
  *grad = *g + *H * *r + H[1] * r[1];
  grad[1] = g[1] + H[1] * *r + H[2] * r[1];
}
void quad_2_grad(double *w, double *wold, double *g, double *s)
{
 w[0] = wold[0] + s[0] * g[0] + s[1] * g[1];
 w[1] = wold[1] + s[0] * g[1] + s[1] * g[2];
}
void update_test_point_dense_SAG(double *w, double *wold, double *g, double *s)
{
 w[0] = wold[0] + s[0] * g[0] + s[1] * g[1];
 w[1] = wold[1] + s[0] * g[1] + s[1] * g[2];
}
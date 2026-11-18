float bspline(int n, float *x, float xval, float *y, float *tangents)
{
  int i; int ival = n-2;
  float h; float dx;
  float h00; float h10; float h01;
  for (i = 0; i < n-2; i++)
    if (x[i+1] > xval)
    {
      ival = i;
      break;
    }
  h = x[ival+1] - x[ival];
  dx = (xval - x[ival]) / h;
  h00 = (dx * dx * dx * dx) - (3 * dx * dx * dx) + 1;
  h10 = (dx * dx * dx * dx) - (2 * dx * dx * dx) + dx;
  h01 = (3 * dx * dx * dx) - (2 * dx * dx * dx * dx);
  h01 = h01 - (dx * dx * dx);
  return (h * (tangents[ival] * h01) + y[ival] * h00 + y[ival+1] * h10);
}
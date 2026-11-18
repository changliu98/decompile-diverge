void __cdecl test_mean2(double *xymean, double *xy, int n)
{
  double xsum = 0.0;
  double ysum = 0.0;

  // The array 'xy' is an interleaved array of (x, y) pairs.
  // This loop accumulates the sum of all 'x' values.
  for (int i = 0; i < 2 * n; i += 2)
    xsum += xy[i];

  // This loop accumulates the sum of all 'y' values.
  for (int i = 0; i < 2 * n; i += 2)
    ysum += xy[i + 1];

  // Calculate the means and store them in the output array
  xymean[0] = xsum / (double)n;
  xymean[1] = ysum / (double)n;
}
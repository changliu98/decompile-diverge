void get_weights(double a, double b, double c, double d, double e, double *weights)
{
  weights[0] = 1.0 / ((a - b) * (a - c) * (a - d) * (a - e));
  weights[1] = 1.0 / ((b - a) * (b - c) * (b - d) * (b - e));
  weights[2] = 1.0 / ((c - a) * (c - b) * (c - d) * (c - e));
  weights[3] = 1.0 / ((d - a) * (d - b) * (d - c) * (d - e));
  weights[4] = 1.0 / ((e - a) * (e - b) * (e - c) * (e - d));
}
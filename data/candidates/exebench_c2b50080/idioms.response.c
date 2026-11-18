static double lagrange4(double t, double *knots, float *weights)
{
  return
    weights[0] * (t - knots[1]) * (t - knots[2]) * (t - knots[3])
    / ((knots[0] - knots[1]) * (knots[0] - knots[2]) * (knots[0] - knots[3]))
    +
    weights[1] * (t - knots[0]) * (t - knots[2]) * (t - knots[3])
    / ((knots[1] - knots[0]) * (knots[1] - knots[2]) * (knots[1] - knots[3]))
    +
    weights[2] * (t - knots[0]) * (t - knots[1]) * (t - knots[3])
    / ((knots[2] - knots[0]) * (knots[2] - knots[1]) * (knots[2] - knots[3]))
    +
    weights[3] * (t - knots[0]) * (t - knots[1]) * (t - knots[2])
    / ((knots[3] - knots[0]) * (knots[3] - knots[1]) * (knots[3] - knots[2]));
}
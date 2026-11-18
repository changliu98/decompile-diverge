void __cdecl pwm(double *series, int n, double *pwms, double A, double B, int isBeta)
{
  double sum = 0.0;
  double sum_w1 = 0.0;
  double sum_w2 = 0.0;

  // Check if A and B are both exactly 0.0
  if (A == 0.0 && B == 0.0)
  {
    for (int i = 1; i <= n; ++i)
    {
      double val = series[i - 1];
      sum += val;
      
      if (!isBeta)
      {
        double w1 = (double)(n - i);
        double w2 = w1 * (double)(n - i - 1);
        sum_w1 += val * w1;
        sum_w2 += val * w2;
      }
      else if (isBeta == 1)
      {
        double w1 = (double)(i - 1);
        double w2 = w1 * (double)(i - 2);
        sum_w1 += val * w1;
        sum_w2 += val * w2;
      }
    }
  }
  else
  {
    for (int i = 1; i <= n; ++i)
    {
      double val = series[i - 1];
      sum += val;
      
      double F = ((double)i + A) / ((double)n + B);
      
      if (!isBeta)
      {
        double w1 = 1.0 - F;
        double w2 = w1 * w1;
        sum_w1 += val * w1;
        sum_w2 += val * w2;
      }
      else if (isBeta == 1)
      {
        double w1 = F;
        double w2 = F * F;
        sum_w1 += val * w1;
        sum_w2 += val * w2;
      }
    }
  }

  // Compute Probability Weighted Moments (PWMs)
  pwms[0] = sum / (double)n;
  pwms[1] = sum_w1 / (double)n / (double)(n - 1);
  pwms[2] = sum_w2 / (double)n / (double)((n - 2) * (n - 1));
}
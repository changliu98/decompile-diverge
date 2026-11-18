static double log10(double x)
{
  double log = 1.;
  double pow = 10.;
  while (x > pow)
    {
      log += 1.;
      pow *= 10.;
    }
  return log;
}
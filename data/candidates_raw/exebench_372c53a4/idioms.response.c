int mjd2jd(double mjd, double *jd)
{
  *jd = mjd + 2400000.5;
  return 0;
}
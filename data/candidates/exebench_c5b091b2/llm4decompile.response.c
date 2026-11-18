int ctr_intersect(double z0, double z1, double zc, double *f)
{
  if((z0 - zc) * (z1 - zc) < 0.0)
    {
      *f = (zc - z0) / (z1 - z0);
      return 1;
    }
  else
    return 0;
}
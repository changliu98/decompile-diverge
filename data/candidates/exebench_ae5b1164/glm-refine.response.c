int __cdecl ctr_intersect(double z0, double z1, double zc, double *f)
{
  // Check if zc is strictly between z0 and z1.
  // The original expression `(zc > z0 == zc > z1)` evaluates to true if 
  // zc is greater than both or less than both, meaning it's outside the interval.
  // The `|| z0 == zc || z1 == zc` ensures the endpoints are excluded.
  if ((zc > z0) == (zc > z1) || z0 == zc || z1 == zc)
    return 0;

  // Linear interpolation factor (t) where the contour zc crosses the segment [z0, z1]
  *f = (zc - z0) / (z1 - z0);
  return 1;
}
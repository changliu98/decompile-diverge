int __cdecl clip(
        double *px,
        double *py,
        double *pz,
        double xmin,
        double xmax,
        double ymin,
        double ymax,
        double zmin,
        double zmax)
{
  int iClip; // [rsp+0h] [rbp-4Ch]

  iClip = 0;
  if ( xmin <= *px )
  {
    if ( *px > xmax )
    {
      *px = xmax;
      iClip = 1;
    }
  }
  else
  {
    *px = xmin;
    iClip = 1;
  }
  if ( ymin <= *py )
  {
    if ( *py > ymax )
    {
      *py = ymax;
      iClip = 1;
    }
  }
  else
  {
    *py = ymin;
    iClip = 1;
  }
  if ( zmin <= *pz )
  {
    if ( *pz > zmax )
    {
      *pz = zmax;
      return 1;
    }
  }
  else
  {
    *pz = zmin;
    return 1;
  }
  return iClip;
}
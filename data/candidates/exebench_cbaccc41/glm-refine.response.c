bool __cdecl clip(
        double *x,
        double *y,
        double *z,
        double xmin,
        double xmax,
        double ymin,
        double ymax,
        double zmin,
        double zmax)
{
  bool was_clipped = false;

  // X-axis clipping
  if (*x < xmin) {
    *x = xmin;
    was_clipped = true;
  } else if (*x > xmax) {
    *x = xmax;
    was_clipped = true;
  }

  // Y-axis clipping
  if (*y < ymin) {
    *y = ymin;
    was_clipped = true;
  } else if (*y > ymax) {
    *y = ymax;
    was_clipped = true;
  }

  // Z-axis clipping
  if (*z < zmin) {
    *z = zmin;
    return true; // Early exit preserves original semantics
  } else if (*z > zmax) {
    *z = zmax;
    return true; // Early exit preserves original semantics
  }

  return was_clipped;
}
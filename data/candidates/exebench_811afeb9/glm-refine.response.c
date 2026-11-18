int __cdecl bbox(int nV, double *vertex, double *dv)
{
  double bmin[3];
  double bmax[3];
  int i, j;

  // Handle edge case where there are no vertices
  if (nV <= 0)
    return 0;

  // Initialize min and max with the first vertex
  for (j = 0; j < 3; ++j)
  {
    bmin[j] = vertex[j];
    bmax[j] = vertex[j];
  }

  // Find the bounding box for all vertices
  for (i = 1; i < nV; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      double val = vertex[3 * i + j];
      if (bmin[j] > val)
        bmin[j] = val;
      if (val > bmax[j])
        bmax[j] = val;
    }
  }

  // Calculate the center of the bounding box
  for (j = 0; j < 3; ++j)
    dv[j] = (bmin[j] + bmax[j]) / 2.0;

  // Calculate the scale factor for each axis
  for (j = 0; j < 3; ++j)
  {
    double scale = 1.0;
    double extent = bmax[j] - bmin[j];

    // Multiply scale by 2 until scale * extent >= 1.0
    while (scale * extent < 1.0)
      scale *= 2.0;

    // Divide scale by 2 until scale * extent <= 1.0
    while (scale * extent > 1.0)
      scale /= 2.0;

    dv[j + 3] = scale;
  }

  // Sort the scales in descending order (dv[3] >= dv[4] >= dv[5])
  // This is a sorting network for 3 elements.
  if (dv[3] < dv[4])
  {
    double tmp = dv[3];
    dv[3] = dv[4];
    dv[4] = tmp;
  }
  if (dv[4] < dv[5])
  {
    double tmp = dv[4];
    dv[4] = dv[5];
    dv[5] = tmp;
  }
  if (dv[3] < dv[4])
  {
    double tmp = dv[3];
    dv[3] = dv[4];
    dv[4] = tmp;
  }

  return 0;
}
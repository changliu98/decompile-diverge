void __cdecl swap(int *p)
{
  int *pmin = p;
  int *pmax = p;
  int temp;
  int i, j;

  // 1. Find the global maximum and minimum of the 5x5 matrix
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 5; ++j)
    {
      int idx = 5 * i + j;
      if (*pmax < p[idx])
        pmax = &p[idx];
      if (*pmin > p[idx])
        pmin = &p[idx];
    }
  }

  // Place the maximum in the center (p[12])
  temp = p[12];
  p[12] = *pmax;
  *pmax = temp;

  // 2. Find the minimum, skipping the first element (p[0])
  pmin = p + 1;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 5; ++j)
    {
      if ((i != 0 || j != 0) && *pmin > p[5 * i + j])
        pmin = &p[5 * i + j];
    }
  }
  
  // Place it in the top-right corner (p[4])
  temp = *pmin;
  *pmin = p[4];
  p[4] = temp;

  // 3. Find the minimum, skipping p[0] and p[4]
  pmin = p + 1;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 5; ++j)
    {
      // Note: (i || j != 4) is evaluated as (i != 0 || j != 4)
      if ((i != 0 || j != 0) && (i != 0 || j != 4) && *pmin > p[5 * i + j])
        pmin = &p[5 * i + j];
    }
  }
  
  // Place it in the bottom-left corner (p[20])
  temp = *pmin;
  *pmin = p[20];
  p[20] = temp;

  // 4. Find the minimum, skipping p[0], p[4], and p[20]
  pmin = p + 1;
  for (i = 0; i < 5; ++i)
  {
    for (j = 0; j < 5; ++j)
    {
      // Note: Same precedence quirk applies to (i || j != 4) and (i != 4 || j)
      if ((i != 0 || j != 0) && (i != 0 || j != 4) && (i != 4 || j != 0) && *pmin > p[5 * i + j])
        pmin = &p[5 * i + j];
    }
  }
  
  // Place it in the bottom-right corner (p[24])
  temp = *pmin;
  *pmin = p[24];
  p[24] = temp;
}
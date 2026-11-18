static float interp_tri(float *table, float x, float y, int grid_scheme)
{
  double a; double b; double c; double d;
  double x1; double y1;
  if (x < 1e-5)
    x = 0.0;
  else if (x > 1 - 1e-5)
    x = 1.0;
  else
    x = x;
  if (y < 1e-5)
    y = 0.0;
  else if (y > 1 - 1e-5)
    y = 1.0;
  else
    y = y;
  if (x == 0 && y == 0)
    return table[0];
  if (x == 1 && y == 0)
    return table[1];
  if (x == 0 && y == 1)
    return table[2];
  if (x == 1 && y == 1)
    return table[3];
  if (grid_scheme > 0)
  {
    a = table[0];
    b = table[1];
    c = table[3];
    d = table[2];
  }
  else
  {
    x1 = 1 - x;
    a = table[1];
    b = table[0];
    c = table[2];
    d = table[3];
  }
  if (x >= y)
  {
    a = a;
    b = b;
    c = c;
    d = d;
  }
  else
  {
    double tmp = a;
    a = c;
    c = tmp;
    tmp = b;
    b = d;
    d = tmp;
    x1 = 1 - x1;
    y = 1 - y;
  }
  return a * (y * (1 - x1)) + b * (y * x1) + c * (y * (1 - x1)) + d * (y * x1);
}
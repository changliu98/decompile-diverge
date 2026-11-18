long fix_order(double *p)
{
  long i = 0;
  double a; double b; double c; double d;
  if (p[0]>p[1])
  {
    a = p[1];
    b = p[0];
    i = 1;
  }
  else
  {
    a = p[0];
    b = p[1];
  }
  if (p[2]>p[3])
  {
    c = p[3];
    d = p[2];
  }
  else
  {
    c = p[2];
    d = p[3];
  }
  if (a > c)
  {
    a = c;
    c = a;
    if (i == 0)
      i = 4;
  }
  else
  {
    p[0] = a;
    p[1] = c;
  }
  if (b > d)
  {
    b = d;
    d = b;
    if (i == 1)
      i = 3;
  }
  else
  {
    p[3] = d;
    p[2] = b;
    if (i == 1)
      i = 1;
  }
  if (p[1]>p[2])
  {
    c = p[1];
    p[1] = p[2];
    p[2] = c;
    if (i == 4)
      i = 2;
    if (i == 5)
      return 1;
  }
  else
  {
    if (i == 4)
      i = 1;
    if (i == 5)
      return 2;
  }
  return i;
}
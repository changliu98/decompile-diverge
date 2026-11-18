int
sort_omegas (double *x)
{
  double t;
  int order = 0;

  if (x[0] > x[1]) {
    t = x[1];
    x[1] = x[0];
    x[0] = t;
    order = 1;
  }
  else {
    t = x[0];
    x[0] = x[1];
    x[1] = t;
  }

  if (x[2] > x[3]) {
    t = x[3];
    x[3] = x[2];
    x[2] = t;
  }
  else {
    t = x[2];
    x[2] = x[3];
    x[3] = t;
  }

  if (x[0] > x[2]) {
    x[0] = x[2];
    x[1] = t;
    if (order == 0)
      order = 4;
  }
  else {
    x[0] = t;
    x[1] = x[2];
  }

  if (x[1] > x[3]) {
    x[3] = x[1];
    x[2] = t;
    if (order == 1)
      order = 3;
  }
  else {
    x[3] = t;
    x[2] = x[1];
    if (order == 1)
      order = 5;
  }

  if (x[1] > x[2]) {
    t = x[1];
    x[1] = x[2];
    x[2] = t;
    if (order == 4)
      order = 2;
    if (order == 5)
      order = 1;
  }
  else {
    if (order == 4)
      order = 1;
    if (order == 5)
      order = 2;
  }

  return order;
}
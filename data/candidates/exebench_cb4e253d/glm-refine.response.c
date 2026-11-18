long __cdecl sort_omegas(double *v)
{
  long i = 0;

  // Sort pairs (v[0], v[1]) and (v[2], v[3])
  double a, b, c, d;
  if (v[0] <= v[1]) {
    a = v[0];
    b = v[1];
  } else {
    a = v[1];
    b = v[0];
    i = 1;
  }

  if (v[2] <= v[3]) {
    c = v[2];
    d = v[3];
  } else {
    c = v[3];
    d = v[2];
  }

  // Merge the two pairs
  if (a <= c) {
    v[0] = a;
    v[1] = c;
  } else {
    v[0] = c;
    v[1] = a;
    if (!i)
      i = 4;
  }

  if (b <= d) {
    v[2] = b;
    v[3] = d;
    if (i == 1)
      i = 5;
  } else {
    v[2] = d;
    v[3] = b;
    if (i == 1)
      i = 3;
  }

  // Final swap if needed
  if (v[1] <= v[2]) {
    if (i == 4)
      i = 1;
    if (i == 5)
      return 2;
  } else {
    double tmp = v[1];
    v[1] = v[2];
    v[2] = tmp;
    if (i == 4)
      i = 2;
    if (i == 5)
      return 1;
  }

  return i;
}
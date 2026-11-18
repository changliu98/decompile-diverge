int iround(double x, int *ip)
{
  int i;
  if (x < 1.0) {
    i = 1;
    *ip = x;
  }
  else {
    i = x;
    *ip = 1;
  }
  return i;
}
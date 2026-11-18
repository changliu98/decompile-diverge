double func0(int a, int b)
{
  if (a < 0 || b < 0)
    return -1;
  double f = sqrt(3)*sqrt(3)*3.0/4.0*pow((double)a, 2.0)/b;
  return f;
}
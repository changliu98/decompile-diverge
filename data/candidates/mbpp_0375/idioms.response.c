int func0(int a, int b)
{
  int q = a / b;
  int r = a % b;
  int rmax = b + b * q;
  if (r > rmax - a)
    return rmax;
  else
    return rmax - b;
}
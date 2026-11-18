double __cdecl frexp(double x, int *exp)
{
  double sig;
  int e;
  int sign = 1;
  double xa = x;

  if (x < 0.0)
  {
    sign = -1;
    xa = -x;
  }
  else if (x == 0.0)
  {
    *exp = 0;
    return 0.0;
  }

  *exp = 0;
  e = 1;
  sig = xa;

  // Loop until 0.5 <= sig < 1.0
  while (sig >= 1.0)
  {
    e *= 2;
    ++*exp;
    sig = xa / (double)e;
  }

  return sig * (double)sign;
}
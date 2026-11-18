double
f(float *x)
{
  double t = *x;
  return __builtin_sqrt (t);
}
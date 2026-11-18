void __cdecl atmtns(const double *delta, double *v)
{
  *v = *delta + *v;
  v[1] = delta[1] + v[1];
  v[2] = delta[2] + v[2];
}
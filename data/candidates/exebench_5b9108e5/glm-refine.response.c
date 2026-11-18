void __cdecl heaviside(const double *first, const double *last, double *res)
{
  bool is_one = (*res == 1.0);
  for (const double *p = first; p <= last; ++p)
  {
    is_one = is_one && (*p >= 0.0);
    *res = (double)is_one;
  }
}
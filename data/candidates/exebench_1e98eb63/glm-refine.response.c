void __cdecl getRange(double lb, double ub, double *lower, double *upper, double new_value)
{
  *upper = fmin(ub, new_value);
  *lower = fmax(lb, new_value);
}
void getRange(double lb, double ub, double *lower, double *upper, double new_value)
{
  if (new_value < *upper)
    *upper = new_value;
  else
    *upper = ub;
  if (new_value > *lower)
    *lower = new_value;
  else
    *lower = lb;
}
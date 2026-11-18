void getRange(double lb,double ub,double *lower,double *upper,double new_value)

{
  double new_value_local;
  double *upper_local;
  double *lower_local;
  double ub_local;
  double lb_local;
  
  if (ub <= new_value) {
    *upper = ub;
  }
  else {
    *upper = new_value;
  }
  if (new_value <= lb) {
    *lower = lb;
  }
  else {
    *lower = new_value;
  }
  return;
}
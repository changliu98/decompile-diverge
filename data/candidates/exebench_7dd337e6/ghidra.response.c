void _kahan_summation_step(double new_value,double *sum,double *err,double *loc,double *tmp)

{
  double *tmp_local;
  double *loc_local;
  double *err_local;
  double *sum_local;
  double new_value_local;
  
  *loc = new_value - *err;
  *tmp = *sum + *loc;
  *err = (*tmp - *sum) - *loc;
  *sum = *tmp;
  return;
}
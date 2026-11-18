int rpn_dbl_compare(double *d1, double *d2, int *is_zero, double *zero_tolerance, double *comparison_tolerance)
{
 int result;

 *is_zero = 0;

 double d1a = fabs__bench(*d1);
 double d2a = fabs__bench(*d2);

 double min_d1_d2 = ((d1a) <= (d2a) ? (d1a) : (d2a));
 double max_d1_d2 = ((d1a) >= (d2a) ? (d1a) : (d2a));

 if (min_d1_d2 > *zero_tolerance)
 {
  result = 0;
 }
 else
 {
  double min_d1_d2_div_max_d1_d2 = min_d1_d2 / max_d1_d2;

  double min_d1_d2_div_max_d1_d2_is_zero = (min_d1_d2_div_max_d1_d2 < *comparison_tolerance);

  if (min_d1_d2_div_max_d1_d2_is_zero)
  {
   *is_zero = 1;
  }

  result = 0;
 }

 return result;
}
double rel_stddev_stats(double standard_deviation, double mean)
{
 double coefficient_of_variation = 0.0;

 if (mean != 0.0) {
  coefficient_of_variation =
   100.0 * standard_deviation / mean;
 }

 return coefficient_of_variation;
}
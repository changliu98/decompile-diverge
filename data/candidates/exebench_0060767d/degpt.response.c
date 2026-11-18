void ltr_int_make_vec(double *start_point, double *end_point, double *result_vector)
{
  // Calculate the difference between the first components of pt1 and pt2
  *result_vector = *start_point - *end_point;
  // Calculate the difference between the second components of pt1 and pt2
  result_vector[1] = start_point[1] - end_point[1];
  // Calculate the difference between the third components of pt1 and pt2
  result_vector[2] = start_point[2] - end_point[2];
}
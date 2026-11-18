void FindDivDiff4Coeff(double point_a, double point_b, double point_c, double point_d, double point_e, double *divided_differences)
{
  // Calculate the 4th order divided difference coefficient for point 'a'
  *divided_differences = DAT_00102010 / ((point_a - point_b) * (point_a - point_c) * (point_a - point_d) * (point_a - point_e));
  // Calculate the 4th order divided difference coefficient for point 'b'
  divided_differences[1] = DAT_00102010 / ((point_b - point_a) * (point_b - point_c) * (point_b - point_d) * (point_b - point_e));
  // Calculate the 4th order divided difference coefficient for point 'c'
  divided_differences[2] = DAT_00102010 / ((point_c - point_a) * (point_c - point_b) * (point_c - point_d) * (point_c - point_e));
  // Calculate the 4th order divided difference coefficient for point 'd'
  divided_differences[3] = DAT_00102010 / ((point_d - point_a) * (point_d - point_b) * (point_d - point_c) * (point_d - point_e));
  // Calculate the 4th order divided difference coefficient for point 'e'
  divided_differences[4] = DAT_00102010 / ((point_e - point_a) * (point_e - point_b) * (point_e - point_c) * (point_e - point_d));
}
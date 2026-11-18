// Converts fractional coordinates (lamda) to Cartesian coordinates (x)
// using the transformation matrix h and box lower bounds (boxlo).
// x = h * lamda + boxlo
void lamda2x(double *fractional_coords, double *cartesian_coords, double *transformation_matrix, double *box_lower_bounds)
{
  // Calculate x component: linear combination of lamda components using h matrix elements, offset by boxlo[0]
  *cartesian_coords = transformation_matrix[4] * fractional_coords[2] + *transformation_matrix * *fractional_coords + transformation_matrix[5] * fractional_coords[1] + *box_lower_bounds;
  
  // Calculate y component: linear combination of lamda components using h matrix elements, offset by boxlo[1]
  cartesian_coords[1] = transformation_matrix[1] * fractional_coords[1] + transformation_matrix[3] * fractional_coords[2] + box_lower_bounds[1];
  
  // Calculate z component: linear combination of lamda components using h matrix elements, offset by boxlo[2]
  cartesian_coords[2] = transformation_matrix[2] * fractional_coords[2] + box_lower_bounds[2];
}
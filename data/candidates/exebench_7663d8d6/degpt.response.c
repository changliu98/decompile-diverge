void treemove(double *bounds, double step, int direction)
{
  // If the least significant bit of d is 0, subtract s from bb[3]
  // Otherwise, add s to *bb (which is bb[0])
  if ((direction & 1U) == 0) {
    bounds[3] = bounds[3] - step;
  }
  else {
    *bounds = step + *bounds;
  }
  // If the second bit of d is 0, subtract s from bb[4]
  // Otherwise, add s to bb[1]
  if ((direction & 2U) == 0) {
    bounds[4] = bounds[4] - step;
  }
  else {
    bounds[1] = step + bounds[1];
  }
  // If the third bit of d is 0, subtract s from bb[5]
  // Otherwise, add s to bb[2]
  if ((direction & 4U) == 0) {
    bounds[5] = bounds[5] - step;
  }
  else {
    bounds[2] = step + bounds[2];
  }
}
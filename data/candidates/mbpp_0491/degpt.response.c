// Calculates a geometric series sum scaled by 'a' and adjusted by constant DAT_00102008
// Formula: a * (DAT_00102008 - r^n) / (DAT_00102008 - r)
// Parameters:
//   a - scaling factor
//   n - exponent for r
//   r - base of the geometric progression
// Returns: computed value of the geometric series expression
double func0(double a, int n, double r)
{
  // Compute and return the result using the geometric series formula
  return (a * (CONSTANT - pow(r, (double)n)) / (CONSTANT - r));
}
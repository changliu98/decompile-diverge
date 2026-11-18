// Calculates the sum of an arithmetic sequence and returns it as a double.
// Parameters:
//   a - the first term of the sequence
//   n - the number of terms
//   d - the common difference between consecutive terms
// Returns:
//   The sum of the arithmetic sequence divided by the constant DAT_00102008.
double func0(int first_term, int num_terms, int common_difference)
{
  // Compute the sum of the arithmetic sequence using the formula: n/2 * (2a + (n-1)d)
  // Multiply by 2 to avoid floating-point division until the final step, then divide by DAT_00102008.
  return (double)(num_terms * (first_term * 2 + (num_terms + -1) * common_difference)) / DAT_00102008;
}
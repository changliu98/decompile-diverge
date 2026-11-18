char * func0(int lhs, int rhs, int multiplier)
{
  // Check if the equation b * 2 * b == a * 9 * c holds true
  if (rhs * 2 * rhs == lhs * 9 * multiplier) {
    // Return "Yes" if the condition is met
    return "Yes";
  }
  else {
    // Return "No" if the condition is not met
    return "No";
  }
}
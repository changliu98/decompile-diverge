// Computes the superfactorial of n
// The superfactorial of n is the product of the first n factorials
// Returns the superfactorial of n
longlong func0(int n)
{
  longlong superfactorial = 1; // Stores the cumulative product of factorials (superfactorial)
  longlong factorial = 1;  // Stores the current factorial value
  for (int i = 1; i <= n; i++) {
    factorial *= i;        // Update fact to be i!
    superfactorial *= factorial;    // Multiply bfact by i! to accumulate the superfactorial
  }
  return superfactorial;       // Return the computed superfactorial
}
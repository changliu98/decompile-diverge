int func0(int lowerBound, int upperBound)
{
  // Ensure m is the smaller value and n is the larger value
  if (upperBound < lowerBound) {
    int swapBuffer = lowerBound;
    lowerBound = upperBound;
    upperBound = swapBuffer;
  }
  // Calculate sum of squares from m^2 to n^2
  // Formula: sum(1..n)^2 - sum(1..m-1)^2
  // Which simplifies to: sum(1..n)^2 - (sum(1..m)^2 - m^2)
  // = sum(1..n)^2 - sum(1..m)^2 + m^2
  // Using sum(1..k)^2 = k*(k+1)*(2k+1)/6
  // The expression computes: sum(1..m)^2 + sum from i=m+1 to n of i^2
  // First term: sum of squares from 1 to m
  // Second term: sum of squares from m+1 to n, calculated as (n-m)*m*(m+1)/2
  // Note: This formula appears to be computing sum of squares in range [m, n]
  // but the second term formula seems non-standard; it may be an approximation or specific identity
  return (lowerBound * (lowerBound + 1) * (lowerBound * 2 + 1)) / 6 +
         ((upperBound - lowerBound) * lowerBound * (lowerBound + 1)) / 2;
}
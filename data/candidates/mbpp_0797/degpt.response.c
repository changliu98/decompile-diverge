// Calculates the sum of odd numbers in the range [l, r]
// by subtracting the sum of odd numbers up to l-1 from the sum up to r
int calculateOddSumInRange(int lowerBound, int upperBound) {
    return computeOddSumUpTo(upperBound) - computeOddSumUpTo(lowerBound - 1);
}
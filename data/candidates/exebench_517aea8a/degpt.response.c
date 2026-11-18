// Function to add two fractions n1/d1 and n2/d2
// Parameters:
//   n1, d1: numerator and denominator of the first fraction
//   n2, d2: numerator and denominator of the second fraction
//   r1, r2: pointers to store the resulting numerator and denominator
void sum(int firstNumerator, int firstDenominator, int secondNumerator, int secondDenominator, int *resultNumerator, int *resultDenominator)
{
    // Calculate the numerator of the sum: n1/d1 + n2/d2 = (n1*d2 + n2*d1) / (d1*d2)
    *resultNumerator = firstNumerator * secondDenominator + secondNumerator * firstDenominator;
    // Calculate the denominator of the sum
    *resultDenominator = firstDenominator * secondDenominator;
}
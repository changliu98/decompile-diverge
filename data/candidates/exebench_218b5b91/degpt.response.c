// Multiplies two fractions (n1/d1 and n2/d2) and stores the result in r1/r2
void mult(int numerator1, int denominator1, int numerator2, int denominator2, int *resultNumerator, int *resultDenominator)
{
  // Calculate the numerator of the product
  *resultNumerator = numerator1 * numerator2;
  // Calculate the denominator of the product
  *resultDenominator = denominator1 * denominator2;
}
void __cdecl sum(int numerator1, int denominator1, int numerator2, int denominator2, int *result_numerator, int *result_denominator)
{
  // Cross-multiply to find the new numerator: (n1 * d2) + (n2 * d1)
  *result_numerator = numerator1 * denominator2 + numerator2 * denominator1;
  
  // Multiply denominators to find the new denominator: d1 * d2
  *result_denominator = denominator1 * denominator2;
}
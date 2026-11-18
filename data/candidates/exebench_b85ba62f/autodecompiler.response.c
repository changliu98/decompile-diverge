int rational_best_approximation (unsigned long given_numerator, unsigned long given_denominator, unsigned long max_numerator, unsigned long max_denominator, unsigned long *numerator_result, unsigned long *denominator_result) {

 unsigned long n = given_numerator;
 unsigned long d = given_denominator;

 unsigned long t, a;
 unsigned long num0 = 0, num1 = 1, den0 = 1, den1 = 0;

 while (1) {
  if ((num1 > max_numerator) || (den1 > max_denominator)) {
   num1 = num0;
   den1 = den0;
   break;
  }
  if (d == 0) break;

  t = d;
  a = n / d;

  d = n % d;
  n = t;

  t = num1;
  num1 = a * num1 + num0;
  num0 = t;

  t = den1;
  den1 = a * den1 + den0;
  den0 = t;
 }

 *numerator_result = num1;
 *denominator_result = den1;

 return 0;
}
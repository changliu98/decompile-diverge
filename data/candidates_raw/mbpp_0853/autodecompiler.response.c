int sum_divisors(int n) {
 int curr_sum, curr_term, power, i, sum;
 while (n % 2 == 0) {
  n /= 2;
 }
 sum = 1;
 for (i = 3; i <= sqrt((double) n) + 1; i += 2) {
  power = 0;
  curr_sum = 1;
  curr_term = 1;
  while (n % i == 0) {
   power++;
   n /= i;
   curr_term *= i;
   curr_sum += curr_term;
  }
  sum *= curr_sum;
 }
 if (n > 2) {
  sum *= n + 1;
 }
 return sum;
}
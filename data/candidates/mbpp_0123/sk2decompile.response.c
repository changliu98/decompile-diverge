int _12(int n) {
  if (n < 1) {
    return -1;
  }
  int sum = 0;
  for (int i = 2; i <= n; i++) {
    int sum_divisors = 0;
    for (int j = 1; j < i; j++) {
      if (i % j == 0) {
        sum_divisors += j;
      }
    }
    int sum_divisors_of_sum_divisors = 0;
    for (int j = 1; j < sum_divisors; j++) {
      if (sum_divisors % j == 0) {
        sum_divisors_of_sum_divisors += j;
      }
    }
    if (i == sum_divisors_of_sum_divisors && i != sum_divisors) {
      sum += i;
    }
  }
  return sum;
}
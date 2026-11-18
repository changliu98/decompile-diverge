int func0(int limit) {
  if (limit < 1) {
    return -1;
  }
  int amicables_sum = 0;
  for (int num = 2; num <= limit; num++) {
    int sum_fact = 0;
    for (int fact = 1; fact < num; fact++) {
      if (num % fact == 0) {
        sum_fact += fact;
      }
    }
    int sum_fact2 = 0;
    for (int fact = 1; fact < sum_fact; fact++) {
      if (sum_fact % fact == 0) {
        sum_fact2 += fact;
      }
    }
    if (num == sum_fact2 && num != sum_fact) {
      amicables_sum += num;
    }
  }
  return amicables_sum;
}
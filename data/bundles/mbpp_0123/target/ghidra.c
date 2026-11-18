int func0(int limit)

{
  int fact_1;
  int sum_fact2;
  int fact;
  int sum_fact;
  int num;
  int amicables_sum;
  int limit_local;
  undefined4 local_c;
  
  if (limit < 1) {
    local_c = -1;
  }
  else {
    amicables_sum = 0;
    for (num = 2; num <= limit; num = num + 1) {
      sum_fact = 0;
      for (fact = 1; fact < num; fact = fact + 1) {
        if (num % fact == 0) {
          sum_fact = fact + sum_fact;
        }
      }
      sum_fact2 = 0;
      for (fact_1 = 1; fact_1 < sum_fact; fact_1 = fact_1 + 1) {
        if (sum_fact % fact_1 == 0) {
          sum_fact2 = fact_1 + sum_fact2;
        }
      }
      if ((num == sum_fact2) && (num != sum_fact)) {
        amicables_sum = num + amicables_sum;
      }
    }
    local_c = amicables_sum;
  }
  return local_c;
}
int func0(int limit) {
 int num, sum_fact, sum_fact2, fact;
 int amicables_sum;

 if (limit < 1) {
  return -1;
 }

 amicables_sum = 0;
 for (num = 2; num <= limit; num++) {
  sum_fact = 0;
  for (fact = 1; fact < num; fact++) {
   if (num % fact == 0) {
    sum_fact += fact;
   }
  }

  sum_fact2 = 0;
  for (fact = 1; fact < sum_fact; fact++) {
   if (sum_fact % fact == 0) {
    sum_fact2 += fact;
   }
  }

  if (sum_fact2 == num && sum_fact != num) {
   amicables_sum += num;
  }
 }

 return amicables_sum;
}
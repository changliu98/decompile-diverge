int func0(int n)
{
 int res;
 int i;
 int count;
 int curr_term;
 int curr_sum;

 if (n % 2 != 0) {
  return 0;
 }

 res = 1;

 for (i = 2; i <= (int)sqrt(n) + 1; i++) {
  count = 0;
  curr_sum = 1;
  curr_term = 1;
  while (n % i == 0) {
   count++;
   n /= i;
   if (i == 2 && count == 1) {
    curr_sum = 0;
   }
   curr_term *= i;
   curr_sum += curr_term;
  }
  res *= curr_sum;
 }

 if (n > 1) {
  res *= (n + 1);
 }

 return res;
}
int func0(int n) {
 int result;
 int product = 1;
 bool has_odd = false;
 while (true) {
  if (n <= 0) break;
  int digit = n % 10;
  if (digit % 2 == 1) {
   has_odd = true;
   product *= digit;
  }
  n /= 10;
 }
 if (has_odd) result = product;
 else result = 0;
 return result;
}
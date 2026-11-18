int func0(int base, int power) {
 int i, j, k, n, m, carry, result[1000] = {1}, sum;
 long long temp;
 for (n = 1, m = 0; ; ++m) {
  if (m >= power)
   break;
  carry = 0;
  for (i = 0; i < n; ++i) {
   temp = (long long)result[i] * base + carry;
   result[i] = temp % 10;
   carry = temp / 10;
  }
  while (carry > 0) {
   result[n] = carry % 10;
   carry /= 10;
   ++n;
  }
 }
 sum = 0;
 for (i = 0; i < n; ++i)
  sum += result[i];
 return sum;
}
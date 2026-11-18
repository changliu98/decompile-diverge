int func0(int m, int n) {
 int i;
 int gcd = 1;

 if (m % n == 0)
  return n;

 for (i = n / 2; i >= 1; i--) {
  if (m % i == 0 && n % i == 0) {
   gcd = i;
   break;
  }
 }

 return gcd;
}
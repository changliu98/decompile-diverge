int func0(int n)
{
 int totalPairs, pairs, i, ans;
 n++;
 i = 2;
 ans = n / 2;

 while (1) {
  if (i > n) break;
  totalPairs = n / i;
  pairs = totalPairs / 2;
  ans += i * pairs;
  if (totalPairs & 1) ans += n % i;
  i <<= 1;
 }

 return ans;
}
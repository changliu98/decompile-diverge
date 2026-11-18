int solve(int x, int y)
{
 int i, ans, tmp;
 if(x == y) {
  ans = 1;
 } else if(y - x >= 6) {
  ans = 0;
 } else {
  tmp = 1;
  for(i = x + 1; ; i++) {
   if(i > y) break;
   tmp *= i % 10;
   tmp %= 10;
  }
  ans = tmp % 10;
 }
 return ans;
}
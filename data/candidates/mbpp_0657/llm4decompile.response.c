int func0(int n)
{
 int i;
 int fact = 1;

 for (i = 2; i <= n; i++) {
  fact *= i;
  while (fact % 10 == 0) {
   fact /= 10;
  }
 }
 while (fact >= 10) {
  fact /= 10;
 }
 return (int)floor(fact);
}
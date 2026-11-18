int func0(int n)
{
 int sum;

 if(n == 0)
  sum = 0;
 else
 {
  int tmp = n % 10;
  sum = tmp + func0(n / 10);
 }
 return sum;
}